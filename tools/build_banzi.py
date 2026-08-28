#!/usr/bin/env python3
"""Generate a compact LaTeX codebook from Markdown notes and code snippets."""

from __future__ import annotations

import argparse
import os
import re
import shutil
import subprocess
import sys
import tomllib
from dataclasses import dataclass
from pathlib import Path
from typing import Any


PROJECT_ROOT = Path(__file__).resolve().parents[1]
CONFIG_FILE = PROJECT_ROOT / "book.toml"
BUILD_DIR = PROJECT_ROOT / "build"
DIST_DIR = PROJECT_ROOT / "dist"

DEFAULT_CODE_EXTENSIONS = {".cpp", ".cc", ".cxx", ".hpp", ".hh", ".h", ".sh"}
LISTING_LANGUAGES = {".sh": "bash"}
REQUIRED_TEX_FILES = (
    "ctexart.cls",
    "xeCJK.sty",
    "listings.sty",
    "tcolorbox.sty",
    "titlesec.sty",
    "enumitem.sty",
    "fancyhdr.sty",
    "lastpage.sty",
    "multicol.sty",
)


class BuildError(RuntimeError):
    """A user-facing build error."""


@dataclass
class Settings:
    title: str
    subtitle: str
    author: str
    date: str
    source_dir: Path
    template: Path
    output_name: str
    columns: int
    toc_depth: int
    code_line_numbers: bool
    code_extensions: set[str]


@dataclass
class Stats:
    directories: int = 0
    entries: int = 0
    markdown_files: int = 0
    code_files: int = 0


def fail(message: str) -> None:
    raise BuildError(message)


def read_toml(path: Path) -> dict[str, Any]:
    try:
        with path.open("rb") as handle:
            return tomllib.load(handle)
    except FileNotFoundError:
        fail(f"找不到配置文件：{path}")
    except tomllib.TOMLDecodeError as exc:
        fail(f"TOML 语法错误：{path}: {exc}")


def project_path(raw: str, field: str) -> Path:
    path = (PROJECT_ROOT / raw).resolve()
    if not path.is_relative_to(PROJECT_ROOT):
        fail(f"{field} 必须位于 Library/ 内：{raw}")
    return path


def load_settings() -> Settings:
    config = read_toml(CONFIG_FILE)
    book = config.get("book", {})
    render = config.get("render", {})

    title = str(book.get("title", "")).strip()
    if not title:
        fail("book.toml 的 book.title 不能为空")

    output_name = str(book.get("output_name", "Library")).strip()
    if not re.fullmatch(r"[A-Za-z0-9._-]+", output_name):
        fail("book.output_name 只能包含字母、数字、点、下划线和连字符")

    columns = int(book.get("columns", 2))
    if columns not in (1, 2):
        fail("book.columns 只能是 1 或 2")

    source_dir = project_path(str(book.get("source_dir", "chapters")), "book.source_dir")
    template = project_path(str(book.get("template", "template/library.tex")), "book.template")
    if not source_dir.is_dir():
        fail(f"内容目录不存在：{source_dir}")
    if not template.is_file():
        fail(f"LaTeX 模板不存在：{template}")

    raw_extensions = render.get("code_extensions", sorted(DEFAULT_CODE_EXTENSIONS))
    code_extensions = {
        extension.lower() if str(extension).startswith(".") else f".{extension.lower()}"
        for extension in map(str, raw_extensions)
    }
    if not code_extensions:
        fail("render.code_extensions 不能为空")

    return Settings(
        title=title,
        subtitle=str(book.get("subtitle", "")).strip(),
        author=str(book.get("author", "")).strip(),
        date=str(book.get("date", "")).strip(),
        source_dir=source_dir,
        template=template,
        output_name=output_name,
        columns=columns,
        toc_depth=int(book.get("toc_depth", 3)),
        code_line_numbers=bool(book.get("code_line_numbers", False)),
        code_extensions=code_extensions,
    )


def natural_key(path: Path) -> tuple[Any, ...]:
    return tuple(int(part) if part.isdigit() else part.casefold() for part in re.split(r"(\d+)", path.name))


def latex_escape(text: str) -> str:
    replacements = {
        "\\": r"\textbackslash{}",
        "&": r"\&",
        "%": r"\%",
        "$": r"\$",
        "#": r"\#",
        "_": r"\_",
        "{": r"\{",
        "}": r"\}",
        "~": r"\textasciitilde{}",
        "^": r"\textasciicircum{}",
    }
    return "".join(replacements.get(character, character) for character in text)


def split_front_matter(path: Path) -> tuple[dict[str, Any], str]:
    text = path.read_text(encoding="utf-8").replace("\r\n", "\n")
    lines = text.splitlines(keepends=True)
    if not lines or lines[0].strip() != "+++":
        return {}, text

    closing = next((index for index, line in enumerate(lines[1:], start=1) if line.strip() == "+++"), None)
    if closing is None:
        fail(f"TOML front matter 缺少结束标记 +++：{path}")

    header = "".join(lines[1:closing])
    body = "".join(lines[closing + 1 :])
    try:
        metadata = tomllib.loads(header)
    except tomllib.TOMLDecodeError as exc:
        fail(f"TOML front matter 语法错误：{path}: {exc}")
    return metadata, body


def enabled(metadata: dict[str, Any]) -> bool:
    return bool(metadata.get("enabled", True))


def heading(level: int, title: str) -> str:
    commands = ("section", "subsection", "subsubsection", "paragraph", "subparagraph")
    command = commands[min(max(level, 1), len(commands)) - 1]
    return f"\\{command}{{{latex_escape(title)}}}\n"


def run_capture(command: list[str], *, cwd: Path | None = None, input_text: str | None = None) -> str:
    result = subprocess.run(
        command,
        cwd=cwd,
        input=input_text,
        text=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        check=False,
    )
    if result.returncode != 0:
        detail = result.stderr.strip() or result.stdout.strip() or "未知错误"
        fail(f"命令执行失败：{' '.join(command)}\n{detail}")
    return result.stdout


def pandoc_markdown(path: Path, body: str, heading_shift: int) -> str:
    command = [
        "pandoc",
        "--from=markdown+pipe_tables+task_lists+strikeout+tex_math_dollars+raw_tex",
        "--to=latex",
        "--wrap=none",
        "--listings",
        f"--shift-heading-level-by={heading_shift}",
    ]
    return run_capture(command, cwd=path.parent, input_text=body).strip()


def layout_wrap(content: str, metadata: dict[str, Any], columns: int) -> str:
    chunks: list[str] = []
    if bool(metadata.get("page_break_before", False)):
        chunks.append(r"\clearpage")

    wide = bool(metadata.get("wide", False)) and columns == 2
    if wide:
        chunks.extend((r"\clearpage", r"\onecolumn"))

    chunks.append(content.strip())

    if wide:
        chunks.extend((r"\clearpage", r"\twocolumn"))
    if bool(metadata.get("page_break_after", False)):
        chunks.append(r"\clearpage")
    return "\n".join(chunk for chunk in chunks if chunk) + "\n"


def listing_path(path: Path) -> str:
    relative = os.path.relpath(path, BUILD_DIR).replace(os.sep, "/")
    if any(character in relative for character in "%#{}"):
        fail(f"代码路径包含 LaTeX 不安全字符（% # {{ }}）：{path}")
    return relative


def manifest_title(metadata: dict[str, Any], path: Path) -> str:
    title = metadata.get("title")
    if not isinstance(title, str) or not title.strip():
        fail(f"TOML 配置 title 必须是非空字符串：{path}")
    return title.strip()


def manifest_sources(
    config_path: Path,
    metadata: dict[str, Any],
    settings: Settings,
    references: dict[Path, Path],
    *,
    required: bool,
) -> list[Path]:
    raw_files = metadata.get("files")
    if raw_files is None:
        if required:
            fail(f"条目配置缺少 files：{config_path}")
        return []
    if not isinstance(raw_files, list) or any(
        not isinstance(item, str) or not item.strip() for item in raw_files
    ):
        fail(f"配置 files 必须是非空路径字符串数组：{config_path}")
    if required and not raw_files:
        fail(f"条目配置 files 不能为空：{config_path}")

    sources: list[Path] = []
    for raw in raw_files:
        relative = Path(raw)
        if relative.is_absolute():
            fail(f"配置 files 只能使用相对路径：{config_path}: {raw}")
        source = (config_path.parent / relative).resolve()
        if not source.is_relative_to(settings.source_dir):
            fail(f"配置 files 不能离开内容目录：{config_path}: {raw}")
        if not source.is_file():
            fail(f"配置引用的文件不存在：{config_path}: {raw}")
        suffix = source.suffix.lower()
        if suffix != ".md" and suffix not in settings.code_extensions:
            fail(f"配置引用了不支持的文件类型：{config_path}: {raw}")
        if source in references:
            fail(f"内容文件被重复引用：{source}\n  首次：{references[source]}\n  再次：{config_path}")
        references[source] = config_path
        sources.append(source)
    return sources


def render_source(path: Path, level: int, stats: Stats) -> str:
    if path.suffix.lower() == ".md":
        metadata, body = split_front_matter(path)
        if metadata:
            fail(f"Markdown 元信息请统一移至 _section.toml 的对应 entry：{path}")
        stats.markdown_files += 1
        return pandoc_markdown(path, body, level).strip()
    stats.code_files += 1
    options = ["style=librarycpp"]
    if language := LISTING_LANGUAGES.get(path.suffix.lower()):
        options.append(f"language={language}")
    return f"\\lstinputlisting[{','.join(options)}]{{{listing_path(path)}}}"


def render_manifest_sources(
    config_path: Path,
    metadata: dict[str, Any],
    level: int,
    settings: Settings,
    stats: Stats,
    references: dict[Path, Path],
    *,
    required: bool,
) -> list[str]:
    return [
        render_source(source, level, stats)
        for source in manifest_sources(config_path, metadata, settings, references, required=required)
    ]


def render_entry(
    config_path: Path,
    metadata: dict[str, Any],
    level: int,
    settings: Settings,
    stats: Stats,
    references: dict[Path, Path],
) -> str:
    if not enabled(metadata):
        return ""
    stats.entries += 1
    parts = [heading(level, manifest_title(metadata, config_path))]
    parts.extend(
        render_manifest_sources(
            config_path, metadata, level, settings, stats, references, required=True
        )
    )
    return layout_wrap("\n".join(parts), metadata, settings.columns)


def content_children(path: Path) -> list[Path]:
    return sorted(
        (child for child in path.iterdir() if child.is_dir() and not child.name.startswith(".")),
        key=natural_key,
    )


def section_entries(config_path: Path, metadata: dict[str, Any]) -> list[dict[str, Any]]:
    raw_entries = metadata.get("entries", [])
    if not isinstance(raw_entries, list) or any(
        not isinstance(entry, dict) for entry in raw_entries
    ):
        fail(f"章节配置 entries 必须是 TOML 表数组：{config_path}")
    return raw_entries


def render_directory(
    path: Path,
    level: int,
    settings: Settings,
    stats: Stats,
    references: dict[Path, Path],
) -> str:
    config_path = path / "_section.toml"
    if not config_path.is_file():
        fail(f"章节目录缺少 _section.toml：{path}")
    metadata = read_toml(config_path)
    extra_configs = sorted(
        (child for child in path.glob("*.toml") if child.name != "_section.toml"),
        key=natural_key,
    )
    if extra_configs:
        fail(f"章节目录只允许一个 _section.toml：{extra_configs[0]}")
    if not enabled(metadata):
        return ""

    stats.directories += 1
    parts = [heading(level, manifest_title(metadata, config_path))]
    parts.extend(render_manifest_sources(config_path, metadata, level, settings, stats, references, required=False))

    for entry in section_entries(config_path, metadata):
        parts.append(render_entry(config_path, entry, level + 1, settings, stats, references))
    for child in content_children(path):
        parts.append(render_directory(child, level + 1, settings, stats, references))

    return layout_wrap("\n".join(parts), metadata, settings.columns)


def render_source_tree(settings: Settings, stats: Stats) -> str:
    parts: list[str] = []
    references: dict[Path, Path] = {}
    root_configs = sorted(settings.source_dir.glob("*.toml"), key=natural_key)
    if root_configs:
        fail(f"内容根目录不允许 TOML，请放入章节目录：{root_configs[0]}")

    for child in content_children(settings.source_dir):
        parts.append(render_directory(child, 1, settings, stats, references))

    content = "\n".join(part for part in parts if part.strip()).strip()
    if not content:
        fail(f"内容目录中没有启用的条目配置：{settings.source_dir}")
    return content + "\n"


def graphic_paths(settings: Settings) -> str:
    directories = {PROJECT_ROOT / "assets"}
    directories.update(path.parent for path in settings.source_dir.rglob("*.md"))
    values: list[str] = []
    for directory in sorted(directories, key=lambda item: str(item)):
        relative = os.path.relpath(directory, BUILD_DIR).replace(os.sep, "/").rstrip("/") + "/"
        if any(character in relative for character in "%#{}"):
            fail(f"图片目录包含 LaTeX 不安全字符（% # {{ }}）：{directory}")
        values.append(f"{{{relative}}}")
    return "\\graphicspath{" + "".join(values) + "}"


def render_main_tex(settings: Settings) -> str:
    template = settings.template.read_text(encoding="utf-8")
    subtitle_block = ""
    if settings.subtitle:
        subtitle_block = "\n".join(
            (
                r"  \vspace{0.9em}",
                r"  {\Large\color{LibraryGray}"
                + latex_escape(settings.subtitle)
                + r"\par}",
            )
        )
    date_block = ""
    if settings.date:
        date_block = "\n".join(
            (
                r"  \vspace{0.6em}",
                r"  {\normalsize\color{LibraryGray}"
                + latex_escape(settings.date)
                + r"\par}",
            )
        )
    replacements = {
        "@@TITLE@@": latex_escape(settings.title),
        "@@SUBTITLE_BLOCK@@": subtitle_block,
        "@@AUTHOR@@": latex_escape(settings.author),
        "@@DATE_BLOCK@@": date_block,
        "@@TOC_DEPTH@@": str(settings.toc_depth),
        "@@CODE_NUMBERS@@": "left" if settings.code_line_numbers else "none",
        "@@COLUMN_START@@": r"\twocolumn" if settings.columns == 2 else "",
        "@@GRAPHIC_PATHS@@": graphic_paths(settings),
    }
    for marker, value in replacements.items():
        template = template.replace(marker, value)
    unresolved = sorted(set(re.findall(r"@@[A-Z0-9_]+@@", template)))
    if unresolved:
        fail(f"LaTeX 模板中存在未替换标记：{', '.join(unresolved)}")
    return template.rstrip() + "\n"


def write_if_changed(path: Path, content: str) -> None:
    if path.is_file() and path.read_text(encoding="utf-8") == content:
        return
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(content, encoding="utf-8")


def clean_outputs() -> None:
    for directory in (BUILD_DIR, DIST_DIR):
        directory.mkdir(parents=True, exist_ok=True)
        for child in directory.iterdir():
            if child.name == ".gitkeep":
                continue
            if child.is_dir() and not child.is_symlink():
                shutil.rmtree(child)
            else:
                child.unlink()


def command_path(name: str) -> str:
    path = shutil.which(name)
    if not path:
        fail(f"找不到命令 `{name}`；请检查 PATH 或安装对应依赖")
    return path


def preflight(*, require_tex: bool) -> dict[str, str]:
    tools = {"python3": sys.executable, "pandoc": command_path("pandoc")}
    if not require_tex:
        return tools

    tools.update(
        {
            "xelatex": command_path("xelatex"),
            "latexmk": command_path("latexmk"),
            "kpsewhich": command_path("kpsewhich"),
        }
    )
    missing = [
        filename
        for filename in REQUIRED_TEX_FILES
        if not run_capture([tools["kpsewhich"], filename]).strip()
    ]
    if missing:
        fail("TinyTeX 缺少必要文件：" + ", ".join(missing) + "。请运行 ./install-packages.sh")
    return tools


def compile_pdf(settings: Settings, tools: dict[str, str], main_tex: Path) -> Path:
    command = [
        tools["latexmk"],
        "-xelatex",
        "-interaction=nonstopmode",
        "-halt-on-error",
        "-file-line-error",
        main_tex.name,
    ]
    result = subprocess.run(command, cwd=BUILD_DIR, check=False)
    if result.returncode != 0:
        fail(f"PDF 编译失败；请查看 {BUILD_DIR / (settings.output_name + '.log')}")

    built_pdf = BUILD_DIR / f"{settings.output_name}.pdf"
    if not built_pdf.is_file():
        fail(f"latexmk 成功退出，但没有生成 PDF：{built_pdf}")
    DIST_DIR.mkdir(parents=True, exist_ok=True)
    final_pdf = DIST_DIR / built_pdf.name
    shutil.copy2(built_pdf, final_pdf)
    return final_pdf


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="从 Markdown 与代码片段生成 LaTeX 模板书")
    parser.add_argument("--check", action="store_true", help="只检查配置、依赖和内容，不写文件")
    parser.add_argument("--tex-only", action="store_true", help="只生成 TeX，不编译 PDF")
    parser.add_argument("--clean", action="store_true", help="构建前清理 build/ 与 dist/ 中的旧产物")
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    settings = load_settings()
    tools = preflight(require_tex=not args.tex_only or args.check)
    stats = Stats()
    generated_content = render_source_tree(settings, stats)
    main_tex = render_main_tex(settings)

    if args.check:
        print("Library 检查通过")
        print(f"  内容目录：{settings.source_dir}")
        print(f"  章节目录：{stats.directories}")
        print(f"  条目：{stats.entries}")
        print(f"  Markdown：{stats.markdown_files}")
        print(f"  代码片段：{stats.code_files}")
        for name, path in tools.items():
            print(f"  {name}：{path}")
        return 0

    if args.clean:
        clean_outputs()
    BUILD_DIR.mkdir(parents=True, exist_ok=True)
    DIST_DIR.mkdir(parents=True, exist_ok=True)

    content_file = BUILD_DIR / "generated-content.tex"
    main_file = BUILD_DIR / f"{settings.output_name}.tex"
    write_if_changed(content_file, "% 此文件由 tools/build_banzi.py 自动生成。\n" + generated_content)
    write_if_changed(main_file, main_tex)

    print(f"已生成：{main_file}")
    print(f"已生成：{content_file}")
    print(
        f"内容：{stats.directories} 个目录，{stats.entries} 个条目，"
        f"{stats.markdown_files} 个 Markdown，{stats.code_files} 个代码片段"
    )

    if args.tex_only:
        return 0

    final_pdf = compile_pdf(settings, tools, main_file)
    print(f"已生成 PDF：{final_pdf}")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except BuildError as exc:
        print(f"错误：{exc}", file=sys.stderr)
        raise SystemExit(1)

# Library

把分散的 Markdown 知识点和代码片段生成一份紧凑的中文 LaTeX 模板书。

## 快速开始

```bash
cd Library
./build.sh
```

最终成品位于 `dist/Library.pdf`。生成的 `build/Library.tex` 和 `build/generated-content.tex` 仅用于调试，不要直接维护。

常用命令：

```bash
./build.sh --check       # 检查工具、配置和源文件
./build.sh --tex-only    # 只生成 TeX，不编译 PDF
./build.sh --clean       # 清理旧产物后重新构建
./install-packages.sh    # 按 tex-packages.txt 补齐 TinyTeX 宏包
```

依赖：Python 3.11+、Pandoc、TinyTeX、XeLaTeX 和 latexmk。

## 内容目录约定

所有内容放在 `chapters/`。每个章节目录只有一个 `_section.toml`，统一管理章节和下面的所有条目：

```text
chapters/
└── 01_Geometry/
    ├── _section.toml
    ├── vector_intro.md
    ├── vector.cpp
    └── vector_examples.md
```

- 目录表示章节，必须包含 `_section.toml`，且不允许存在其他 TOML。
- `_section.toml` 中的 `[[entries]]` 按书写顺序生成条目，不再依赖多个 TOML 文件名排序。
- Markdown、C++ 和 Shell 文件名可以与标题完全不同，且不参与排序。
- 只有被 `files` 引用的 `.md/.cpp/.hpp/.h/...` 会进入 PDF。
- 图片建议放在 Markdown 相邻目录或 `assets/`。

## 章节配置

`_section.toml` 的 `title` 管理章节标题，每个 `[[entries]]` 管理一个小节。`files` 按数组顺序拼接同一标题下的内容：

```toml
title = "Geometry"

[[entries]]
title = "vector"
files = [
  "vector_intro.md",
  "vector.cpp",
  "vector_examples.md",
]

[[entries]]
title = "seg_poly"
files = ["seg_poly.cpp"]
```

一个条目可以包含任意数量的 Markdown、C++ 和 Shell 文件。引用路径相对于 `_section.toml`，必须位于 `chapters/` 内。缺失文件、不支持的扩展名、越界路径或重复引用都会使构建失败。章节本身如果需要在条目前放置内容，也可在顶层添加 `files` 数组。

Markdown 文件只写正文，不再使用 front matter；标题和排版字段统一放在 `_section.toml` 中。

章节顶层与每个 `[[entries]]` 都可使用：

- `wide = true`：在双栏书中临时切到单栏。
- `page_break_before/page_break_after`：内容前后强制分页。
- `enabled = false`：暂时排除该章节或条目。

## 排版说明

- 默认 A4 横向双栏、紧凑页边距、自动目录和页眉页脚；正文先排满左栏，再从右栏顶部继续向下排列。
- 中英文正文、标题和代码统一使用 `Maple Mono NF CN` 字体。
- 字体文件位于 `assets/fonts/MapleMono-NF-CN/`，构建时直接按相对路径加载，无需安装系统字体。
- C++ 和 Shell 使用 `listings`，支持语法高亮、中文注释、折行和可选行号。
- Markdown 由 Pandoc 转换；宽表格请设置 `wide = true`，因为 `longtable` 不能直接放在双栏中。
- `book.toml` 控制书名、作者、列数、代码行号和输出文件名。

## 恢复依赖

`tex-packages.txt` 相当于项目的 TeX 依赖清单。新机器安装 TinyTeX 后运行：

```bash
./install-packages.sh
```

`tlmgr` 会自动跳过已经安装的宏包并补齐依赖。

## 接入旧 Banzi.md

当前框架不会修改仓库根目录的 `Banzi.md`。确认版式后，可以将它整体复制为一个 Markdown 章节，或按一级标题拆分到多个目录；拆分工作应单独执行并核对内容，避免破坏原文件。

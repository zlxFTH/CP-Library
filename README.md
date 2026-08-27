# Library

把分散的 Markdown 知识点和 C++ 代码片段生成一份紧凑的中文 LaTeX 模板书。

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

所有内容放在 `chapters/`。目录与文件使用数字前缀控制顺序：

```text
chapters/
├── 01_基础/
│   ├── index.md
│   ├── 01_fast_io.cpp
│   ├── 01_fast_io.cpp.toml
│   └── 02_复盘记录.md
└── 02_图论/
    ├── 01_最短路.md
    └── 02_dijkstra.cpp
```

- 文件夹：生成章节标题。
- `index.md`：生成文件夹开场正文，不重复生成标题。
- 其他 `.md`：生成一个带标题的知识点条目。
- `.cpp/.hpp/.h/...`：生成一个带标题的 C++ 代码条目。
- 其他文件默认忽略；图片建议放在相邻目录或 `assets/`。

标题默认来自文件名：去掉开头数字，将 `_` 和 `-` 转为空格。

## Markdown 元信息

Markdown 文件可使用 TOML front matter：

```markdown
+++
title = "最短路备忘"
wide = true
page_break_before = true
page_break_after = false
enabled = true
+++

这里开始写正文。
```

字段含义：

- `title`：覆盖文件名生成的标题。
- `wide`：在双栏书中临时切到单栏，适合宽表格和宽公式。
- `page_break_before/page_break_after`：条目前后强制分页。
- `enabled = false`：暂时排除该文件。

文件夹可以使用 `_section.toml` 设置同样的字段。C++ 文件使用同名旁车配置，例如 `dijkstra.cpp.toml`：

```toml
title = "Dijkstra"
wide = false
page_break_before = false
enabled = true
```

## 排版说明

- 默认 A4 横向双栏、紧凑页边距、自动目录和页眉页脚；正文先排满左栏，再从右栏顶部继续向下排列。
- 中文使用 XeLaTeX、CTeX 和 Fandol 字体。
- C++ 使用 `listings`，支持中文注释、折行和可选行号。
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

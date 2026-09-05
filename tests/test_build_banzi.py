import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

from tools import build_banzi


class ManifestRenderingTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory()
        self.source_dir = Path(self.temporary.name) / "chapters"
        self.section_dir = self.source_dir / "01_Geometry"
        self.section_dir.mkdir(parents=True)
        (self.section_dir / "_section.toml").write_text('title = "Geometry"\n', encoding="utf-8")
        self.settings = build_banzi.Settings(
            title="Test",
            subtitle="",
            author="",
            date="",
            source_dir=self.source_dir,
            template=Path("unused"),
            output_name="Test",
            columns=2,
            toc_depth=3,
            code_line_numbers=False,
            code_extensions={".cpp"},
        )

    def tearDown(self):
        self.temporary.cleanup()

    def write(self, name: str, content: str) -> None:
        (self.section_dir / name).write_text(content, encoding="utf-8")

    def configure(self, content: str) -> None:
        self.write("_section.toml", 'title = "Geometry"\n' + content)

    def test_one_title_renders_mixed_sources_in_manifest_order(self):
        self.write("z_intro.md", "intro")
        self.write("a_point.cpp", "struct P {};")
        self.write("m_notes.md", "notes")
        self.write("ignored.cpp", "int ignored;")
        self.configure(
            '[[entries]]\ntitle = "Point"\n'
            'files = ["z_intro.md", "a_point.cpp", "m_notes.md"]\n'
        )
        stats = build_banzi.Stats()
        fake_markdown = lambda path, body, level: f"MARKDOWN:{path.name}"
        with patch.object(build_banzi, "pandoc_markdown", side_effect=fake_markdown):
            rendered = build_banzi.render_source_tree(self.settings, stats)

        self.assertEqual(rendered.count("\\subsection{Point}"), 1)
        self.assertLess(rendered.index("MARKDOWN:z_intro.md"), rendered.index("a_point.cpp"))
        self.assertLess(rendered.index("a_point.cpp"), rendered.index("MARKDOWN:m_notes.md"))
        self.assertNotIn("ignored.cpp", rendered)
        self.assertEqual(
            (stats.directories, stats.entries, stats.markdown_files, stats.code_files),
            (1, 1, 2, 1),
        )

    def test_duplicate_source_reference_fails(self):
        self.write("point.cpp", "struct P {};")
        self.configure(
            '[[entries]]\ntitle = "First"\nfiles = ["point.cpp"]\n'
            '[[entries]]\ntitle = "Second"\nfiles = ["point.cpp"]\n'
        )

        with self.assertRaisesRegex(build_banzi.BuildError, "重复引用"):
            build_banzi.render_source_tree(self.settings, build_banzi.Stats())

    def test_entries_array_controls_entry_order(self):
        self.write("late.cpp", "int late;")
        self.write("early.cpp", "int early;")
        self.configure(
            '[[entries]]\ntitle = "Late"\nfiles = ["late.cpp"]\n'
            '[[entries]]\ntitle = "Early"\nfiles = ["early.cpp"]\n'
        )

        rendered = build_banzi.render_source_tree(self.settings, build_banzi.Stats())

        self.assertLess(
            rendered.index("\\subsection{Late}"),
            rendered.index("\\subsection{Early}"),
        )

    def test_entry_title_is_required(self):
        self.write("point.cpp", "struct P {};")
        self.configure('[[entries]]\nfiles = ["point.cpp"]\n')

        with self.assertRaisesRegex(build_banzi.BuildError, "title"):
            build_banzi.render_source_tree(self.settings, build_banzi.Stats())

    def test_shell_source_uses_bash_language(self):
        self.settings.code_extensions.add(".sh")
        self.write("test.sh", "mk() { g++ -o $1 $1.cpp -O2; }")
        self.configure('[[entries]]\ntitle = "test"\nfiles = ["test.sh"]\n')

        rendered = build_banzi.render_source_tree(self.settings, build_banzi.Stats())

        self.assertIn("[style=librarycpp,language=bash]", rendered)

    def test_extra_toml_in_section_fails(self):
        self.write("legacy.toml", 'title = "Legacy"\nfiles = ["legacy.cpp"]\n')

        with self.assertRaisesRegex(build_banzi.BuildError, "只允许一个 _section.toml"):
            build_banzi.render_source_tree(self.settings, build_banzi.Stats())

    def test_toml_in_content_root_fails(self):
        (self.source_dir / "legacy.toml").write_text('title = "Legacy"\n', encoding="utf-8")

        with self.assertRaisesRegex(build_banzi.BuildError, "内容根目录不允许 TOML"):
            build_banzi.render_source_tree(self.settings, build_banzi.Stats())


class CleanOutputsTests(unittest.TestCase):
    def test_clean_removes_build_outputs_and_only_the_generated_dist_pdf(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            build_dir = root / "build"
            dist_dir = root / "dist"
            build_dir.mkdir()
            dist_dir.mkdir()
            (build_dir / ".gitkeep").write_text("\n", encoding="utf-8")
            (build_dir / "Library.aux").write_text("temporary", encoding="utf-8")
            (build_dir / "nested").mkdir()
            (build_dir / "nested" / "temporary.log").write_text("temporary", encoding="utf-8")
            (dist_dir / "Library.pdf").write_bytes(b"generated")
            (dist_dir / "NOI notes.pdf").write_bytes(b"archive")
            (dist_dir / "reference.txt").write_text("keep", encoding="utf-8")

            with (
                patch.object(build_banzi, "BUILD_DIR", build_dir),
                patch.object(build_banzi, "DIST_DIR", dist_dir),
            ):
                build_banzi.clean_outputs("Library")

            self.assertEqual(sorted(path.name for path in build_dir.iterdir()), [".gitkeep"])
            self.assertFalse((dist_dir / "Library.pdf").exists())
            self.assertEqual((dist_dir / "NOI notes.pdf").read_bytes(), b"archive")
            self.assertEqual((dist_dir / "reference.txt").read_text(encoding="utf-8"), "keep")


if __name__ == "__main__":
    unittest.main()

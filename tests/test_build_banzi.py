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

    def test_one_title_renders_mixed_sources_in_manifest_order(self):
        self.write("z_intro.md", "intro")
        self.write("a_point.cpp", "struct P {};")
        self.write("m_notes.md", "notes")
        self.write("ignored.cpp", "int ignored;")
        self.write(
            "01_point.toml",
            'title = "Point"\nfiles = ["z_intro.md", "a_point.cpp", "m_notes.md"]\n',
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
        self.write("01_first.toml", 'title = "First"\nfiles = ["point.cpp"]\n')
        self.write("02_second.toml", 'title = "Second"\nfiles = ["point.cpp"]\n')

        with self.assertRaisesRegex(build_banzi.BuildError, "重复引用"):
            build_banzi.render_source_tree(self.settings, build_banzi.Stats())

    def test_entry_config_names_control_entry_order(self):
        self.write("late.cpp", "int late;")
        self.write("early.cpp", "int early;")
        self.write("10_late.toml", 'title = "Late"\nfiles = ["late.cpp"]\n')
        self.write("02_early.toml", 'title = "Early"\nfiles = ["early.cpp"]\n')

        rendered = build_banzi.render_source_tree(self.settings, build_banzi.Stats())

        self.assertLess(
            rendered.index("\\subsection{Early}"),
            rendered.index("\\subsection{Late}"),
        )

    def test_entry_title_is_required(self):
        self.write("point.cpp", "struct P {};")
        self.write("01_point.toml", 'files = ["point.cpp"]\n')

        with self.assertRaisesRegex(build_banzi.BuildError, "title"):
            build_banzi.render_source_tree(self.settings, build_banzi.Stats())

    def test_shell_source_uses_bash_language(self):
        self.settings.code_extensions.add(".sh")
        self.write("test.sh", "mk() { g++ -o $1 $1.cpp -O2; }")
        self.write("01_test.toml", 'title = "test"\nfiles = ["test.sh"]\n')

        rendered = build_banzi.render_source_tree(self.settings, build_banzi.Stats())

        self.assertIn("[style=librarycpp,language=bash]", rendered)


if __name__ == "__main__":
    unittest.main()

"""Versioned Report V1.1 launcher; leaves the V1 launcher untouched."""
from pathlib import Path
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent / "analyzer"))
from urb_analyzer.cli import main

raise SystemExit(main(["--gui"]))

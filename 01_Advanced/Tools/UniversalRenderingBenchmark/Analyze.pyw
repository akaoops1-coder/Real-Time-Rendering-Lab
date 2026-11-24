"""Windows double-click launcher for the bundled RTR V1 analyzer."""
from pathlib import Path
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent / "phase4" / "analyzer"))
from urb_analyzer.cli import main

raise SystemExit(main(["--gui"]))

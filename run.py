import subprocess, sys
from pathlib import Path

ROOT = Path(__file__).parent

EXECUTABLES = {
    "src":    ROOT / "src"    / "build" / "minesweeper.exe",
    "server": ROOT / "server" / "build" / "minesweeper_server.exe",
}

if len(sys.argv) < 2 or sys.argv[1] not in EXECUTABLES:
    print("Usage: python run.py src|server")
    sys.exit(1)

exe = EXECUTABLES[sys.argv[1]]

if not exe.exists():
    print(f"Executable not found: {exe}")
    print("Run build.py first.")
    sys.exit(1)

subprocess.run([str(exe)], cwd=exe.parent, check=True)
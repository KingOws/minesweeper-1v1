import subprocess, sys, shutil
from pathlib import Path

ROOT = Path(__file__).parent

def build(folder):
    cwd = ROOT / folder
    subprocess.run(["cmake", "-G", "Ninja", "-B", "build"], check=True, cwd=cwd)
    subprocess.run(["cmake", "--build", "build"],            check=True, cwd=cwd)

def clean():
    for folder in ["src/build", "server/build"]:
        path = ROOT / folder
        if path.exists():
            shutil.rmtree(path)
            print(f"Deleted {path}")
        else:
            print(f"Nothing to clean in {path}")

target = sys.argv[1] if len(sys.argv) > 1 else "both"

if target == "clean":
    clean()
elif target == "src":
    build("src")
elif target == "server":
    build("server")
elif target == "both":
    build("src")
    build("server")
else:
    print(f"Unknown target '{target}'. Use: src, server, both (default), or clean.")
    sys.exit(1)
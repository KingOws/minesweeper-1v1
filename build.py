import os
import shutil
import stat
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).parent


def copy_dlls(build_folder):
    dll_src = Path("C:/SFML-3.0.2/bin")
    dll_dst = ROOT / build_folder / "build"
    for dll in dll_src.glob("*.dll"):
        shutil.copy2(dll, dll_dst)
        print(f"Copied {dll.name}")


def build(folder):
    cwd = ROOT / folder
    subprocess.run(["cmake", "-G", "Ninja", "-B", "build"], check=True, cwd=cwd)
    subprocess.run(["cmake", "--build", "build"], check=True, cwd=cwd)
    copy_dlls(folder)


def remove_readonly(func, path, _):
    os.chmod(path, stat.S_IWRITE)
    func(path)


def clean():
    for folder in ["src/build"]:
        path = ROOT / folder
        if path.exists():
            shutil.rmtree(path, onexc=remove_readonly)
            print(f"Deleted {path}")
        else:
            print(f"Nothing to clean in {path}")


target = sys.argv[1] if len(sys.argv) > 1 else "both"

if target == "clean":
    clean()
elif target == "src":
    build("src")
else:
    print(f"Unknown target '{target}'. Use: src, or clean.")
    sys.exit(1)

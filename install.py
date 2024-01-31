import subprocess
import os
def main():
    build_dir="build"
    local_dir="~/.local"
    if not os.path.exists(build_dir):
        os.mkdir(build_dir)
    root_dir = os.path.split(__file__)[0]
    cmake_cmd = ["cmake", os.path.abspath(root_dir)]

    cmake_cmd += ["-DCMAKE_INSTALL_PREFIX=" + local_dir]
    subprocess.check_call(cmake_cmd, cwd=build_dir)

    subprocess.check_call(["make", "-j2"], cwd=build_dir)

if __name__ == "__main__":
    main()
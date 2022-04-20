import os
import subprocess
import re
import platform

def call_shell(*args):
    try:
        return subprocess.check_output(" ".join(args), shell=True).strip().decode('utf-8')
    except:
        print(f'ERROR: invalid command "{" ".join(args)}"')
        exit(1)

source_dir = "src"
object_dir = "obj"
compiler = "c++"
compile_pattern = ".*\.cpp$"

cflags = f"-I{source_dir}" + call_shell("pkg-config --cflags SDL2")
err_flags = "-Wall -Wunused-variable -Wextra -Wno-enum-compare -fpermissive -g -ggdb -fdiagnostics-color=always"
libs = call_shell("pkg-config --libs SDL2") + " " + call_shell("pkg-config --libs SDL2_Image")
out_ext = ""

if platform.system() == "Windows":
    out_ext = "exe"
else:
    out_ext = "out"

compiled_objects = []

for [dir, subDirs, files] in os.walk(source_dir):
    for file in files:
        if not re.search(compile_pattern, file) == None:
            compile_path = os.path.join(dir, file)
            out_path = os.path.join(object_dir, file.split('.')[0]) + '.o'
            print(f"INFO: Compiling {compile_path}...")
            call_shell(f"{compiler} {cflags} {err_flags} -c {compile_path} -o {out_path} {libs}")
            compiled_objects.append(out_path)

print("INFO: Linking...")
call_shell(f'{compiler} {cflags} {err_flags} -o bin/main.{out_ext} {" ".join(compiled_objects)} {libs}')
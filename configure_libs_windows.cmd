@echo off

git clone https://github.com/raysan5/raylib --recursive

mkdir lib
mkdir include

cd raylib\src
make -j PLATFORM=PLATFORM_DESKTOP

copy libraylib.a ..\..\lib
xcopy *.h ..\..\include

cd ..\..\
rm -r -f raylib
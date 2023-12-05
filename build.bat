call "E:\VS\VC\Auxiliary\Build\vcvarsall.bat" x64
set "folderPath=build"
if not exist "%folderPath%" (
    mkdir "%folderPath%"
)
cl ./main.c -o ./build/main.exe
rm main.obj
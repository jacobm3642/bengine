call "E:\VS\VC\Auxiliary\Build\vcvarsall.bat" x64
set "folderPath=build"
if not exist "%folderPath%" (
    mkdir "%folderPath%"
)
cl ./main.c /Fe:build/main.exe /link user32.lib
rm main.obj
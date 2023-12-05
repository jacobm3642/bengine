call "E:\VS\VC\Auxiliary\Build\vcvarsall.bat" x64
set "folderPath=build"
if not exist "%folderPath%" (
    mkdir "%folderPath%"
)
set "compilerFlag=E:\glew-2.2.0\lib\Release\Win32\glew32.lib user32.lib gdi32.lib opengl32.lib"
cl main.c /EHsc /I"E:\glew-2.2.0\include" /I"E:\glew-2.2.0\lib" /Fe:build/main.exe /link %compilerFlag%
rm main.obj
call "E:\VS\VC\Auxiliary\Build\vcvarsall.bat" x64
set "folderPath=E:\Bengine\bengine\build"
if not exist "%folderPath%" (
    mkdir "%folderPath%"
)
set "compilerFlag=E:\glew-2.2.0\lib\Release\x64\glew32.lib user32.lib gdi32.lib opengl32.lib"
set "outputFile=%folderPath%\main.exe"
cl E:\Bengine\bengine\main.c /EHsc /I"E:\glew-2.2.0\include" /I"E:\glew-2.2.0\lib" /Fe:%outputFile% /link %compilerFlag%
del main.obj
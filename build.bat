call "E:\VS\VC\Auxiliary\Build\vcvarsall.bat" x64

set "folderPath=E:\Bengine\bengine"
if not exist "%folderPath%\build" (
    mkdir "%folderPath%\build"
)

set "compilerFlag=E:\glew-2.2.0\lib\Release\x64\glew32.lib user32.lib gdi32.lib opengl32.lib"
set "outputFile=%folderPath%\build\main.exe"
set "inputFiles=%folderPath%\main.c %folderPath%\renderer\objects.c"

cl %inputFiles% /EHsc /I"E:\glew-2.2.0\include" /Fe:%outputFile% /link %compilerFlag%
flags=" -Wall -Werror -lX11 -lGL -lGLU -lGLEW"

gcc $flags main.c -o ./build/main 
./build/main
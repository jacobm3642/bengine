#include <stdio.h>

#if defined(_WIN32) || defined(_WIN64) 
int main(){
    printf("you're on windows\n");
    return 0;
}
#elif defined(__linux__) 
int main(){
    printf("you're on linux\n");
    return 0;
}
#else
    #error "Unsupported operating system"
#endif
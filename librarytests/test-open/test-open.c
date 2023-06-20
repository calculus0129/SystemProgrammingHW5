#include <stdio.h>
#include <fcntl.h> // for the flag constants.
#include <unistd.h> // for write() and read().
#include <string.h>

int main() {
    int w = open("output.txt", O_WRONLY | O_TRUNC | O_CREAT, 0x777);
    dup2(w, 1); // link the standard output to fd w.
    int T1 = open("input.txt", O_RDONLY); printf("%d\n", T1);
    int T2 = open("input.txt", O_WRONLY); printf("%d\n", T2);
    int T3 = open("input.txt", O_RDWR); printf("%d\n", T3);
    //printf("the return value of open(\"input.txt\", O_RDONLY); is: %d", r);

    return 0;
}
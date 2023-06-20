#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "flock.h"

int main() {
    int i=0;
    pid_t pid = fork();
    if(pid==0) { // child
        while(i++<5) write(1, "I'm a child! ", sizeof("I'm a child! "));
        puts("");
    }
    else if((pid=fork())==0) {
        while(i++<5) write(1, "I'm a parent! ", sizeof("I'm a parent! "));
        puts("");
    }
    else {
        while(i++<5) write(1, "I'm a grandparent! ", sizeof("I'm a grandparent! "));
        puts("");
    }
    return 0;
}
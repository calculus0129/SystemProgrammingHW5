#include <unistd.h>
#include "flock.h"

int main() {
    int i=0;
    pid_t pid = fork();
    if(pid==0) { // child
        while(!lockThisFileAsExclusive(1));
        while(i++<5) write(1, "I'm a child! ", sizeof("I'm a child! "));
        unlockThisFile(1);
    }
    else if((pid=fork())==0) {
        while(!lockThisFileAsExclusive(1));
        while(i++<5) write(1, "I'm a parent! ", sizeof("I'm a parent! "));
        unlockThisFile(1);
    }
    else {
        while(!lockThisFileAsExclusive(1));
        while(i++<5) write(1, "I'm a grandparent! ", sizeof("I'm a grandparent! "));
        unlockThisFile(1);
    }
    return 0;
}

/*OUTPUT: The flock() DOES NOT WORK WELL...
I'm a child! I'm a grandparent! I'm a parent! I'm a child! I'm a grandparent! I'm a parent! I'm a parent! I'm a child! I'm a grandparent! I'm a parent! I'm a child! I'm a grandparent! I'm a parent! I'm a child! I'm a grandparent!
*/
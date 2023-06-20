/**
 * Testing: myfopen(), myfwrite(), and myfclose().
*/
#include "../mystdio.h"
//#include <stdio.h>
int main() {
    int i=10;
    myFILE* f = myfopen("test0-output.txt", "a");
    char wr[] = "Hello! this is well-implemented!\n", wr2[]="\nTest0 complete!\n";
    myfwrite(wr, 1, sizeof(wr), f);
    //while(i--) 
    //myfwrite(wr2, 1, sizeof(wr2), f);
    myfflush(f);
    myfclose(f);
    return 0;
}
/**
 * Testing: myfopen(), myfwrite(), and myfclose().
*/
#include "../mystdio.h"
//#include <stdio.h>
int main() {
    int i=10;
    myFILE* f = myfopen("test0-output.txt", "w");
    char wr[] = "Hello! this is well-implemented!\n", wr2[]="\nTest0 complete!\n";
    while(i--) myfwrite(wr, sizeof(char), (sizeof(wr)-1)/sizeof(char), f);
    myfwrite(wr2, 1, sizeof(wr2)-1, f);
    myfflush(f);
    myfclose(f);
    return 0;
}
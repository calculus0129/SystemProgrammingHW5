/**
 * reading + writing + seeking (almost) all possible combinations.
*/
#include "../mystdio.h"
#include <assert.h>
#include <stdio.h>

void curpos(int fd) {
    printf("filepos: %ld\n", lseek(fd, 0, SEEK_CUR)); // 0
}

int main() {
    char dirname[] = "output5-2.txt";
    myFILE *f = myfopen(dirname, "w+");
    char s1[] = "For Example,"; // 12
    char s2[] = "This is, "; // 9
    char s3[] = "Program is running."; // 19
    char s4[] = "MMMMMMMM"; // 8
    char r1[sizeof("For Example,")/sizeof(char)]="";
    char r2[sizeof("This is, ")/sizeof(char)]="";
    char r3[sizeof("Program is running.")/sizeof(char)]="";
    char r4[sizeof("MMMMMMMM")/sizeof(char)]="";

    // The comments are my-ideal-code-specific.
    myfwrite(s1, sizeof(char), strlen(s1), f); curpos(f->fd);
    myfwrite(s2, sizeof(char), strlen(s2), f); curpos(f->fd);
    myfwrite(s3, sizeof(char), strlen(s3), f); curpos(f->fd);
    myfwrite(s4, sizeof(char), strlen(s4), f); curpos(f->fd);
    myfseek(f, 0, SEEK_CUR); curpos(f->fd); // 48
    if(myfseek(f, 0, SEEK_SET)==-1) puts("Error in myfseek!");
    curpos(f->fd); // must be 0.
    puts("");
    
    myfread(r1, sizeof(char), strlen(s1), f); assert(strcmp(s1, r1)==0);
    myfread(r2, sizeof(char), strlen(s2), f); assert(strcmp(s2, r2)==0);
    myfread(r3, sizeof(char), strlen(s3), f); assert(strcmp(s3, r3)==0);
    myfread(r4, sizeof(char), strlen(s4), f); assert(strcmp(s4, r4)==0);
    myfseek(f, 0, SEEK_CUR); curpos(f->fd); // 48
    if(myfseek(f, 0, SEEK_SET)==-1) puts("Error in myfseek!");
    curpos(f->fd); // must be 0.
    puts("");

    myfwrite(s1, sizeof(char), strlen(s1), f);
    myfread(r2, sizeof(char), strlen(r2), f); assert(strcmp(s2, r2)==0);
    myfseek(f, 0, SEEK_CUR); curpos(f->fd); // 21

    myfread(r3, sizeof(char), strlen(r3), f); assert(strcmp(s3, r3)==0);
    myfwrite(s4, sizeof(char), strlen(s4), f);
    myfseek(f, 0, SEEK_CUR); curpos(f->fd); // 48

    if(myfseek(f, 0, SEEK_SET)==-1) puts("Error in myfseek!");
    curpos(f->fd); // must be 0.
    return 0;
}
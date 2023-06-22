#include "../mystdio.h"
#include <stdio.h>
int main() {
    char dirname[] = "output5-2.txt";
    myFILE *f = myfopen(dirname, "w+");
    char s1[] = "For Example,";
    char s2[] = "This is, ";
    char s3[] = "Program is running.";
    char s4[] = "MMMMMMMM";
    char r1[sizeof("For Example,")/sizeof(char)]="";
    char r2[sizeof("This is, ")/sizeof(char)]="";

    // The comments are my-ideal-code-specific.

    myfwrite(s1, sizeof(char), strlen(s1), f); printf("filepos: %ld\n", lseek(f->fd, 0, SEEK_CUR)); // 0 in my case.
    // output: 0. the file position is not changed in this mode.

    if(myfseek(f, 0, SEEK_CUR)==-1) puts("Error in myfseek!");
    printf("filepos: %ld\n", lseek(f->fd, 0, SEEK_CUR)); // 12

    if(myfseek(f, -strlen(s1), SEEK_CUR)==-1) puts("Error in myfseek!");
    printf("filepos: %ld\n", lseek(f->fd, 0, SEEK_CUR)); // 0
    
    if(myfread(r1, sizeof(char), strlen(s1)/sizeof(char), f)==-1) puts("Error in myfread!");
    printf("filepos: %ld\n", lseek(f->fd, 0, SEEK_CUR)); // 12 ... Happened to be already the end position of the file.
    
    printf("%s\n", r1);

    myfwrite(s2, sizeof(char), strlen(s2), f); printf("filepos: %ld\n", lseek(f->fd, 0, SEEK_CUR)); // 12 in my case.
    myfseek(f, -strlen(s2), SEEK_CUR); printf("filepos: %ld\n", lseek(f->fd, 0, SEEK_CUR)); // 12

    if(myfread(r2, sizeof(char), strlen(s2)/sizeof(char), f)==-1) puts("Error in myfread!");
    printf("filepos: %ld\n", lseek(f->fd, 0, SEEK_CUR)); // 21

    printf("%s\n", r2);

    // Testing if read-flush works well
    myfseek(f, 0, SEEK_SET); printf("filepos: %ld\n", lseek(f->fd, 0, SEEK_CUR)); // 0
    
    if(myfread(r1, sizeof(char), strlen(s1)/sizeof(char), f)==-1) puts("Error in myfread!");
    printf("filepos: %ld\n", lseek(f->fd, 0, SEEK_CUR)); // 12+9=21 (In my case)
    
    printf("%s\n", r1);

    myfseek(f, 0, SEEK_CUR); printf("filepos: %ld\n", lseek(f->fd, 0, SEEK_CUR)); // 12
    
    return 0;
}
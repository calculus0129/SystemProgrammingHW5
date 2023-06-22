#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
int main() {
    char dirname[] = "output5-2.txt";
    //int fd = open(dirname, O_CREAT | O_TRUNC | O_RDWR, 0777);
    FILE *f = fopen(dirname, "w+");
    char s1[] = "For Example,";
    char s2[] = "This is, ";
    char s3[] = "Program is running.";
    char s4[] = "MMMMMMMM";
    char r1[sizeof("For Example,")/sizeof(char)]="";
    char r2[sizeof("This is, ")/sizeof(char)]="";
    fwrite(s1, sizeof(char), strlen(s1), f); printf("filepos: %ld\n", ftell(f));
    // output: 0. the file position is not changed in this mode.

    if(fseek(f, -strlen(s1), SEEK_CUR)==-1) puts("Error in fseek!");
    printf("filepos: %ld\n", ftell(f));
    fread(r1, sizeof(char), strlen(s1)/sizeof(char), f); printf("filepos: %ld\n", ftell(f));
    printf("%s\n", r1);
    fwrite(s2, sizeof(char), strlen(s2), f); printf("filepos: %ld\n", ftell(f));
    fseek(f, -strlen(s2), SEEK_CUR); printf("filepos: %ld\n", ftell(f));
    fread(r2, sizeof(char), strlen(s2)/sizeof(char), f); printf("filepos: %ld\n", ftell(f));
    printf("%s\n", r2);
    
    return 0;
}
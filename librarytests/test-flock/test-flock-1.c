#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include "flock.h"
#include <fcntl.h>
#include <sys/stat.h>
/**
 * gcc -Wall -g -O3 -o pgm test-flock-1.c
 * myfopen 이후 프로세스를 생성하지 않고, fork() 등을 이용해 프로세스를 생성하는 부분 이후에 myfopen 을 통해 파일을 열도록 평가할 것입니다.
 * 
 * You may assume that test cases for grading will always be fork() -> myfopen(), not myfopen() -> fork().
*/
#include <sys/wait.h>
int main() {
    pid_t pid = fork(), pid2, d=0;
    int fsize=0, i=1100, r, fd;
    char c, prevc, forbidden[3];
    // Just Make a file.
    FILE* f = fopen("test-flock-1.txt", "w");
    fclose(f);
    char ctext = 'C';
    char ptext = 'P';
    char gtext = 'G';
    char nl = '\n';
    if(pid==0) { // child
        fd = open("test-flock-1.txt", O_APPEND | O_CREAT | O_WRONLY, S_IRWXU);
        while(!lockThisFileAsExclusive(fd));
        while(i--) write(fd, &ctext, sizeof(char));
        write(fd, &nl, sizeof(char));
        while(!unlockThisFile(fd));
        close(fd);
    }
    else if((pid2=fork())==0) {
        fd = open("test-flock-1.txt", O_APPEND | O_CREAT | O_WRONLY, S_IRWXU);
        while(!lockThisFileAsExclusive(fd));
        while(i--) write(fd, &ptext, sizeof(char));
        write(fd, &nl, sizeof(char));
        while(!unlockThisFile(fd));
        close(fd);
    }
    else {
        fd = open("test-flock-1.txt", O_APPEND | O_CREAT | O_WRONLY, S_IRWXU);
        while(!lockThisFileAsExclusive(fd));
        while(i--) write(fd, &gtext, sizeof(char));
        write(fd, &nl, sizeof(char));
        while(!unlockThisFile(fd));
        close(fd);
        d=1;
    }
    if(d==1) {
        wait(&pid);
        wait(&pid2);
        f = fopen("test-flock-1.txt", "r");
        fread(&prevc, sizeof(char), 1, f);
        forbidden[fsize++] = prevc;
        while(fread(&c, sizeof(char), 1, f) > 0) {
            if(c=='\n') continue;
            r=1;
            for(i=0;i<fsize;++i) if(forbidden[i] == c) {
                assert(c==prevc);
                r=0;
                break;
            }
            if(r) {
                forbidden[fsize++]=c;
            }
            prevc=c;
        }
        fclose(f);
        puts("Test-Flock-1 Passed!");
    }
    return 0;
}
#ifndef MYSTDIO_H
#define MYSTDIO_H	1

#include <stdlib.h>
#include <fcntl.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define BUFSIZE     1024    /* Default buffer size: 1024 bytes  */
#define EOF         -1      /* to indicate the end of the file. */

#define SEEK_SET    0       /* Seek from beginning of file.     */
#define SEEK_CUR    1       /* Seek from current position.      */
#define SEEK_END    2       /* Seek from end of file.           */

#define STDIN_FD    0
#define STDOUT_FD   1
#define STDERR_FD   2

typedef struct _myFILE{
	int fd;                 /* file descriptor of this file     */
    char rdbuffer[BUFSIZE]; /* read buffer of this file         */
    char wrbuffer[BUFSIZE]; /* write buffer of this file        */
    int mode_flag;          /* flag to describe opened mode     */
    int offset;             /* current position of a file (file position indicator) */
    int last_operation;     /* last operation for this file (read or write) */
} myFILE;

/*
 *  Exclusive Lock: Only 1 process can access this file at once.
 *   - I can have lock (ownership) of this file. (Use only once to get a lock)
 *   - but other processes CANNOT have the lock after I get the lock (until I unlock).
 *   - HINT: get the exclusive lock if you are a writer of this file.
 *   - returns: 1 if I can get the lock (success), otherwise 0
 */
int lockThisFileAsExclusive(myFILE *file){
    return flock(file->fd, LOCK_EX | LOCK_NB) == 0;
}

/*
 *  Shared Lock: Several processes can access this file at once.
 *   - I can have a lock (ownership) of this file. (Use only once to get a lock)
 *   - but other processes can have the lock too.
 *   - HINT: get the shared lock if you are a reader of this file.
 *   - returns: 1 if I can get the lock (success), otherwise 0
 */
int lockThisFileAsShared(myFILE *file){
    return flock(file->fd, LOCK_SH | LOCK_NB) == 0;
}

/*
 *  unlock this file after I finish to use this file.
 *  - returns: 1 if I can unlock the lock (success), otherwise 0
 */
int unlockThisFile(myFILE *file){
    return flock(file->fd, LOCK_UN | LOCK_NB) == 0;
}

myFILE *myfopen(const char *pathname, const char *mode);
myFILE *myfclose(myFILE *stream);
int myfseek(myFILE *stream, int offset, int whence);
int myfread(void *ptr, int size, int nmemb, myFILE *stream);
int myfwrite(const void *ptr, int size, int nmemb, myFILE *stream);
int myfflush(myFILE *stream);

/* ************************
 *  Implement after here. *
 * ************************ */

/* fopen mode: "r", "r+", "w", "w+", "a", "a+" */
myFILE *myfopen(const char *pathname, const char *mode){

}

myFILE *myfclose(myFILE *stream){

}

int myfseek(myFILE *stream, int offset, int whence){

}

int myfread(void *ptr, int size, int nmemb, myFILE *stream){

}

int myfwrite(const void *ptr, int size, int nmemb, myFILE *stream){

}

int myfflush(myFILE *stream){

}

#endif // mystdio.h included
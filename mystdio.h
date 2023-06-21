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
    int bufpos;             /* current buffer position */
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
int myfclose(myFILE *stream);
int myfseek(myFILE *stream, int bufpos, int whence);
int myfread(void *ptr, int size, int nmemb, myFILE *stream);
int myfwrite(const void *ptr, int size, int nmemb, myFILE *stream);
int myfflush(myFILE *stream);

/* ************************
 *  Implement after here. *
 * ************************ */

# define MIN(a, b) \
    (((a)<(b))?(a):(b))

/** [wrbuffer->file]
 * flush the wrbuffer to the file.
 * 
 * returns the number of bytes written to the file.
*/
static int _wflush(myFILE *stream) {
    int ret = write(stream->fd, stream->wrbuffer, stream->bufpos);
    stream->bufpos=0;
    return ret;
}

/** [rdbuffer -> ptr]
 * replace at most 'size' amount of bytes of 'ptr' with 'stream'->rdbuffer,
 * and reduce the buffer by substitution and reducing 'stream'->bufpos.
 * 
 * returns the number of bytes successfully moved.
*/
static int _rflush(myFILE* stream, char* ptr, int size) {
    char * c = stream->rdbuffer;
    int ret = MIN(stream->bufpos, size);
    for(size_t i=0;i<ret;++i) ptr[i] = c[i];
    if(stream->bufpos=stream->bufpos-ret) for(size_t i=ret, e=stream->bufpos; i<e; ++i) stream->rdbuffer[i-ret] = stream->rdbuffer[i];
    return ret;
}

/** [file -> rdbuffer]
 * get the file content to the rdbuffer.
 * 
 * returns the number of bytes successfully read.
*/
static int _rfill(myFILE* stream) {
    int ret=read(stream->fd, stream->rdbuffer+stream->bufpos, BUFSIZE-stream->bufpos);
    stream->bufpos += ret;
    return ret;
}

/** [ptr -> wrbuffer]
 * Copy at most size byte of data from the ptr to the wrbuffer.
 * 
 * returns the byte size of data successfully moved.
*/
static int _wfill(myFILE* stream, const char *ptr, int size) {
    int i=stream->bufpos,j=0,e=MIN(BUFSIZE-i, size);
    stream->bufpos+=e;
    for(;j<e;++j) stream->wrbuffer[i+j]=ptr[j];
    return e;
}

/* fopen mode: "r", "r+", "w", "w+", "a", "a+" */
/**
 * "r": Open text file for reading. The stream is positioned at the beginning of the file.
 * => O_RDONLY, only.
 * "r+": Open for reading and writing. The stream is positioned at the beginning of the file.
 * => O_RDWR
 * "w": Truncate file to zero length or create text file for writing. The stream is positioned at the beginning of the file.
 * => O_TRUNC | O_CREAT | O_WRONLY, 0x777
 * "w+": Open for reading and writing. The file is created if it does not exist, otherwise it is truncated. The stream is positioned at the beginning of the file.
 * => O_TRUNC | O_CREAT | O_RDWR, 0x777
 * "a": Open for appending (writing at end of file). The file is created if it does not exist. The stream is positioned at the end of the file.
 * => O_APPEND | O_CREAT | O_WRONLY, 0x777
 * "a+": Open for reading and appending (writing at end of file). The file is created if it does not exist. Output is always appended to the end of the file. POSIX is silent on what the initial read position is when using this mode, but, the stream must be positioned at the end of the file in this work.
 * => O_APPEND | O_CREAT | O_RDWR, 0x777
*/
myFILE *myfopen(const char *pathname, const char *mode) {
    myFILE* ret = malloc(sizeof(myFILE)); //(myFILE*) 
    if(strlen(mode)>2 || !strlen(mode)) return NULL;
    int mode_flag, fd;
    switch(mode[0]) {
        case 'r':
            mode_flag=0;
            if(strlen(mode)==1) fd = open(pathname, O_RDONLY);
            else { fd = open(pathname, O_RDWR); mode_flag|=1; }
            break;
        case 'w':
            mode_flag=2;
            if(strlen(mode)==1) fd = open(pathname, O_TRUNC | O_CREAT | O_WRONLY, 0x777);
            else { fd = open(pathname, O_TRUNC | O_CREAT | O_RDWR, 0x777); mode_flag|=1; }
            break;
        case 'a':
            mode_flag=4;
            if(strlen(mode)==1) fd = open(pathname, O_APPEND | O_CREAT | O_WRONLY, 0x777);
            else { fd = open(pathname, O_APPEND | O_CREAT | O_RDWR, 0x777); mode_flag|=1; }
            break;
        default:
            return NULL;
    }
    if(fd<0) return NULL;
    ret->fd = fd;
    ret->mode_flag = mode_flag;
    ret->offset = 0; // Just in case.
    ret->last_operation = 0;
    ret->bufpos = 0;
    return ret;
}

int myfclose(myFILE *stream){
    if(stream==NULL) return EOF;
    while(!lockThisFileAsExclusive(stream)); // We do not need while(!unlockThisFile(stream));, as the lock is cleared when fd is closed.
    if (myfflush(stream)) return EOF;
    while(!unlockThisFile(stream));
    if (close(stream->fd)) return EOF;
    free(stream);
    return 0;
}

int myfseek(myFILE *stream, int bufpos, int whence){
    if(stream==NULL) return EOF;
    while(!lockThisFileAsExclusive(stream));
    if (lseek(stream->fd, bufpos, whence)<0) return EOF;
    while(!unlockThisFile(stream)); //while(!unlockThisFile(stream));
    return 0;
}

int myfread(void *ptr, int size, int nmemb, myFILE *stream){
    // Check if the stream is readable.
    if(stream==NULL) return EOF;
    if(stream->mode_flag>1 && stream->mode_flag<5) return EOF;
    while(!lockThisFileAsExclusive(stream)); // Nyum Nyum
    // _wflush() if the last operation was writing.
    if(stream->mode_flag>1 && stream->last_operation==1) {
        _wflush(stream);
    }
    // ret: # of actually written bytes.
    // t: # of size of additional buffer filled.
    int siz=size*nmemb, ret=_rflush(stream, (char*)ptr, siz), i, q, r, e;

    while(ret<siz && _rfill(stream)>0) ret+=_rflush(stream, (char*)ptr+ret, siz-ret);
    if(_rfill(stream)==0) { // cannot read anymore
        ret+=_rflush(stream, (char*)ptr+ret, siz-ret);
        if(ret<siz) {
            q = ret/size, r = ret%size;
            stream->bufpos = MIN(stream->bufpos+r, BUFSIZE);
            for(i=stream->bufpos-1,e=r;i>=e;--i) stream->rdbuffer[i] = stream->rdbuffer[i-r];
            lseek(stream->fd, -r, SEEK_END);
            for(i=0, e=MIN(r, BUFSIZE);i<e;++i) {
                stream->rdbuffer[i] = ((char*)ptr)[size*q+i];
                ((char*)ptr)[size*q+i] = 0; // just in case. // consider the original data that are deleted later!
            }
            ret = q*size;
        }
    }
    stream->last_operation=0;
    while(!unlockThisFile(stream));
    //unlockThisFile(stream);//while(!unlockThisFile(stream));
    return ret;
}

int myfwrite(const void *ptr, int size, int nmemb, myFILE *stream){
    if(stream==NULL) return EOF;
    if(stream->mode_flag<2) return EOF;
    int siz = size*nmemb;
    if(siz==0) return 0;
    while(!lockThisFileAsExclusive(stream));
    // i.e. last operation was reading or nothing
    if(stream->last_operation==0 && stream->bufpos!=0) {
        lseek(stream->fd, -stream->bufpos, SEEK_CUR);
        stream->bufpos=0;
    }
    int ret=_wfill(stream, (char*)ptr, siz);
    while(ret<siz) {
        _wflush(stream);
        ret += _wfill(stream, ((char*)ptr)+ret, siz-ret);
    }
    stream->last_operation=1;
    while(!unlockThisFile(stream));//unlockThisFile(stream);
    return ret;
}

int myfflush(myFILE *stream) {
    if(stream==NULL) return EOF;
    while(!lockThisFileAsExclusive(stream));
    if(stream->last_operation==1) {
        if(_wflush(stream)==-1) {
            while(!unlockThisFile(stream));//unlockThisFile(stream);
            return -1;
        }
        stream->last_operation=0;
    }
    stream->bufpos=0;
    while(!unlockThisFile(stream));//unlockThisFile(stream);
    return 0;
}

#endif // mystdio.h included
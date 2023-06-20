#ifndef FLOCK_H
#define FLOCK_H
#include <sys/file.h>

/*
 *  Exclusive Lock: Only 1 process can access this file at once.
 *   - I can have lock (ownership) of this file. (Use only once to get a lock)
 *   - but other processes CANNOT have the lock after I get the lock (until I unlock).
 *   - HINT: get the exclusive lock if you are a writer of this file.
 *   - returns: 1 if I can get the lock (success), otherwise 0
 */
int lockThisFileAsExclusive(int fd){
    return flock(fd, LOCK_EX | LOCK_NB) == 0;
}

/*
 *  Shared Lock: Several processes can access this file at once.
 *   - I can have a lock (ownership) of this file. (Use only once to get a lock)
 *   - but other processes can have the lock too.
 *   - HINT: get the shared lock if you are a reader of this file.
 *   - returns: 1 if I can get the lock (success), otherwise 0
 */
int lockThisFileAsShared(int fd){
    return flock(fd, LOCK_SH | LOCK_NB) == 0;
}

/*
 *  unlock this file after I finish to use this file.
 *  - returns: 1 if I can unlock the lock (success), otherwise 0
 */
int unlockThisFile(int fd){
    return flock(fd, LOCK_UN | LOCK_NB) == 0;
}
#endif
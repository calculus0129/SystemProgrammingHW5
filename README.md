# SystemProgrammingHW5
Making my custom stdio with unistd.h and stdlib.h, fcntl.h, etc.


Testings:

0. Testing: myfopen(), myfclose(), myfwrite(), myfflush()
1. Test: myfopen(), myfread()
2. myfwrite() buffer auto-flushing
3. myfread() buffer using
4. myfread() + myfflush()
5. myfwrite() + myfread() + myfseek()
6. myfwrite()+myfread()+myfseek()+myfflush()
7. exceptional cases (e.g. using myfwrite() or myfread() in inadequate mode)
8. Using multiple processes
9. Using threads(optional, since we only have to maintain multiprocess concurrency.)
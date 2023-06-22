# SystemProgrammingHW5
Making my custom stdio with unistd.h and stdlib.h, fcntl.h, etc.


Testings:

0. myfopen(), myfwrite(), and myfclose().
1. myfopen(), myfread().
2. myfwrite() buffer auto-flushing
3. myfread() buffer using
4. myfread() + myfflush()
5. Just an integrated fun testing searching for primes.
    1. reading and writing in one stream.
    2. reading + writing + seeking (almost) all possible combinations.
6. exceptional cases (e.g. using myfwrite() or myfread() in inadequate mode)
7. Multiprocess Concurrency
_. Multithread Concurrency (not complete. An example from a friend.)
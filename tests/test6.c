#include "../mystdio.h"
#include <stdio.h>
#include <assert.h>

int main() {
    char nopath[]=";2o3ijroqi3jropiqj2 3oijqp23orj q2oi3rjopqj2 3op qo2i3r opq2j3rpoq23 roiqj.awrjoq2j3ir o";
    myFILE* f = myfopen(nopath, "r");
    assert(f==NULL);
    f = myfopen(nopath, "r+");
    assert(f==NULL);
    f = myfopen("output6.dat", "w");
    double pi = 3.1415926535897932384626433832795, pi2=0;
    myfwrite(&pi, sizeof(double), 1, f);
    assert(myfread(&pi, sizeof(pi), 1, f)==EOF);
    myfwrite(&pi, sizeof(double), 1, f);
    myfclose(f);
    f = myfopen("output6.dat", "r");
    myfread(&pi, sizeof(pi), 2, f);
    printf("PI is %f", pi);
    assert(pi2==0);
    myfclose(f);
    return 0;
}
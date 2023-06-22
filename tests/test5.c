// Just an integrated fun testing.
// Let's search for primes and store it using my library!

#include "../mystdio.h"
#include <stdio.h>
#include <math.h>
#include <signal.h>
#define MAX_P (unsigned long long int)1000000 // 2000000 results in segmentation fault!

myFILE *f;

void my_SIGINT_handler(int signum) {
    printf("\nReceived signal: %d\n", signum);
    myfflush(f);
    myfclose(f);
    puts("Bye-bye!");
    exit(0);
}

int main() {
    //system("clear");
    signal(SIGINT, my_SIGINT_handler);
    char filename[]="output5-primes.dat";

    printf("Finding Prime File %s ... ", filename);
    f = myfopen(filename, "r");
    unsigned long long int size = 8, wantsize, np, i, r;
    unsigned long long int primes[MAX_P]={2, 3, 5, 7, 11, 13, 17, 19};
    if(f==NULL) {
        puts("Find Failed!\nGenerating new primes data... ");
    } else {
        printf("File Found!\nLoading primes data...");
        myfread(&size, sizeof(size), 1, f);
        myfread(&primes, sizeof(primes[0]), size, f);
    }
    myfclose(f);
    puts("Complete!");
    // This is unexpectedly important to set the mode like this: "w"!! Or unexpected consequences may happen!!
    f = myfopen(filename, "w");
    myfwrite(&size, sizeof(size), 1, f);
    myfwrite(primes, sizeof(primes[0]), size, f);
    myfseek(f, 0, SEEK_END);
    char m;
    while(1) {
        puts("Hello! Welcome to Jaehyun's prime research factory!\n");
        puts("1: search for more primes / see the primes searched so far.");
        puts("else: Bye-bye!");
        scanf(" %c", &m);
        if(m!='1') break;
        while(1) {
            puts("Currently Known Primes: ");
            printf("(%llu)\n", size);
            for(i=0;i<size;++i) printf("%llu ", primes[i]);
            printf("\n(%llu)\n", size);
            puts("Do you want to find more?\n1: Yes,\nelse: No");
            scanf(" %c", &m);
            if(m!='1') break;
            while(1) {
                printf("How much do you want to find in total? (MAX: %llu)\n(put 0 to exit.)\n", MAX_P);
                scanf("%llu", &wantsize);
                if(!wantsize) break;
                puts("Searching.... ");
                np=primes[size-1];
                while(size<wantsize && size<MAX_P) {
                    np+=2;
                    i=r=0;
                    while(primes[i]*primes[i]<=np && i<size) {
                        if(np%primes[i++]==0) {
                            r=1;
                            break;
                        }
                    }
                    if(r) continue;
                    primes[size++]=np;
                    myfwrite(&np, sizeof(np), 1, f);
                    myfseek(f, 0, SEEK_SET);
                    myfwrite(&size, sizeof(size), 1, f);
                    myfseek(f, 0, SEEK_END);
                    printf("%llu\n", np);
                }
                puts("Search Complete!");
            }
        }
    }
    myfclose(f);
    puts("Bye-bye!");

    return 0;
}
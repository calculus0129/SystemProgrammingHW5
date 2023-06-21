// myfwrite() buffer auto-flushing
/*#include "../mystdio.h"
int main() {
    myFILE *f = myfopen("output2.txt", "w");
    
    char intro[] = "Hello! I'm gonna mark everything into yee!\n"; // 43 letters
    myfwrite(intro, sizeof(char), strlen(intro), f);
    write(1, intro, strlen(intro)*sizeof(char));
    char yee[] = "Yee! Yee! Yee! Yee! Yee! Yee! Yee! Yee! Yee! Yee! Yee! Yee! Yee! Yee! Yee! Yee! Yee! Yee! Yee! Yee!\n";
    // ("Yee!" * 20 + ' '*19) * 10 is almost 1024.
    // Considering the intro, this suffices to auto-flush the wrbuffer.
    int i=10;
    while(i--) myfwrite(yee, sizeof(char), strlen(yee), f);

    double pi = 3.1415926535897932384626433832795;
    double pis[] = {pi, pi, pi, pi, pi, pi, pi, pi, pi, pi};
    char intro2[] = "I wonder how PI is represented in memory...!\n\n";
    write(1, intro2, strlen(intro2)*sizeof(char));
    i=10;
    while(i--) {
        myfwrite(&pi, sizeof(pi), 1, f);
        myfwrite("\n", 1, 1, f);
    }
    myfwrite(pis, sizeof(pi), 10, f);
    myfclose(f);

    return 0;
}
*/

#include <stdio.h>
#include <unistd.h>
int main() {
    FILE *f = fopen("output2.txt", "w");
    
    char intro[] = "Hello! I'm gonna mark everything into yee!\n"; // 43 letters
    fwrite(intro, sizeof(char), strlen(intro), f);
    write(1, intro, strlen(intro)*sizeof(char));
    char yee[] = "Yee! Yee! Yee! Yee! Yee! Yee! Yee! Yee! Yee! Yee! Yee! Yee! Yee! Yee! Yee! Yee! Yee! Yee! Yee! Yee!\n";
    // ("Yee!" * 20 + ' '*19) * 10 is almost 1024.
    // Considering the intro, this suffices to auto-flush the wrbuffer.
    int i=10;
    while(i--) fwrite(yee, sizeof(char), strlen(yee), f);

    double pi = 3.1415926535897932384626433832795;
    double pis[] = {pi, pi, pi, pi, pi, pi, pi, pi, pi, pi};
    char intro2[] = "I wonder how PI is represented in memory...!\n\n";
    write(1, intro2, strlen(intro2)*sizeof(char));
    i=10;
    while(i--) {
        fwrite(&pi, sizeof(pi), 1, f);
        fwrite("\n", 1, 1, f);
    }
    fwrite(pis, sizeof(pi), 10, f);
    fclose(f);

    return 0;
}

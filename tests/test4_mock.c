#include <stdio.h>
int main() {
    int t, i=10*20;
    char c;
    char yees[5];
    double pi, pis[7];
    FILE *f = fopen("output2.txt", "r");
    while((t=fread(&c, 1, 1, f))!=0 && c!='\n') {
        printf("%c", c);
    }
    puts("");
    //fflush(f);
    while((t=fread(yees, 5, 1, f))!=0 && i--) {
        printf("%s", yees);
    }
    i=10;
    while((t=fread(&pi, sizeof(double), 1, f))!=0 && i--) {
        fread(&c, sizeof(char), 1, f);
        //fflush(f);
        printf("%f%c", pi, c);
    }
    puts("");
    i=10;
    int j;
    // Testing fread()'s reading ability.
    while((t=fread(pis, sizeof(double), 7, f))!=0 && i--) {
        //fflush(f);
        j=7;
        printf("%02d elements: ", t);
        //fflush(f);
        while(j--) printf("%f", pis[j]);
        puts("");
        //fflush(f);
    }
    fclose(f);
    return 0;
}
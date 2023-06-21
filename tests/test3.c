// myfread() buffer using
#include "../mystdio.h"

int main() {
    myFILE *f = myfopen("output2.txt", "r");
    char content[2048]="";
    myfread(content, 1, 2047, f);
    write(1, content, 2047);
    myfclose(f);
    return 0;
}
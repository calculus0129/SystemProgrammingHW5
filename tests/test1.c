#include "../mystdio.h"

int main() {
    myFILE *f = myfopen("input1.txt", "r");
    char buf[1024]="";
    myfread(buf, 1, 1024, f);
    write(1, buf, 1024);
    
    return 0;
}
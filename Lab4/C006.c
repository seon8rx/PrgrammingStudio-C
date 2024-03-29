#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "member.h"

int main(void){
    Member* mlist[SIZE];
    int no, menu;
    no = createData(mlist);

    while(1){
        printf("\n[1. List] [2. Modify] [3. Delete] [0. Exit]\n|> Enter a menu >> ");
        scanf("%d", &menu);

        if(menu==1) readMembers(mlist, no);
        else if(menu==2) printf("\n");
        else break;
    }

    return 0;
}
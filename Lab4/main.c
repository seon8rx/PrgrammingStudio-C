#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crud_member.h"

int main(void){
    Member* mlist[SIZE];
    int no, menu;
    no = createData(mlist);

    while(1){
        printf("\n[1. List] [2. Modify] [3. Delete] [4. Search] [5. Save] [6. Report] [7. Random Pick] [0. Exit]\n>> Enter a menu >> ");
        scanf("%d", &menu);

        if(menu==1) readMembers(mlist, no);
        else if(menu==2) updateMember(mlist, no);
        else if(menu==3) no = deleteMember(mlist, no);
        else if(menu==4) searchMember(mlist, no);
        else if(menu==5) saveInfo(mlist, no);
        else if(menu==6) makeReport(mlist,no);
        else if(menu==7) pickupRandomMember(mlist, no);
        else break;
    }

    return 0;
}
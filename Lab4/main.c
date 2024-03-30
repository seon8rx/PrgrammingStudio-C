#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crud_member.h"

int main(void){
    Member* mlist[SIZE];
    int no, menu;
    no = createData(mlist);

    while(1){
        printf("\n[1. List] [2. Modify] [3. Add] [4. Delete] [5. Search] [6. Save] [7. Report] [8. Random Pick] [0. Exit]\n>> Enter a menu >> ");
        scanf("%d", &menu);

        if(menu==1) readMembers(mlist, no);
        else if(menu==2) updateMember(mlist, no);
        else if(menu==3) no = addNewMember(mlist, no);
        else if(menu==4) no = deleteMember(mlist, no);
        else if(menu==5) searchMember(mlist, no);
        else if(menu==6) saveInfo(mlist, no);
        else if(menu==7) makeReport(mlist,no);
        else if(menu==8) pickupRandomMember(mlist, no);
        else break;
    }

    return 0;
}
#include "member.h"

char GENDER[2][30] = {"MALE", "FEMALE"};

int createData(Member* m[]){
    int count=0;
    FILE* file;

    file=fopen("member_list.txt", "r");
    while(!feof(file)){
        m[count] = (Member*)malloc(sizeof(Member));
        int r = fscanf(file, "%s %d %d %s %s", m[count]->name, &(m[count]->age), &(m[count]->g), m[count]->email, m[count]->password);
        if(r < 5) break;
        count++;
    }
    fclose(file);
    printf("\n> THE INFORMATION FOR \"%d MEMBERS\" IS READY.", count);
    return count;
}

void readMembers(Member* m[], int size){
    printf("\n");
    for(int i=0; i<size; i++){
        printf("[%2d] name: %20s, age: %d, gender: %6s : e-mail: %s, pw: ", i+1, m[i]->name, m[i]->age, GENDER[m[i]->g], m[i]->email);
        for(int p=0; p<strlen(m[i]->password); p++){
            printf("*");
        }
        printf("\n");
	}
}

void updateMember(Member* m[], int size){
    printf("> Modify the informatioin for a member\n");
	printf("> Enter a number of member in the list > ");
	int no_mem = 0;
	scanf("%d", &no_mem);

	if(no_mem<=0 || no_mem>=size+1){
		printf("> %d is not in the list.\n", no_mem);
		return;
    }
    
    printf("Information of the member > ");
    printf("[%d] name: %20s, age: %d, gender: %6s : e-mail: %s, pw: ", no_mem, m[no_mem-1]->name, m[no_mem-1]->age, GENDER[m[no_mem-1]->g], m[no_mem-1]->email);
    for(int p=0; p<strlen(m[no_mem-1]->password); p++){
        printf("*");
    }
    printf("\n");

    printf("> Enter his/her NAME info. > ");
	scanf("%s", m[no_mem-1]->name);
	printf("> Enter his/her AGE info. > ");
	scanf("%d", &(m[no_mem-1]->age));
	printf("> Enter his/her GENDER info. (MALE: 0, FEMALE: 1) > ");
    scanf("%d", &(m[no_mem-1]->g));
    printf("> Enter his/her E-MAIL info. > ");
    scanf("%s", m[no_mem-1]->email);
    printf("> Enter his/her PASSWORD info. > ");
    scanf("%s", m[no_mem-1]->password);

	printf("\n> Member info. is modified.\n");
}

int deleteMember(Member* m[], int size){
    int no_mem, yesno;
    printf("> Delete information for a member\n");
    printf("> Enter a number of member in the list > ");
    scanf("%d", &no_mem);

    if(no_mem<=0 || no_mem>=size+1){
		printf("> %d is not in the list.\n", no_mem);
		return size;
    }
        
    printf("Information of the member > ");
    printf("[%d] name: %20s, age: %d, gender: %6s : e-mail: %s, pw: ", no_mem, m[no_mem-1]->name, m[no_mem-1]->age, GENDER[m[no_mem-1]->g], m[no_mem-1]->email);
    for(int p=0; p<strlen(m[no_mem-1]->password); p++){
        printf("*");
    }
    printf("\n");

    printf("> Do you want to delete this information? (1:Yes 0:No) > ");
    scanf("%d", &yesno);
	if(yesno==0){
		printf("> Canceled.\n");
		return size;
    }else{
        if(no_mem==size){
            printf("> Information is deleted.\n");
            return size-1;
        }else{
            for(int d=no_mem-1; d<size-1; d++){
                strcpy(m[d]->name, m[d+1]->name);
                m[d]->age = m[d+1]->age;
                m[d]->g = m[d+1]->g;
                strcpy(m[d]->email, m[d+1]->email);
                strcpy(m[d]->password, m[d+1]->password);
            }
        }
        printf("> Information is deleted.\n");
        return size-1;
    }
}
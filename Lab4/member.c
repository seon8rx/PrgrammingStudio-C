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
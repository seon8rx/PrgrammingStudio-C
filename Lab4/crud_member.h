#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 30

char GENDER[2][30];

typedef struct member{
    char name[20];
    int age;
    int g;

    char email[100];
    char password[20];
} Member;

int createData(Member* m[]); 
void readMembers(Member* m[], int size);
void updateMember(Member* m[], int size);
int deleteMember(Member* m[], int size);
void provideInfo(Member* m[], int i);
void searchMember(Member* m[], int size);
void saveInfo(Member* m[], int size);
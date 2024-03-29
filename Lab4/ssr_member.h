#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define SIZE 30

char GENDER[2][30];

typedef struct member{
    char name[20];
    int age;
    int g;

    char email[100];
    char password[20];
} Member;

void searchMember(Member* m[], int size);
void saveInfo(Member* m[], int size);
void makeReport(Member* m[], int size);
void pickupRandomMember(Member* m[], int size);

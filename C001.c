#include <stdio.h>

int main(){
    int size;
    printf("SIZE ? : ");
    scanf("%d", &size);

    int blank_1;
    int blank_2;

    blank_1=0;
    blank_2 = 2*size - 2;
    for(int i=0; i < size; i++){
        for(int j=0; j < blank_1; j++){
            printf(" ");
        }
        printf("*");
        for(int j=0; j < blank_2; j++){
            printf(" ");
        }
        printf("*\n");
        blank_1++;
        blank_2 = blank_2 - 2;
    }

    for(int i=0; i < size; i++){
        for(int j=0; j<2*size; j++){
            printf("*");
        }
        printf("\n");
    }

    int blank = 0;
    int star = 2*size;
    for(int i=0; i < size; i++){
        for(int j=0; j < blank; j++){
            printf(" ");
        }
        for(int j=0; j < star; j++){
            printf("*");
        }
        printf("\n");
        blank++;
        star = star - 2;
    }

    for(int i=0; i < 2*size; i++){
        printf("*");
    }

    printf("\n");

    return 0;
}

#include <stdio.h>

int main(){
    int person[4][3];
    int sum[3]={0};
    float ratio[3]={0.0};

    printf("남학생층 점호\n");
    for(int i=0; i<2; i++){
        for(int j=0; j<3; j++){
            printf("%d0%d호실 점호 인원 > ", i+1, j+1);
            scanf("%d", &person[i][j]);
            sum[0] += person[i][j];
        }
    }

    printf("여학생층 점호\n");
    for(int i=2; i<4; i++){
        for(int j=0; j<3; j++){
            printf("%d0%d호실 점호 인원 > ", i+1, j+1);
            scanf("%d", &person[i][j]);
            sum[1] += person[i][j];
        }
    }

    sum[2] = sum[0] + sum[1];

    ratio[0] = 100*sum[0]/24.0;
    ratio[1] = 100*sum[1]/24.0;
    ratio[2] = 100*sum[2]/48.0;

    printf("점호 결과\n");
    printf("남학생 : %d명/24명 (%.1f%%)\n", sum[0], ratio[0]);
    printf("여학생 : %d명/24명 (%.1f%%)\n", sum[1], ratio[1]);
    printf("전체 : %d명/48명 (%.1f%%)\n", sum[2], ratio[2]);
}
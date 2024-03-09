#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int findRoom(int persons[5]); // 5개의 호실 중 빈 베드가 있는 방을 찾아낸다. (리턴값 1~5)
void printReport(char mn[10][20], int mr[10], int mc, char wn[10][20], int wr[10], int wc); // 배정 결과를 출력한다.

int main(){
	char mnames[10][20]; // 남학생명단(최대 10명)
	int mroom[10];		// 남학생명단별 호실 배정 목록
	char wnames[10][20]; // 여학생명단(최대 10명)
	int wroom[10];		// 여학생명단별 호실 배정 목록
	int person[2][5]={0};   // 2개 층별 5개 호실의 배정 인원 수 
	int mcount=0, wcount=0; // 인원 합계 (남, 여)
	int menu;

	srand(time(0));
	printf("===========================================\n");
	printf("생활관 호실 배정 프로그램\n");
	printf("===========================================\n");
	while(1){
		printf("메뉴 : 1.남학생 등록 2.여학생 등록 0.종료 > ");
		scanf("%d", &menu);
		if(menu==0) break;
		else if(menu==1) {
			if(mcount>=10) {
				printf("정원 초과입니다. 등록불가!\n");
				continue;
			}
			printf("학생 이름은? > ");
			scanf("%s", mnames[mcount]);
			int roomno = findRoom(person[0]);
			mroom[mcount] = 100+roomno;
			printf("%s 학생 %d호실 배정되었습니다.\n", mnames[mcount], mroom[mcount]);
			mcount++;
		}
		else if(menu==2) {
			if(wcount>=10) {
				printf("정원 초과입니다. 등록불가!\n");
				continue;
			}
			printf("학생 이름은? > ");
			scanf("%s", wnames[wcount]);
			int roomno = findRoom(person[1]);
			wroom[wcount] = 200+roomno;
			printf("%s 학생 %d호실 배정되었습니다.\n", wnames[wcount], wroom[wcount]);
			wcount++;
		}
	}

	printf("===========================================\n");
	printf("생활관 호실 배정 결과는 다음과 같습니다.\n");
	printf("===========================================\n");
	printReport(mnames, mroom, mcount, wnames, wroom, wcount);

	return 0;
}

int findRoom(int persons[5]){
	//2개 층별 5개 호실의 배정 인원 수를 다루는 배열을 받는다
	//방이 다 찼는지 안 찾는지로 나누어 확인한다
	//랜덤하게 1~5 정수값을 호수로 받는다.
	//만약 해당 호실에 2명이 다 찼다면 (no[]는 0값을 가진다.)
	//만약 해당 호실에 자리가 있다면, 2개 층별 5개 호실의 배정 인원 수를 다루는 배열의 해당 부분의 값을 1 올린다
	//해당 호실 값을 리턴한다.

    int no[5]={0};

    for(int i=0; i<5; i++){
        if(persons[i] != 2) no[i] = 1;
        else no[i] = 0;
    }
	
	int r;
    while(1){
		int a = rand()%5+1;
        if(no[a-1] == 1) {
			persons[a-1]++;
			r=a;
			break;
			}
    }
    
    return r;
}

void printReport(char mn[10][20], int mr[10], int mc, char wn[10][20], int wr[10], int wc){
// 남학생명단을 for를 이용하여 배열에 들어있는 남학생들의 이름과 호실을 한줄씩 출력한다
// 여학생명단을 for를 이용하여 배열에 들어있는 여학생들의 이름과 호실을 한줄씩 출력한다
//호실별 배정 명단은 while 안에 for를 이용하여 출력한다
//101호 부터 오름차순으로 201호 부터 오름차순으로 조건문을 이용하여 찾아내고
//해당 index의 학생 명단을 출력한다.

	printf("남학생 명단 (%d명)\n", mc);
	for(int i=0; i<mc; i++){
		printf("%d. %s [%d호]\n", i+1, mn[i], mr[i]);
	}
	printf("\n");


	printf("여학생 명단 (%d명)\n", wc);
	for(int i=0; i<wc; i++){
		printf("%d. %s [%d호]\n", i+1, wn[i], wr[i]);
	}
	printf("\n");


	printf("호실별 배정 명단\n");
	for(int i=0; i<mc; i++){
		if(101+i<106) printf("%d호 : ", 101+i);
		int count=0;
		while(count<mc){
			if(mr[count]==101+i) printf("%s ", mn[count]);
			count++;
		}
		if(i<5) printf("\n");
	}
	for(int i=0; i<wc; i++){
		if(201+i<206) printf("%d호 : ", 201+i);
		int count=0;
		while(count<mc){
			if(wr[count]==201+i) printf("%s ", wn[count]);
			count++;
		}
		if(i<5) printf("\n");
	}
	
}

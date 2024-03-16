// 22100110 김성규

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct st_class{
	int code;		// class code
	char name[30]; 	// class name
	int unit;		// credites
	int grading;	// grading (1:A+~F, 2:P/F)
};

char kname[2][10] = {"A+~F", "P/F"}; // String for grading

// Functions provided
int loadData(struct st_class* c[]); // Load all class list from data file.
void printAllClasses(struct st_class* c[], int csize); // Print all class list

// Functions for modifying
int addNewClass(struct st_class* c[], int csize); // Add a class into the list
void editClass(struct st_class* c[], int csize); // Modify a class in the list
void findClasses(char* name, struct st_class* c[], int csize); // Search a class by name from the list

// Functions for making
int applyMyClasses(int my[], int msize, struct st_class* c[], int csize); // Apply a class
void printMyClasses(int my[], int msize, struct st_class* c[], int csize); // Print my classes
void saveMyClass(int my[], int msize, struct st_class* c[], int csize); // Save my classes
void saveAllClasses(struct st_class* c[], int csize); // Save all class list


int main(void) {
	int no;	// menu number 
	struct st_class* classes[50]; // Class list (max. 50 classes)

	int myclass[10]; // My classes (max. 10 classes of code)
	int mycount = 0; // Amount of my classes

	srand(time(0));
	int count = loadData(classes);
	printf("> Load %d classes.\n", count);

	while(1){
		printf("\n> Menu 1.List 2.Add 3.Modify 4.Search 5.Apply 6.My classes 7.Save 0.Quit\n");
		printf(">> Menu? > ");
		scanf("%d", &no);

		if(no == 1){ 
			printf("> 1.Class list (%d classes)\n", count);
			printAllClasses(classes, count);
		}
		else if(no == 2){ 
			printf("> 2.Add a Class\n");
			count = addNewClass(classes, count);
		}
		else if(no == 3){ 
			printf("> 3.Modify a Class\n");
			editClass(classes, count);
		}
		else if(no == 4){
			printf("> 4.Search a Class\n");
			printf(">> Enter class name > ");
			char name[30];
			scanf("%s", name);
			findClasses(name, classes, count);
		}
		else if(no == 5){
			printf("> 5.Apply a class\n");
			mycount = applyMyClasses(myclass, mycount, classes, count);
			printf("%d classes has been applied.\n", mycount);
		}
		else if(no == 6){
			printf("> 6.My classes\n");
			printMyClasses(myclass, mycount, classes, count);
		}
		else if(no == 7){
			printf("> 7.Save\n");
			saveMyClass(myclass, mycount, classes, count);
			printf("\n> All my classes ware saved to my_classes.txt.\n");
			saveAllClasses(classes, count);
			printf("\n> All of class list ware saved to classes.txt.\n");
		}
		else break;
	}
	return 0;
}

int loadData(struct st_class* c[]){
	// 파일에서 읽어와야하니 파일을 읽기 모드로 열어 파일의 마지막(EOF)까지
	// 반복문을 통해 50개까지 가능한 struct 포인터를 동적으로 할당하여 읽어들인다.
	// 조건문을 통해 코드, 과목명, 학점, 점수체계의 대한 정보가 모두 없을 경우에도 반복문을 종료한다.
	// 열었던 파일을 닫으며 함수가 종료된다.
	int count=0;
	FILE* file;

	file=fopen("classes.txt", "r");
	while(!feof(file)){
		c[count] = (struct st_class*)malloc(sizeof(struct st_class));
		int r = fscanf(file, "%d %s %d %d", &(c[count]->code),c[count]->name, &(c[count]->unit), &(c[count]->grading));
		if(r < 4) break;
		count++;
	}
	fclose(file);
	return count;
}

void printAllClasses(struct st_class* c[], int csize){
	// 받아 온 struct 포인터와 읽어들인 과목의 총 갯수를 이용하여
	// 반복문을 통해 읽어들인 모든 과목을 화면에 출력한다.
	for(int i=0; i<csize; i++){
		printf("[%d] %s [credit %d - %s]\n",c[i]->code, c[i]->name, c[i]->unit, kname[c[i]->grading-1]);
	}
}

void saveAllClasses(struct st_class* c[], int csize){
	// 저장을 위한 파일을 선언하고 쓰기 모드로 열어준다.
	// 반복문을 통해 양식에 맞춰 받아 온 struct 포인터와 과목에 대한 정보를 csize만큼 모두 파일에 입력한 후
	// 파일을 닫아준다.
	FILE* file;
	file = fopen("classes.txt", "w");
	for(int i=0; i<csize; i++){
		fprintf(file, "%d %s %d %d\n",c[i]->code, c[i]->name, c[i]->unit, c[i]->grading);
	}
	fclose(file);	
}

void findClasses(char* name, struct st_class* c[], int csize){
	// name으로 받아온 정보를 반복문을 통해 과목 전체 리스트에서 strstr을 사용하여 찾아내고
	// 찾아낼때마다 해당 과목의 정보를 출력하고 count를 ++하여 마지막에 최종적으로 몇개의 과목이
	// 찾아졌는지 출력한다
	int count = 0;

	printf("Searching (keyword : %s)\n", name);
	for(int i=0; i<csize; i++){
		if(strstr(c[i]->name, name)){
			printf("[%d] %s [credit %d - %s]\n",c[i]->code, c[i]->name, c[i]->unit, kname[c[i]->grading-1]);
			count++;
		}
	}
	printf("%d classes found.\n", count);
}

// You must complete these functions.
int addNewClass(struct st_class* c[], int csize){
// Caution : Don't allow the duplicate class code.
// You must complete this function.
	// 새로 과목을 추가하기 위해 struct 포인터를 동적으로 선언해준다
	// 반복문을 통해 추가하고자하는 과목코드를 입력 받고
	// 입력을 받으면 이미 목록에 있는 전체 과목의 코드와 비교를 하고
	// 일치하는 것이 있다면 경고문구를
	// 일치하지 않을 때 마다 ww변수의 값을 1씩 올린다
	// 만약 일치하는 것이 없다면 ww의 값은 csize와 같을 것이고
	// 조건문을 통하여 ww==csize일 때 반복문을 종료하고
	// 나머지 정보들을 입력 받고 c[csize-1]에 마지막 과목들의
	// 정보가 있었으니 c[csize]에 p에 입력 받았던 정보를 넘기고
	// csize를 1올리며 리턴한다.

	struct st_class* p = (struct st_class*)malloc(sizeof(struct st_class));
	
	while(1){
		printf(">> code number > ");
		scanf("%d", &(p->code));
		int ww=0;
		for(int i=0; i<csize; i++){
			if(p->code==c[i]->code) printf(">> Code duplicated! Retry.\n");
			else ww++;
		}

		if(ww==csize) break;

	}

	printf(">> class name > ");
	scanf("%s", p->name);
	printf(">> credits > ");
	scanf("%d", &(p->unit));
	printf(">> grading (1: A+~F, 2: P/F) > ");
	scanf("%d", &(p->grading));

	c[csize] = p;
	return csize+1;
}

void editClass(struct st_class* c[], int csize){
	// 수정하고자하는 과목의 정보를 일시적으로 가지고 있기 위한 struct 포인터를 선언해주고
	// 수정하고자하는 과목의 코드를 입력받는다
	// while반복문안에서
	// for 반복문을 통해 과목 전체 리스트에서 입력받은 과목의 코드가 있는지 확인한다
	// 있을 경우 code_check를 1로 바꾸어주고
	// 함수 안에서 선언한 struct 포인터에 해당 과목의 정보들을 넘겨준다.
	// 다음 조건문으로 code_check가 1일 경우 while 반복문을 종료하고
	// 0일경우 해당 코드가 존재하지 않으니 경구문구를 출력하고
	// 다시 while문에 처음으로 돌아가 확인한다.
	
	struct st_class* p;
	int code;
	printf(">> Enter a code of class > ");
	scanf("%d", &code);

	while(1){
		int code_check = 0;

		for(int i = 0; i<csize; i++){
			if(code == c[i]->code){
				code_check=1;
				p=c[i];
			} 
		}

		if(code_check==0){
			printf("> No such class.\n");
			printf(">> Enter a code of class > ");
			scanf("%d", &code);
		}else if(code_check==1) break;

	}
	
	printf("> Current: [%d] %s [credits %d - %s]\n",p->code, p->name, p->unit, kname[p->grading-1]);
	printf("> Enter new class name > ");
	scanf("%s", p->name);
	printf("> Enter new credits > ");
	scanf("%d", &(p->unit));
	printf("> Enter new grading(1:Grade, 2: P/F) > ");
	scanf("%d", &(p->grading));

	printf("> Modified.\n");

}


// You must make all these functions.

int applyMyClasses(int my[], int msize, struct st_class* c[], int csize){
	// while 반복문을 통해 apply할 과목의 코드를 입력받고
	// for 반복문을 통해 우선 이미 신청되어있는 코드값인지 확인한다
	// 다음 for반복문을 통해 이미 위에서 신청되어있는 코드값으로 나오면 바로 break하고
	// 아니라면 전체 과목 리스트에서 입력받은 코드 값을 찾아서 확인한 후 입력받은 코드값을 my[]에 넣어주고
	// 해당 과목의 정보들을 화면에 출력한다.
	// 조건문을 통해 상황에 맞는 경고문 혹은 추가로 신청을 할 것인지를 확인하여 입력값을 받고
	// 반복문을 실행하거나, 혹은 반복문을 나와 추가한 과목의 수(msize)를 리턴한다.
	int code;
	int repeat=1;

	while(repeat==1){
		printf(">> Enter a class code > ");
		scanf("%d", &code);
		
		int code_check = 0;

		for(int j = 0; j<msize; j++){
			if(code==my[j]) code_check=2;
		}

		for(int i = 0; i<csize; i++){
			if(code_check==2) break;			

			if(code == c[i]->code){
				code_check=1;
				my[msize]=code;
				msize++;
				printf("[%d] %s [credit %d - %s]\n",c[i]->code, c[i]->name, c[i]->unit, kname[c[i]->grading-1]);
			}
		}

		if(code_check==0){
			printf("> No such class.\n");
		}else if(code_check==1){
			printf(">> Add more?(1:Yes 2:No) > ");
			scanf("%d", &repeat);
		}
		else if(code_check==2){
			printf(">> Already applied this class! Retry.\n");
		}
	}

	return msize;
}

void printMyClasses(int my[], int msize, struct st_class* c[], int csize){
	// 임시로 정보를 저장할 struct를 mszie만큼 만들어준 후
	// 이중 반복문을 통해
	// 신청한 과목의 코드를 전체 과목리스트에서 찾아
	// 해당 정보들을 임시로 선언한 struct에 저장해준다
	// 그런 후 반복문을 통해 신청한 코드를 통해 가져온 정보들을 모두 출력하고 총 몇학점인지를 계산하여 마지막에 출력한다
	struct st_class temp[msize];

	for(int a=0; a<msize; a++){
		for(int b=0; b<csize; b++){
			if(my[a]==c[b]->code){
				temp[a].code=c[b]->code;
				strcpy(temp[a].name, c[b]->name);
				temp[a].unit=c[b]->unit;
				temp[a].grading=c[b]->grading;
			}
		}
	}

	int credit_sum = 0;

	for(int i=0; i<msize; i++){
		printf("%d. [%d] %s [credit %d - %s]\n", i+1, temp[i].code, temp[i].name, temp[i].unit, kname[temp[i].grading-1]);
		credit_sum += temp[i].unit;
	}
	printf("All : %d credits\n", credit_sum);
}

void saveMyClass(int my[], int msize, struct st_class* c[], int csize){
	// 신청한 과목들을 텍스트파일에 저장하기 위해
	// 파일을 선언하고 쓰기 모드로 파일을 열어준다
	// 내가 신청한 과목의 코드를 토대로 전체 과목 리스트에서 과목에 대한 정보들을 찾아와
	// 임시로 선언한 struct에 모두 넣어주고 msize 만큼 반복한다
	// 반복문을 통해 찾아 온 정보들을 모두 파일에 입력해주고
	// 총 몇학점인지, 레터 그레이드 과목과 pf 과목의 갯수를 
	// 반복문에서 파일에 입력하며 같이 구하고 마지막에 파일에 입력한다.
	// 모두 완료한 파일을 닫는다
	FILE* file;
	file=fopen("my_classes.txt", "w");
	struct st_class temp[msize];
	int credit_sum = 0;

	for(int a=0; a<msize; a++){
		for(int b=0; b<csize; b++){
			if(my[a]==c[b]->code){
				temp[a].code=c[b]->code;
				strcpy(temp[a].name, c[b]->name);
				temp[a].unit=c[b]->unit;
				temp[a].grading=c[b]->grading;

			}
		}
	}

	int grade_count=0;
	int pf_count=0;
	for(int i=0; i<msize; i++){
		fprintf(file, "%d. [%d] %s [credit %d - %s]\n", i+1, temp[i].code, temp[i].name, temp[i].unit, kname[temp[i].grading-1]);
		credit_sum += temp[i].unit;
		if(temp[i].grading==1) grade_count++;
		else pf_count++;
	}
	fprintf(file, "All : %d classes, %d credits (A+~F %d credits, P/F %d credits)\n", msize, credit_sum, grade_count, pf_count);

	fclose(file);
}
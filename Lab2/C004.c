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
	for(int i=0; i<csize; i++){
		printf("[%d] %s [credit %d - %s]\n",c[i]->code, c[i]->name, c[i]->unit, kname[c[i]->grading-1]);
	}
}

void saveAllClasses(struct st_class* c[], int csize){
	FILE* file;
	file = fopen("classes.txt", "w");
	for(int i=0; i<csize; i++){
		fprintf(file, "%d %s %d %d\n",c[i]->code, c[i]->name, c[i]->unit, c[i]->grading);
	}
	fclose(file);	
}

void findClasses(char* name, struct st_class* c[], int csize){
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
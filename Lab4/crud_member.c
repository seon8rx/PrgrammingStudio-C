#include "crud_member.h"

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
    printf("\n>> THE INFORMATION FOR \"%d MEMBERS\" IS READY. <<", count);
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
    printf("\n> Modify the informatioin for a member\n");
	printf("> Enter a number of member in the list > ");
	int no_mem = 0;
	scanf("%d", &no_mem);

	if(no_mem<=0 || no_mem>=size+1){
		printf("> %d is not in the list.\n", no_mem);
		return;
    }
    
    printf("\n>>> Information of the member\n");
    provideInfo(m, no_mem);

    printf("\n> Enter his/her NAME info. > ");
	scanf("%s", m[no_mem-1]->name);
	printf("> Enter his/her AGE info. > ");
	scanf("%d", &(m[no_mem-1]->age));
	printf("> Enter his/her GENDER info. (MALE: 1, FEMALE: 2) > ");
    scanf("%d", &(m[no_mem-1]->g));
    (m[no_mem-1]->g)--;
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
        
    printf("\n>>> Information of the member\n");
    provideInfo(m, no_mem);

    printf("\n> Do you want to delete this information? (1:Yes 2:No) > ");
    scanf("%d", &yesno);
	if(yesno==2){
		printf("> Canceled.\n");
		return size;
    }else if(yesno==1){
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
    }else{
        printf("%d is not in your options.\n", yesno);
        return size;
    }
}

void provideInfo(Member* m[], int i){
    printf(">>> [%d] name: %20s, age: %d, gender: %6s, e-mail: %s, pw: ", i, m[i-1]->name, m[i-1]->age, GENDER[m[i-1]->g], m[i-1]->email);
    for(int p=0; p<strlen(m[i-1]->password); p++){
        printf("*");
    }
    printf("\n");
}

void searchMember(Member* m[], int size){
    printf("> Search member(s)\n");
    printf("> Choose one (1:by name, 2:by age, 3:by gender) > ");
    int input;
    scanf("%d", &input);

    int r=0;

    if(input == 1){
        char search[20];
        printf("> Enter a name > ");
        scanf("%s", search);
        printf("> Result : \n");

        for(int i=0; i<size; i++){
            if(strstr(m[i]->name, search)){
                provideInfo(m, i+1);
                r++;
            }
        }
    }else if(input == 2){
        int search;
        printf("> Enter age > ");
        scanf("%d", &search);
        printf("> Result : \n");

        for(int i=0; i<size; i++){
            if(m[i]->age==search){
                provideInfo(m, i+1);
                r++;
            }
        }
    }else if(input == 3){
        int search;
        printf("> Enter gender type (1:MALE , 2:FEMALE) > ");
        scanf("%d", &search);
        printf("> Result : \n");

        for(int i=0; i<size; i++){
            if(m[i]->g==search-1){
                provideInfo(m, i+1);
                r++;
            }
        }
    }else{
        printf("> %d is not in your options\n", input);
    }

    if(r!=0) printf("> %d member(s) is/are found.\n", r);
}

void saveInfo(Member* m[], int size){
    FILE* file;
    file = fopen("member_list.txt", "w");

    for(int i=0; i<size; i++)
        fprintf(file, "%s %d %d %s %s\n", m[i]->name, m[i]->age, m[i]->g, m[i]->email, m[i]->password);

    fclose(file);

    printf("\nInformation is saved in member_list.txt file.\n");
}

void makeReport(Member* m[], int size){
    FILE* file;
    file = fopen("report.txt", "w");

    int male=0, female=0, age_sum=0, male_age_sum=0, female_age_sum=0;
    double age_avg=0.0, male_age_avg=0.0, female_age_avg=0.0;

    for(int i=0; i<size; i++){
        fprintf(file, "[%2d] name: %20s, age: %d, gender: %6s : e-mail: %s, pw: ", i+1, m[i]->name, m[i]->age, GENDER[m[i]->g], m[i]->email);
        for(int p=0; p<strlen(m[i]->password); p++){
            fprintf(file, "*");
        }
        fprintf(file, "\n");

        if(m[i]->g==0){
            male++;
            male_age_sum += m[i]->age;
            age_sum += m[i]->age;}
        else if(m[i]->g==1){
            female++;
            female_age_sum+=m[i]->age;
            age_sum += m[i]->age;}
    }

    age_avg = 1.0*age_sum/size;
    male_age_avg = 1.0*male_age_sum/male;
    female_age_avg = 1.0*female_age_sum/female;

    fprintf(file, "%d members, avarage age = %.1f\n", size, age_avg);
    fprintf(file, "%d male members, average age of males = %.1f\n", male, male_age_avg);
    fprintf(file, "%d female members, average age of females = %.1f\n", female, female_age_avg);


    fclose(file);

    printf("\nInformation is reported in report.txt file.\n");
}

void pickupRandomMember(Member* m[], int size){
    srand(time(0));

    printf("> Pick up RANDOM members\n");
    printf("> How many members you want to pick up? > ");

    int input;
    scanf("%d", &input);

    if(input<=0 || input>size){
        printf("> %d is not in the list.\n", input);
    }else{
        int ran[input];
        int count=0;
        int random_no;
        int check=0;
        while(count<input){
            random_no = rand()%size;
            if(count==0){
                ran[count]=random_no;
                count++;
            }else{
                for(int i=0; i<count; i++){
                    if(random_no==ran[i]) check=1;
                }
                if(check==0){
                    ran[count] = random_no;
                    count++;
                }
            }
        check=0;
        }

        printf("Random Members\n");
        for(int i=0; i<input; i++){
            printf(">>> [%d] name: %20s, age: %d, gender: %6s : e-mail: %s, pw: ", ran[i], m[ran[i]]->name, m[ran[i]]->age, GENDER[m[ran[i]]->g], m[ran[i]]->email);
            for(int p=0; p<strlen(m[ran[i]]->password); p++) printf("*");
            printf("\n");
        }
    }
}

int addNewMember(Member* m[], int size){
    Member* temp;
    printf("> Add a new Member\n");
    temp = (Member*)malloc(sizeof(Member));
    printf("\n> Enter his/her NAME info. > ");
	scanf("%s", temp->name);
	printf("> Enter his/her AGE info. > ");
	scanf("%d", &(temp->age));
	printf("> Enter his/her GENDER info. (MALE: 1, FEMALE: 2) > ");
    scanf("%d", &(temp->g));
    (temp->g)--;
    printf("> Enter his/her E-MAIL info. > ");
    scanf("%s", temp->email);
    printf("> Enter his/her PASSWORD info. > ");
    scanf("%s", temp->password);
    m[size] = temp;
    printf("> !New Member's information is added.\n");
    return size+1;

}
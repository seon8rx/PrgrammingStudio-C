#include "ssr_member.h"

char GENDER[2][30] = {"MALE", "FEMALE"};

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

        if(m[i]->g==0){male++; male_age_sum+=m[i]->age; age_sum += m[i]->age;}
        else if(m[i]->g==1){female++; female_age_sum+=m[i]->age; age_sum += m[i]->age;}
    }

    age_avg = 1.0*age_sum/size;
    male_age_avg = 1.0*male_age_avg/male;
    female_age_avg = 1.0*female_age_avg/female;

    fprintf(file, "%d members, avarage age = %.1f\n", size, age_avg);
    fprintf(file, "%d male members, average age of males = %.1f\n", male, male_age_avg);
    fprintf(file, "%d female members, average age of females = %.1f\n", female, female_age_avg);


    fclose(file);

    printf("\nInformation is reported in report.txt file.\n");
}

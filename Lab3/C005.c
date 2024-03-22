// 22100110 김성규

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 50

char LNAME[5][30]={"Graphite","Opal","Bronze","Silver","Gold"}; // labels by level

struct st_channel{
	char name[100]; // Channel name
	int count;	  // # of subscriptions
	int level;	  // index of level (0~4)
};

int loadData(struct st_channel* c[]); 
int findLevel(int num); 
void printStatistics(struct st_channel* c[], int size);
void printChannels(struct st_channel* c[], int size);
void pickupRandomChannels(struct st_channel* c[], int size);
void searchChannel(struct st_channel* c[], int size);
int addChannel(struct st_channel* c[], int size);
void updateChannel(struct st_channel* c[], int size);
int deleteChannel(struct st_channel* c[], int size);
void makeReport(struct st_channel* c[], int size); 

int main(void) {
	int no;	// amount of channels
	struct st_channel* clist[SIZE]; // channel list
	int menu; // menu number 

	srand(time(0));
	no = loadData(clist);

	while(1)
	{
		// Print menu
		printf("\n[1]List [2]Statistics [3]Random pick [4]Search [5]Add [6]Modify [7]Delete [8]Report [0]Exit\n> Enter a menu >> ");
		scanf("%d",&menu);	

		if(menu==1){
			printChannels(clist, no); // Print all list of channels
		}
		else if(menu==2){
			printStatistics(clist, no);	// Print statistics of each level
		}
		else if(menu==3){
			pickupRandomChannels(clist, no); // Pick up random channels
		}
		else if(menu==4){
			searchChannel(clist, no);	// Search a channel
		}
		else if(menu==5){
			no = addChannel(clist, no); // Add a channel
		}
		else if(menu==6){
			updateChannel(clist, no); // Modify a channel
		}
		else if(menu==7){
			no = deleteChannel(clist, no); // Delete a channel
		}
		else if(menu==8){
			makeReport(clist, no);	// Make a Report
		}
		else {
			break;
		}
	}
	return 0;
}

int loadData(struct st_channel* c[]){
	int no=0;
	FILE* file;

	file=fopen("channels.txt", "r");
	while(!feof(file)){
		struct st_channel* t = (struct st_channel*)malloc(sizeof(struct st_channel));
		int r=fscanf(file, "%s %d", t->name, &(t->count));
		if(r<2) break;
		t->level = findLevel(t->count);
		c[no] = t;
		no++;
	}
	fclose(file);
	printf("> %d channels are loaded.\n", no);
	return no;
}

int findLevel(int num){
	int range[5]={1000,10000,100000,1000000,10000000}; // range for level
	for(int j=0;j<5;j++)
		if(num<range[j])
			return j;
	return 0;
}

void printChannels(struct st_channel* c[], int size){
	printf("> List of Channels\n");
	for(int i=0; i<size; i++){
		printf("[%2d] %-20s %10d peoples [%s] \n",i+1, c[i]->name, c[i]->count,LNAME[c[i]->level]);
	}
}

int addChannel(struct st_channel* c[], int size){
	struct st_channel* temp;
	printf("> Add a new Channel\n");
	temp = (struct st_channel*)malloc(sizeof(struct st_channel));
	printf("> Enter a name of channel > ");
	scanf("%s", temp->name);
	printf("> Enter an amount of peoples > ");
	scanf("%d", &(temp->count));
	temp->level = findLevel(temp->count);
	c[size] = temp;
	printf("> New channel is added.\n");
	printf("[%2d] %-20s %10d peoples [%s] \n",size+1, c[size]->name, c[size]->count,LNAME[c[size]->level]);
	return size+1;
}

void printStatistics(struct st_channel* c[], int size){
	printf("> Statistics of Channels\n");

    int count[5] = {0};
    int sum[5] = {0};
    double avrg[5] = {0.0};
    int max_count[5]={0};
    char max_name[5][100];

    for(int i=0; i<size; i++){
        count[c[i]->level]++;
        sum[c[i]->level] = sum[c[i]->level] + c[i]->count;
        if(max_count[c[i]->level] < c[i]->count){
            max_count[c[i]->level] = c[i]->count;
            strcpy(max_name[c[i]->level], c[i]->name);
        }
    }
    for(int a=0; a<5; a++){
        avrg[a] = 1.0*sum[a]/count[a];
    }

    for(int r=0; r<5; r++){
        printf("%s : %d channels, Average %.1f peoples, Top channel : %s (%d people)\n", LNAME[r], count[r], avrg[r], max_name[r], max_count[r]);
    }


}

void pickupRandomChannels(struct st_channel* c[], int size){
	printf("> Pick up Channels\n");
	printf("> How much channels you want to pick up? > ");

	int num;
	scanf("%d", &num);
	
	int r[num];
	int count = 0;
	int random_no;
	int check = 0;
	while(count<num){
		random_no = rand()%size;
		if(count==0){
			r[count] = random_no;
			count++;
		}else{
			for(int i=0; i<count; i++){
				if(random_no==r[i]) check=1;
			}
			if(check==0){
				r[count] = random_no;
				count++;
			}
		}
		check=0;
	}

	printf("Random Channels\n");
	for(int i=0; i<num; i++){
		printf("[%d] %s (%s, %d peoples)\n", r[i]+1, c[r[i]]->name, LNAME[c[r[i]]->level], c[r[i]]->count);
	}
}
void searchChannel(struct st_channel* c[], int size){
	printf("> Search Channels\n");
	printf("> Choose one (1:by peoples 2:by names) > ");
	int input;
	scanf("%d", &input);

	int count=0;

	if(input==1){
		int search_to;
		int search_from;
		printf(">Enter the range of peoples (from ~ to) > ");
		scanf("%d %d", &search_from, &search_to);
		for(int i=0; i<size; i++){
			if(search_from<=c[i]->count && c[i]->count<=search_to){
				printf("[%2d] %-20s %10d peoples [%s] \n",i+1, c[i]->name, c[i]->count,LNAME[c[i]->level]);
				count++;
			}
		}
	}else if(input==2){
		char search[30];
		printf("> Enter a name > ");
		scanf("%s", search);
		for(int i=0; i<size; i++){
			if(strstr(c[i]->name, search)){
				printf("[%2d] %-20s %10d peoples [%s] \n",i+1, c[i]->name, c[i]->count,LNAME[c[i]->level]);
				count++;
			}
		}
	}

printf("> %d channels are found.\n", count);
}

void updateChannel(struct st_channel* c[], int size){
	printf("> Modify a new Channel\n");
	printf("> Enter a number of channel > ");
	int no_chan = 0;
	scanf("%d", &no_chan);

	//struct st_channel* t;
	while(1){
		int check = 0;
		if(1<=no_chan && no_chan<=size+1){
			break;
		}else{
			printf("> No Channel No.%d\n", no_chan);
			printf("> Modify a new Channel\n");
			printf("> Enter a number of channel > ");
			scanf("%d", &no_chan);
		}
	}

	printf("> Channel Info.\n");
	printf("[%2d] %-20s %10d peoples [%s] \n", no_chan, c[no_chan-1]->name, c[no_chan-1]->count,LNAME[c[no_chan-1]->level]);
	printf("> Enter new name of channel > ");
	scanf("%s", c[no_chan-1]->name);
	printf("> Enter a new amount of peoples > ");
	scanf("%d", &(c[no_chan-1]->count));
	c[no_chan-1]->level=findLevel(c[no_chan-1]->count);
	printf("> Channel info. is modified.\n");
}

int deleteChannel(struct st_channel* c[], int size){
	int no, yesno;
	printf("> Delete a new Channel\n");
	printf("> Enter a number of channel > ");

	return size;
}


void makeReport(struct st_channel* c[], int size){


}
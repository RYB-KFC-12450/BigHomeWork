#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

struct students
{
	char ID[23];
	int score,time;
};

int main()
{
	open:
	int choice;
	struct students stu;
	void start_test(int *);
	int Check_ID(char *);
	void Check_Score(char *);
	
	printf("--------------------------------");
	printf("\nPlease input your ID \nNo:");
	gets(stu.ID);
	while(!Check_ID(stu.ID))
	{
		printf("Error!\nCheck your input and insert your ID properly.");
		gets(stu.ID);
	}
	
	printf("--------------------------------\nWelcome!NO:%s",stu.ID);
	printf("\nNow you have three choices to choose\nPlease input your choice!");
	printf("\n(1)   Start a test\n(2)   Check scores\n(3)   Exit\n");
	scanf("%d",&choice);
	switch (choice)
	{
		case 1:
		clock_t start,end;
		start=clock();
		
		start_test(&stu.score);
		printf("\n--------------------------------");
		
		end=clock();
		stu.time=(end-start)/1000;
		printf("\nNO:%s!\nYour score is %d,and your time is %ds\n\n",stu.ID,stu.score,stu.time);
		
		FILE *RECORD;

		RECORD=fopen("record.txt","a");
			if (RECORD==NULL)
				 {
				 printf("The file was not successfully opened!\nPlease check the file!");
			     exit(1);
				 }
            fprintf(RECORD,"%s %d %d\n\n",stu.ID,stu.score,stu.time);
            fclose(RECORD);
            
            
		getchar();
		goto open;
		break;
		
		case 2:
		Check_Score(stu.ID);
		getchar();
		goto open;
		break;
		
		case 3:
		printf("\nEXIT NOW!");
		return 0; 
		break;
		
		default:
		printf("\nYou type a incorrect choice!!Please input again!!!\n");
		goto open;
		return 0;
		break;
	}
}

void Check_Score(char *idnum)
{
	FILE *RECORD;
	struct students stu;
	int i=0;

	RECORD=fopen("record.txt","r");
	if (RECORD==NULL)
 	{
        printf("The file was not successfully opened!\nPlease check the file!");
        exit(0);
    }
    
    
    printf("ID         score   time\n");
     while((fscanf(RECORD	,"%s %d %d",stu.ID,&stu.score,&stu.time))!=EOF) {
        if(!strcmp(idnum,stu.ID)) 
        {
            printf("%s %6d  %5dseconds\n",stu.ID,stu.score,stu.time);
            i=1;
        }                 
    }
    
    
   
   	if(!i)
	printf("Sorry, there is no your record before.\n");
	
}

int Check_ID(char* ID) 
{
	int i;
	if((ID[0]>='a'&&ID[0]<='z')||(ID[0]>='A'&&ID[0]<='Z'))
	{
		if((ID[1]>='a'&&ID[1]<='z')||(ID[1]>='A'&&ID[1]<='Z'))
		{
			for(i=2;i<6;i++)
			{
				if(!(ID[i]>='0'&&ID[i]<='9'))
				break;
			}
			if (i==6)
			return 1;
			else
			return 0;
		}
	}
}

void start_test(int *score_mid)
{   
	printf("--------------------------------\nWelcome to the text!\nNow let's begin!\n");
	int result[10],j[10],m[10],n[10],pre_operator[10];
	int i,mark,t;
	srand(time(NULL));
	
	mark=0;
	for(i=0;i<=9;i++)
	{
		m[i]=rand()%100;
		n[i]=rand()%100;
		pre_operator[i]=1+rand()%4;
				
		switch(pre_operator[i])
		{
			case 1:
			while(m[i]+n[i]>=100)
			{
				m[i]=rand()%100;
				n[i]=rand()%100;
			}
			printf(" %d + %d = ",m[i],n[i]);
			j[i]=m[i]+n[i];
			break;
		
			case 2:
			if(m[i]>=n[i])
			{
				printf(" %d - %d = ",m[i],n[i]);
				j[i]=m[i]-n[i];
			}
			else
			{
				printf(" %d - %d = ",n[i],m[i]);
				j[i]=n[i]-m[i];
			}
			break;
		
			case 3:
			while(m[i]*n[i]>=100)
			{
				m[i]=rand()%100;
				n[i]=rand()%100;
			}
			printf(" %d * %d = ",m[i],n[i]);
			j[i]=m[i]*n[i];
			break;
		
			case 4:
			while(m[i]%n[i]!=0)
			{
				n[i]=1+rand()%99;
				m[i]=1+rand()%99;
				if (m[i]<n[i])
				{
					t=m[i];
					m[i]=n[i];
					n[i]=t;
				}
			}
			printf(" %d / %d = ",m[i],n[i]);
			j[i]=m[i]/n[i];
			break;	
			
		}
		

		scanf("%d",&result[i]);	
	    if(result[i]==j[i])
	    {
		   	printf("Right.");
			mark=mark+10;
		}
		if(result[i]!=j[i])
		{
			printf("Wrong.");
			mark=mark;
		}
		printf("\n--------------------------------\n");	
		}
	*score_mid=mark;
	
	}

	
}



//creating a structure for shares 
typedef struct shares{
	int noofshares;
	int goldshares;
	int silvershares;
	int diamondshares;
	char sharetype;
	int price;
	int priceofgs;
	int priceofss;
	int priceofds;
}SHARES;

//creating structure for stock(linkedlist)
typedef struct stock{
	int bodylength; 
	char ordertype;
	int orderid;
	SHARES shares;
	int messeqnum;
	int checksum;
	int clientid;
	char orderstatus[4];
	char time[10];
	char date[15];
	char orderinstrument[10];
	struct stock *next;
}STOCK;

typedef struct array{
	int data;
	struct array *next;
}ARRAY;

//creating random value for time 
STOCK *timeof(STOCK *object)
{
	char timeof[20];
	char str[4];
	timeof[0]='\0';
	int x;
	x=rand()%24;
	snprintf(str, sizeof(str), "%d", x);
	strcat(timeof,str);
	strcat(timeof,":");
	x=rand()%+60;
	snprintf(str, sizeof(str), "%d", x);
	strcat(timeof,str);
	strcat(timeof,":");
	x=rand()%+60;
	snprintf(str, sizeof(str), "%d", x);
	strcat(timeof,str);
	strcpy(object->time,timeof);
	return object;
}

//creating random dates
STOCK *dateof(STOCK *object)
{
	char dateof[20];
	char str[6];
	dateof[0]='\0';
	int x;
	x=rand()%28+1;
	snprintf(str, sizeof(str), "%d", x);
	strcat(dateof,str);
	strcat(dateof,"/");
	x=rand()%11+1;
	snprintf(str, sizeof(str), "%d", x);
	strcat(dateof,str);
	strcat(dateof,"/");
	x=rand()%16+2000;
	snprintf(str, sizeof(str), "%d", x);
	strcat(dateof,str);
	strcpy(object->date,dateof);
	return object;
}

//checks whether the clientid and password are correct or not 
int search(char string[])
{
	FILE *fp3=fopen("users.txt","a+");
	char r[100];
	int x;
	while(fgets(r,sizeof(r),fp3)!=NULL) {
		x=strcmp(r,string);
		if(x==0)
		{
			return 1;
		}
	}
	fclose(fp3);
	return 0;
}

ARRAY *insert(ARRAY *a,char *p)
{
	ARRAY *n=(ARRAY *)malloc(sizeof(ARRAY));
	n->data=atoi(p);
	n->next=a;
	return n;
}

//confirms that the newly generated clientid doesnot match with existing clientid
int check(int userid)
{
	
	FILE *fp=fopen("data.txt","r");
	int x=0;
	char r[10];
	ARRAY *a=NULL;
	char p[10];
	while(fgets(r,sizeof(r),fp) != NULL) {
		int g=0;
		for(int i=0;r[i] != '\0';i++)
		{
			if(r[i] == '\n'){
				p[g] = '\0';
				g=0;
				a=insert(a,p);
			}
			else{
				p[g] = r[i];
				g++;
			}
		}
	}
	fclose(fp);
	FILE *fp1=fopen("data.txt","w");fclose(fp1);
	while(a!=NULL)
	{
		if(userid==a->data) {
			return 1;
		}
		a=a->next;
	}
	return 0;
}

//code for login
int login()
{

	int id,x,userid,c;
	char n[10];
	char string[100],string1[100],*pas;
	printf("Enter 1. To login  \n      2. To create new account \n\nEnter a valid option:");
	scanf("%s",n);
	if(strcmp(n,"1")==0) {
		printf("\nEnter clientid:");
		scanf("%d",&id);
		string[0]='\0';
		snprintf(string1,sizeof(string1),"%d",id);
		strcat(string,string1);
		strcat(string,",");
		pas=getpass("Enter password:");
		snprintf(string1,sizeof(string1),"%s",pas);
		strcat(string,string1);
		strcat(string,"\n");
		x=search(string);
		if(x==1)
		{
			printf("\nSuccessfully logged in!!!\n");
			return id;
		}
		else
		{
			printf("\n\nInvalid creadentials!!! login again\n\n");
			login();
		}
	}
	else if(strcmp(n,"2")==0) {
		char *string2;
		FILE *fp=fopen("users.txt","a+");
		FILE *fp1=fopen("data.txt","a+");
		x=0;
		while(x==0) {
			id=rand()%8999+1000;
			c=check(id);
			if(c==0)
			{
				break;
			}
		}
		printf("\nYour userid is : %d\n",id);
		string[0]='\0';
		snprintf(string1,sizeof(string1),"%d",id);
		fprintf(fp1,"%d\n",id);
		strcat(string,string1);
		strcat(string,",");
		string2=getpass("Generate your password:");
		printf("\nPassword successfully set!!!\n");
		strcat(string,string2);
		strcat(string,"\n");
		fprintf(fp,"%s",string);
		fclose(fp);
		fclose(fp1);
		return id;
	}
	else {
		printf("\n\nEnter a valid option\n\n");
		login();
	}

}


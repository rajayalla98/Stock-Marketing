//defining colours with variable names both background and text
#define ULINE "\x1B[4m" 
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define BBLCK "\x1B[40m"
#define BRED  "\x1B[41m"
#define BGRN  "\x1B[42m"
#define BYEL  "\x1B[43m"
#define BBLU  "\x1B[44m"
#define BMAG  "\x1B[45m"
#define BCYAN "\x1B[46m"
#define BWHT  "\x1B[47m"
#define BLINK "\x1B[5m"
#define HBBLCK "\x1B[100m"
#define FRAME "\x1B[51m"
#define FNT1  "\x1B[11m"
#define FNT2  "\x1B[12m"
#define FNT4  "\x1B[17m"
#define RESET "\x1B[0m"
//function for print heading
void printHeading()
{
	printf("\n");
	int i;
	for(i=0;i<25;i++)
		printf(" ");//giving spaces in terminal
	for(i=0;i<80;i++)
		printf(HBBLCK" "RESET);//printing background for 80 spaces 
	printf("\n");//entering into the new line 
	for(i=0;i<25;i++)
		printf(" ");
        //printing background in new line 
	for(i=0;i<21;i++)
		printf(HBBLCK" "RESET);    
	printf(HBBLCK"\x1B[31m******STOCK EXCHANGE BY HACKERS******"RESET);//printing head in red in text 
	for(i=0;i<22;i++)
		printf(HBBLCK" "RESET);
	printf("\n");//entering into new line
	for(i=0;i<25;i++)
		printf(" ");      
	for(i=0;i<80;i++)
		printf(HBBLCK" "RESET);
	printf("\n");
	printf("\n");      
}
//function for counting the no of digits for every number for the purpose of indentation
int countdigit(int n)
{
	int count=0;
	if(n==0)
		return 1;
	while(n!=0){
		count++;
		n=n/10;
	}; 
	return count;
}
//function for printing the colour backgroud spaces required for creating table
void printspace(int cnt ,int count[],int l,int k)
{
	int i;
	//printf("CNT:%d COUNT:%d",cnt,count[l]);
	if(k%2==0){
		for(i=0;i<count[l]-cnt;i++)
			printf(BBLCK" "RESET);
	}
	else{
		for(i=0;i<count[l]-cnt;i++)
			printf(HBBLCK" "RESET); 
	}       
}          

int count[11];
int printlst(STOCK *temp)
{  
	int cnt;
	printf("\n\n                                         THE GENERAL INFORMATION OF STOCKs BY DIFFERENT CLIENTS                       \n\n");
        //following print is for creating table with required columns 
	printf(BRED"S.NO      CLIENTID       ORDERID       NO OF SHARES       G.S VALUE      S.S VALUE      D.S VALUE        TIME       DATE        PRICE    "RESET);
	printf("\n");
	count[0]=10;count[1]=15;count[2]=14;count[3]=19;count[4]=15;count[5]=15;count[6]=17;count[7]=11;count[8]=12;count[9]=9;//storing the no of spaces used for each column(there are 10 cloumns)
	int k=1,l;
        // k represents the serial no and l represents the column index
	while(temp!=NULL) {
		l=0;	
		if(k%2==0){
                        //count digit function for counting no of digits ina number 
			cnt=countdigit(k);
			printf(BBLCK"\x1B[31m%d"RESET,k);
			printspace(cnt,count,l,k);//calling the printspace for required spaces with cnt
			l++;
			cnt=countdigit(temp->clientid);
			printf(BBLCK"\x1B[32m%d"RESET,temp->clientid);
			printspace(cnt,count,l,k);
			l++;
			cnt=countdigit(temp->orderid);
			printf(BBLCK"\x1B[33m%d"RESET,temp->orderid);
			printspace(cnt,count,l,k);
			l++;
			cnt=countdigit(temp->shares.noofshares);
			printf(BBLCK"\x1B[34m%d"RESET,temp->shares.noofshares);
			printspace(cnt,count,l,k);
			l++;
			cnt=countdigit(temp->shares.priceofgs);
			printf(BBLCK"\x1B[35m%d"RESET,temp->shares.priceofgs);
			printspace(cnt,count,l,k);
			l++;
			cnt=countdigit(temp->shares.priceofss);
			printf(BBLCK"\x1B[36m%d"RESET,temp->shares.priceofss);
			printspace(cnt,count,l,k);
			l++;
			cnt=countdigit(temp->shares.priceofds);
			printf(BBLCK"\x1B[37m%d"RESET,temp->shares.priceofds);
			printspace(cnt,count,l,k);
			l++;
			cnt=strlen(temp->time);
			printf(BBLCK"\x1B[33m%s"RESET,temp->time);
			printspace(cnt,count,l,k);
			l++;
			cnt=strlen(temp->date);
			printf(BBLCK"\x1B[31m%s"RESET,temp->date);
			printspace(cnt,count,l,k);
			l++;
			cnt=countdigit(temp->shares.price);
			printf(BBLCK"\x1B[35m%d"RESET,temp->shares.price);
			printspace(cnt,count,l,k);
			l++;
			printf("\n");//ending of the one row and enter into the next row
		}
                //printing another background for odd serial number
		else{
			cnt=countdigit(k);
			printf(HBBLCK"\x1B[37m%d"RESET,k);
			printspace(cnt,count,l,k);
			l++;
			cnt=countdigit(temp->clientid);
			printf(HBBLCK"\x1B[36m%d"RESET,temp->clientid);
			printspace(cnt,count,l,k);
			l++;
			cnt=countdigit(temp->orderid);
			printf(HBBLCK"\x1B[33m%d"RESET,temp->orderid);
			printspace(cnt,count,l,k);
			l++;
			cnt=countdigit(temp->shares.noofshares);
			printf(HBBLCK"\x1B[34m%d"RESET,temp->shares.noofshares);
			printspace(cnt,count,l,k);
			l++;
			cnt=countdigit(temp->shares.priceofgs);
			printf(HBBLCK"\x1B[33m%d"RESET,temp->shares.priceofgs);
			printspace(cnt,count,l,k);
			l++;
			cnt=countdigit(temp->shares.priceofss);
			printf(HBBLCK"\x1B[32m%d"RESET,temp->shares.priceofss);
			printspace(cnt,count,l,k);
			l++;
			cnt=countdigit(temp->shares.priceofds);
			printf(HBBLCK"\x1B[31m%d"RESET,temp->shares.priceofds);
			printspace(cnt,count,l,k);
			l++;
			cnt=strlen(temp->time);
			printf(HBBLCK"\x1B[37m%s"RESET,temp->time);
			printspace(cnt,count,l,k);
			l++;
			cnt=strlen(temp->date);
			printf(HBBLCK"\x1B[34m%s"RESET,temp->date);
			printspace(cnt,count,l,k);
			l++;
			cnt=countdigit(temp->shares.price);
			printf(HBBLCK"\x1B[32m%d"RESET,temp->shares.price);
			printspace(cnt,count,l,k);
			l++;
			printf("\n");
		} 

		temp=temp->next;
		k++;
	}
}


//this function creates a input string according to the 
void orderplacing(int clientid)
{
	char IN_FIXstring[1000],*OUT_FIXString;
	STOCK *IN_Object,*OUT_Object;
	FILE *fp=fopen("input.txt","a+");
	char type,ch;
	int noshares;
	char str[1000],string[100];str[0]='\0';
	printf("\nsharetype(G/S/D):");getchar();scanf("%c",&type);
	printf("\nNO-of-shares:");scanf("%d",&noshares);

	strcat(str,"109=");snprintf(string, sizeof(string), "%d", clientid);strcat(str,string);
	strcat(str,"'\\001'");

	strcat(str,"9=");int bl=rand()%300+99;snprintf(string, sizeof(string), "%d", bl);
	strcat(str,string);strcat(str,"'\\001'");

	strcat(str,"40=");snprintf(string, sizeof(string), "%c", 'I');
	strcat(str,string);strcat(str,"'\\001'");

	strcat(str,"37=");int orderid=rand()%9000+1000;snprintf(string, sizeof(string), "%d",orderid);
	strcat(str,string);strcat(str,"'\\001'");

	strcat(str,"53=");snprintf(string, sizeof(string), "%d",noshares);
	strcat(str,string);strcat(str,"'\\001'");

	strcat(str,"34=");int msgqnum=rand()%9+1;snprintf(string, sizeof(string), "%d",msgqnum);
	strcat(str,string);strcat(str,"'\\001'");

	strcat(str,"10=");int checksum=1;snprintf(string, sizeof(string), "%d",checksum);
	strcat(str,string);strcat(str,"'\\001'");

	strcat(str,"20=");snprintf(string, sizeof(string), "%c", type);
	strcat(str,string);

	fprintf(fp,"%s\n",str);fclose(fp);
	printf("\n\nThe generated string according to your inputs is:\n\n%s\n\n",str);
	printf("\n-----------------------------------------------------------------------------------------------------------------\n");
	IN_Object = convertFIXStringtoObject(str);
	//function to place or not to place order
	printf("The decoded string according to input string:\n\n");
	printf("clientid(109) : %d\n",IN_Object->clientid);
	printf("Msglength(9) : %d\n",IN_Object->bodylength);
	printf("Ordertype[I,D](40) : %c\n",IN_Object->ordertype);
	printf("Orderid(37) : %d\n",IN_Object->orderid);
	printf("No-of shares(53) : %d\n",IN_Object->shares.noofshares);
	printf("Msgsequence num(34) : %d\n",IN_Object->messeqnum);
	printf("Check sum(10) : %d\n",IN_Object->checksum);
	printf("Sharetype[G/S/D](20) : %d\n\n",IN_Object->shares.sharetype);
	printf("\n-----------------------------------------------------------------------------------------------------------------\n");
	OUT_Object = SendtoExchange(IN_Object);
	//function to generate outpur string
	OUT_FIXString=convertObjecttoFIXString(OUT_Object);
	printf("The encoded string that will be given to the user is:\n\n%s\n\n",OUT_FIXString);
	printf("\n-----------------------------------------------------------------------------------------------------------------\n");
}

//function for storing in .csv file
void create_csv(STOCK *head1)
{
	//to write share values for queries
	FILE *fp=fopen("in.csv","w+");
	fprintf(fp,"Client-ID,OrderID,No-Of-Shares,Price,NO-Silver-shares,Silver-shares,No-Gold-shares,Gold-share-value,No-Diamond-shares,Diamond-shares,Date,Time,Order-Status\n");
	while(head1!=NULL) {
		fprintf(fp,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s,%s,%s\n",head1->clientid,head1->orderid,head1->shares.noofshares,head1->shares.price,head1->shares.silvershares,head1->shares.priceofss,head1->shares.goldshares,head1->shares.priceofgs,head1->shares.diamondshares,head1->shares.priceofds,head1->date,head1->time,head1->orderstatus);
		head1=head1->next;
	}
}

//for displaying the user details(no-of shares,sharevalue)
void viewdetails(int clientid)
{
	STOCK *head1=head; 
	int y=0;
	//printf("Enter your client ID:");scanf("%d",&id);
	while(head1!=NULL) {
		if(head1->clientid==clientid) {
			if(strcmp(head1->orderstatus,"NP")==0) {
				printf("\n\nyour order is not placed because your details are corrupted by someone\n\nTRY AGAIN!!!\n\n");
				break;
			}
			else {
			printf("\n-----------------------------------------------------------------------------------------------------------------\n");
			printf("\nclientID:%d \norderID: %d  \nNo.of.shares: %d \norder Status: %s \nshareValue: %d \nno_of_silver-share: %d \nno-of-goldshares:%d\nno-of-diamondshares:%d\nsilver_share_value: %d\ngold_share_value: %d \ndiamond_share_value: %d\n",head1->clientid,head1->orderid,head1->shares.noofshares,head1->orderstatus,head1->shares.price,head1->shares.silvershares,head1->shares.goldshares,head1->shares.diamondshares,head1->shares.priceofss*head1->shares.silvershares,head1->shares.priceofgs*head1->shares.goldshares,head1->shares.priceofds*head1->shares.diamondshares);
			printf("\n-----------------------------------------------------------------------------------------------------------------\n");
			y=1;
			break;
			}
		}	
		head1=head1->next;
	}
	if(y==0) {
		printf("\n-----------------------------------------------------------------------------------------------------------------\n");
		printf("\nDETAILS NOT FOUND\n");			
	}	
}

//function for queries
void query()
{
	STOCK *temp=head;
	STOCK *pos;
	float max=0.0;int sel,q,p;
	char sel1 ;
	printf("\n\nChoose one of the following:\n\n     1. most valuable share Details\n     2. Highest shares\n     3. shares in b/w any particular range\n\nEnter a valid option:");
	char choose;scanf(" %c",&choose);
	switch(choose){

		case '1':
			printf("\nEnter 1 for gold \n      2 for silver \n      3 for diamond :");
			scanf("  %c:",&sel1);
			while(temp!=NULL){
				float max1;
				switch(sel1){
					case '1':
						max1=(temp->shares.priceofgs)/(temp->shares.goldshares+0.0);
						break;
					case '2':
						max1=(temp->shares.priceofss)/(temp->shares.silvershares+0.0);
						break;
					case '3':
						max1=(temp->shares.priceofds)/(temp->shares.diamondshares+0.0);
						break;
					default:
						printf("\n\nplease choose a valid option\n");
				}
				if(max1>max){
					max=max1;
					pos=temp;
				}
				temp=temp->next;
			}printf("\n-----------------------------------------------------------------------------------------------------------------\n");
			printf("\n\nMost Valuable share	: %f \n",max);
			printf("clientID : %d  \nTotal-share-value : %d  \nNo-Of-Shares : %d \n\n",pos->clientid,pos->shares.price,pos->shares.noofshares);
			printf("\n-----------------------------------------------------------------------------------------------------------------\n");
			temp=head;pos=NULL;
			break;
		case '2':

			while(temp!=NULL)
			{
				if(temp->shares.noofshares>max){
					max=temp->shares.noofshares;
					pos=temp;
				}
				temp=temp->next;
			}
			temp=head;printf("\n-----------------------------------------------------------------------------------------------------------------\n");
			printf("clientID: %d share-value :%d No-Of-Shares :%d \n",pos->clientid,pos->shares.price,pos->shares.noofshares);
			printf("\n-----------------------------------------------------------------------------------------------------------------\n");
			break;
		case '3':
			sel=0;
			printf("\nEnter particular range of price(seperated by space):");
			scanf("%d %d",&q,&p);
			while(temp!=NULL)
			{
				if(temp->shares.price*temp->shares.noofshares >q && temp->shares.price*temp->shares.noofshares<p)
				{
					sel=1;
					printf("\n-----------------------------------------------------------------------------------------------------------------\n");
					printf("\nclientID  :  %d  \norderID  :  %d  \nNo.of.shares  :  %d \norder Status  :  %s  \nshareValue  :  %d \nno_of_silver-share  :  %d  \nno-of-goldshares  :  %d \nno-of-diamondshares  :  %d \nsilver_share_value  :  %d \ngold_share_value  :  %d \ndiamond_share_value :  %d \n",temp->clientid,temp->orderid,temp->shares.noofshares,temp->orderstatus,temp->shares.price*temp->shares.noofshares,temp->shares.silvershares,temp->shares.goldshares,temp->shares.diamondshares,temp->shares.priceofss*temp->shares.silvershares,temp->shares.priceofgs*temp->shares.goldshares,temp->shares.priceofds*temp->shares.diamondshares);printf("\n");
					printf("\n-----------------------------------------------------------------------------------------------------------------\n");
				}
				temp=temp->next;
			}
			if(sel==0)
			{
				printf("\n\nsorry!!!  no shares available in the entered range\n");
			}		
			break;
		default:
			printf("\n\nplease choose a valid option\n");
			query();
	}

}

//recursively asks for the details of user if the entered details are wrong
int infinite(int clientid)
{
	char q;
	printf("\nChoose any of the following:\n\n    1. Orderplacing\n    2. View Details\n    3. Queries\n    4. Exit\n\nEnter a valid option:");
	scanf(" %c",&q);
	switch(q) {
		case '1':
			orderplacing(clientid);
			//encryption_decryption();
			//function to create a csv file
			create_csv(head);
			infinite(clientid);
			break;
		case '2':
			//encryption_decryption();
			flag++;
			viewdetails(clientid);
			infinite(clientid);
			break;
		case '3':
			//encryption_decryption();
			flag++;
			//function for any queries
			query();
			infinite(clientid);
			break;
		case '4':
			//function to print the list
			printlst(head);
			exit(-1);
		default:
			printf("\n\nplease enter a valid option\n\n");
			infinite(clientid);
			
	}
}



//globally declaring head as initially NULL
STOCK *head=NULL;
int flag=0;
char str[1000];
void printHeading();

//inserting object in a linked list
STOCK *insertObject(STOCK *object,int cost)
{
	STOCK *temp=head;
	if(head==NULL && object->ordertype=='I') {
		head=object;
	}
	else if(head!=NULL) {
		while(temp!=NULL) {
			if(temp->clientid==object->clientid) {
				if(temp->ordertype=='I') {	
					temp->shares.noofshares=temp->shares.noofshares+object->shares.noofshares;
					if(object->shares.sharetype=='G') {
						temp->shares.goldshares=temp->shares.goldshares+object->shares.goldshares;
						temp->shares.price=temp->shares.price-temp->shares.priceofgs+temp->shares.goldshares*cost+object->shares.priceofgs;
						temp->shares.priceofgs=cost;
					}
					else if(object->shares.sharetype=='S') {
						temp->shares.silvershares=temp->shares.silvershares+object->shares.silvershares;
						temp->shares.price=temp->shares.price-temp->shares.priceofss+temp->shares.silvershares*cost+object->shares.priceofss;
						temp->shares.priceofss=cost;
					}
					else if(object->shares.sharetype=='D') {
						temp->shares.diamondshares=temp->shares.diamondshares+object->shares.diamondshares;
						temp->shares.price=temp->shares.price-temp->shares.priceofds+temp->shares.diamondshares*cost+object->shares.priceofds;
						temp->shares.priceofds=cost;
					}
				}
				else {
					temp->shares.noofshares=temp->shares.noofshares-object->shares.noofshares;
					if(object->shares.sharetype=='G') {
						temp->shares.goldshares=temp->shares.goldshares-object->shares.goldshares;
						temp->shares.price=temp->shares.price-temp->shares.priceofgs;
						temp->shares.priceofgs=cost;
					}
					else if(object->shares.sharetype=='S') {
						temp->shares.silvershares=temp->shares.silvershares-object->shares.silvershares;
						temp->shares.price=temp->shares.price-temp->shares.priceofss;
						temp->shares.priceofss=cost;
					}
					else if(object->shares.sharetype=='D') {
						temp->shares.diamondshares=temp->shares.diamondshares-object->shares.diamondshares;
						temp->shares.price=temp->shares.price-temp->shares.priceofds;
						temp->shares.priceofds=cost;
					}
				}
				break;
			}
			temp=temp->next;
		}	
		if(temp==NULL && object->ordertype=='I') {
			object->next=head;
			head=object;
		}
	}
}

//converting given stock string to individual values and strings
STOCK *keepInLinkedlist(int a[][10],int k)
{
	int i,j,cost;
	STOCK *object=(STOCK *)malloc(sizeof(STOCK));
	FILE *fp2=fopen("data.txt","a");
	FILE *fp3=fopen("decoded.txt","a");
	for(i=0;i<k;i++) {
		if(a[i][0]==9) {
			object->bodylength=a[i][1];
			fprintf(fp3,"Bodylen:%d  ",a[i][1]);
		}
		else if(a[i][0]==40) {
			object->ordertype=a[i][1];
			fprintf(fp3,"Ordertype:%c  ",a[i][1]);
		}
		else if(a[i][0]==37) {
			object->orderid=a[i][1];
			fprintf(fp3,"Orderid:%d  ",a[i][1]);
		}
		else if(a[i][0]==53) {
			object->shares.noofshares=a[i][1];
			fprintf(fp3,"No-of shares:%d  ",a[i][1]);
		}
		else if(a[i][0]==34) {
			object->messeqnum=a[i][1];
			fprintf(fp3,"Messeqnum:%d  ",a[i][1]);
		}
		else if(a[i][0]==10) {
			object->checksum=a[i][1];
			fprintf(fp3,"Checksum:%d  ",a[i][1]);
		}
		else if(a[i][0]==109) {
			object->clientid=a[i][1];
			fprintf(fp2,"%d\n",a[i][1]);
			fprintf(fp3,"Clientid:%d  ",a[i][1]);
			fclose(fp2);
		}
		else if(a[i][0]==20) {
			object->shares.sharetype=a[i][1];
			fprintf(fp3,"sharetype:%c\n",a[i][1]);
			if(a[i][1]=='G') {
				cost=rand()%50+100;
				object->shares.goldshares=object->shares.noofshares;
				object->shares.priceofgs=cost*object->shares.noofshares;
				object->shares.silvershares=0;
				object->shares.priceofss=0;
				object->shares.diamondshares=0;
				object->shares.priceofds=0;
			}
			else if(a[i][1]=='S') {
				cost=rand()%20+50;
				object->shares.silvershares=object->shares.noofshares;
				object->shares.priceofss=cost*object->shares.noofshares;
				object->shares.goldshares=0;
				object->shares.priceofgs=0;
				object->shares.priceofds=0;
				object->shares.diamondshares=0;
			}
			else if(a[i][1]=='D') {
				cost=rand()%100+150;
				object->shares.diamondshares=object->shares.noofshares;
				object->shares.priceofds=cost*object->shares.noofshares;
				object->shares.goldshares=0;
				object->shares.priceofgs=0;
				object->shares.silvershares=0;
				object->shares.priceofss=0;
			}
		}
	}
	object->shares.price=object->shares.priceofgs+object->shares.priceofss+object->shares.priceofds;
	object=timeof(object);
	object=dateof(object);
	object->next=NULL;
	insertObject(object,cost);
	fclose(fp3);
	return object;
}

//function to convert given objects to a fixed string
char *convertObjecttoFIXString(STOCK *temp)
{
	char string[100];
	FILE *fp1=fopen("output.txt","a");
	//snprintf is used for converting integer to string

	str[0]='\0';
	//converting bodylength  from integer  to string
	strcat(str,"9=");
	snprintf(string, sizeof(string), "%d", temp->bodylength);
	strcat(str,string);
	strcat(str,"'\\001'");

	//seeing the checksum value and proceeding according to it 
	strcat(str,"39=");
	if(temp->checksum==1) {
		strcat(str,"P");
	}
	else {	
		strcat(str,"NP");
	}
	strcat(str,"'\\001'");

	//price
	strcat(str,"44=");
	snprintf(string, sizeof(string), "%d", temp->shares.price);
	strcat(str,string);
	strcat(str,"'\\001'");

	//orderid
	strcat(str,"37=");
	snprintf(string, sizeof(string), "%d", temp->orderid);
	strcat(str,string);	
	strcat(str,"'\\001'");

	//messeqnum
	strcat(str,"34=");
	snprintf(string, sizeof(string), "%d", temp->messeqnum);
	strcat(str,string);	
	strcat(str,"'\\001'");

	//checksum
	strcat(str,"10=");
	snprintf(string, sizeof(string), "%d", temp->checksum);
	strcat(str,string);	
	strcat(str,"'\\001'");

	//checking ascii value of ordertype and proceeding according to it
	strcat(str,"40=");
	if(temp->ordertype==73) {
		strcat(str,"I");
	}
	else if(temp->ordertype==68){
		strcat(str,"D");
	}	
	strcat(str,"'\\001'");

	//clientid
	strcat(str,"109=");
	snprintf(string, sizeof(string), "%d", temp->clientid);
	strcat(str,string);	

	fprintf(fp1,"%s\n",str);
	//printf("%s\n",str);
	fclose(fp1);
	return str;
}
//checking weather to place or not to place the order
STOCK *SendtoExchange(STOCK *temp)
{
	if(temp->checksum==1) {
		strcpy(temp->orderstatus,"P");
	}
	else {	
		strcpy(temp->orderstatus,"NP");
	}
	return temp;
}

//storing input string in a 2d integer array
STOCK *convertFIXStringtoObject(char r[])
{
	STOCK *temp;
	int i,k,j,sum,b[10],x,l;
	int a[100][10];
	k=0;j=0;x=0;
	for(i=0;i<strlen(r);i++) {
		if(r[i] == '=') {
			sum=0;
			for(l=0;l<x;l++) {
				sum=sum*10+b[l];
			}
			a[k][j]=sum;j++;
			x=0;
			if(sum==40) {
				a[k][j]=r[i+1];
				i=i+7;j=0;k++;
				continue;
			}
			else if(sum==20) {
				a[k][j]=r[i+1];
				i=i+7;j=0;k++;
				continue;
			}
		}
		else if(r[i] == '\'' || r[i]=='\n' || r[i]=='\0') {
			sum=0;
			for(l=0;l<x;l++)
			{
				sum=sum*10+b[l];
			}
			a[k][j]=sum;
			k++;j=0;i=i+5;x=0;
		}
		else {
			b[x] =r[i] - '0';
			x++;
		}
	}
	temp=keepInLinkedlist(a,k);
	return temp;
}

//taking each line of file keeping it in linkedlist
void encryption_decryption()
{
	if(flag==0) {
		FILE *fp=fopen("input.txt","r");
		char IN_FIXstring[1000],*OUT_FIXString;
		STOCK *IN_Object,*OUT_Object;
		while(fgets(IN_FIXstring,sizeof(IN_FIXstring),fp)!=NULL) {
			//function to convert string to object and generating price
			IN_Object = convertFIXStringtoObject(IN_FIXstring);
			//function to place or not to place order
			OUT_Object = SendtoExchange(IN_Object);
			//function to generate outpur string
			OUT_FIXString=convertObjecttoFIXString(OUT_Object);   
			//printf("%s\n\n",OUT_FIXString);
		}

	}
}

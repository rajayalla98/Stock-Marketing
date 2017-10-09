#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<string.h>
#include<unistd.h>
#include"094-assign12.h"
#include"160-assign12.h"
#include"071-assign12.h"
#include"020-assign12.h"

int main(int argc,char *argv[])
{	
	srand((unsigned)time(NULL));
	printHeading();
	printf("\n");
	FILE *fp2=fopen("output.txt","w");fclose(fp2);
	FILE *fp3=fopen("decoded.txt","w");fclose(fp3);
	//personal program	
	encryption_decryption();
	int clientid=login();
	infinite(clientid);
	return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<string.h>

//function for generating random input file
void randomfile(int n){
	FILE *fp;
	fp=fopen("input.txt","w+");
	for(int i=0;i<n;i++){
		char ch,ch1;
		int k;
		fprintf(fp,"109=%d'\\001'",1000+rand()%9000);
		fprintf(fp,"9=%d'\\001'",100+rand()%900);
		k=rand()%2;
		if(k==0)
			ch='I';
		else
			ch='D';  
		fprintf(fp,"40=%c'\\001'",ch);
		fprintf(fp,"37=%d'\\001'",1000+rand()%9000);
		fprintf(fp,"53=%d'\\001'",1+rand()%9);
		fprintf(fp,"34=%d'\\001'",1+rand()%9);
		fprintf(fp,"10=%d'\\001'",rand()%2);
		int y=rand()%3;
		if(y==0)
			ch1='S';
		else if(y==1)
			ch1='G';  
		else ch1='D';
		fprintf(fp,"20=%c\n",ch1);

	}
	fclose(fp);
}

int main(int argc,char *argv[])
{
	int n=argc > 1 ? atoi(argv[1]):2000;
	randomfile(n);
	return 0;
}

#include <stdio.h>

#include "MyStruct.h"

struct myStruct strus[]={{"Sinus",50,23,{1,2,3,4}},{"Rechteck",15,33,{5,6,7,8,9}},{"Saegezahn",18,12,{10,11,12,13,14,15}}};

void main()
{
	
	for(int i=0;i<3;i++)
	{
	FILE* f=fopen( "/dev/MessageKiel", "w");	
	
	printf("Nachricht:%s i:%d  j:%d values:",strus[i].nachricht,strus[i].i,strus[i].j);
	for(int j=0;j<20;j++)
		{
			printf(" %d ",strus[i].values[j]);	
		}
	 printf("sende %d Bytes\n",sizeof(strus[i]));
	 int angenommen=fwrite(&strus[i],1,sizeof(strus[i]),f);
	 printf("Der Treiber hat %d bytes angenommen\n",angenommen);
	 fclose(f);
	}

	
	
	
	struct myStruct structs[10];
	int i=0;
	for(int i=0;i<3;i++)
	{
	FILE* f=fopen( "/dev/MessageKiel", "r");	
	
	 int angenommen=fread(&structs[i],sizeof(structs[0]),1,f);
	
	printf("bytes gelesen :%d wollte aber %d\n",angenommen,sizeof(structs[0]));
		
	printf("Nachricht empfangen:%s i:%d  j:%d values:",structs[i].nachricht,structs[i].i,structs[i].j);
	for(int j=0;j<20;j++)
		{
			printf(" %d ",structs[i].values[j]);	
		}
	 
	 fclose(f);
	}

	
}

	
	
	

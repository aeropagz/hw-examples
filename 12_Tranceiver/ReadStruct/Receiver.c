#include <stdio.h>

#include "MyStruct.h"
void main()
{
	
	struct myStruct structs[10];
	int i=0;
	for(int i=0;i<3;i++)
	{
	FILE* f=fopen( "/dev/MessageKiel", "r");	
	int angenommen=fread(&structs[i],sizeof(structs[0]),1,f);
	printf("bytes gelesen :%d wollte aber %d\n",angenommen*sizeof(structs[0]),sizeof(structs[0]));

	printf("Nachricht empfangen:%s i:%d  j:%d values:",structs[i].nachricht,structs[i].i,structs[i].j);
	for(int j=0;j<20;j++)
		{
			printf(" %d ",structs[i].values[j]);	
		}
	 
	 fclose(f);
	}
}

	
	
	

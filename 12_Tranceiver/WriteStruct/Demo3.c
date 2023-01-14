#include <stdio.h>

#include "MyStruct.h"
void main()
{
	
	FILE* f=fopen( "/dev/MessageKiel", "w");
	
	struct myStruct strus[]={{"Sinus",50,23,{1,2,3,4}},{"Rechteck",15,33,{5,6,7,8,9}},
		{"Saegezahn",18,12,{10,11,12,13,14,15}}};
	
	printf("Nachricht:%s i:%d  j:%d values:",strus[0].nachricht,strus[0].i,strus[0].j);
	for(int j=0;j<20;j++)
		{
			printf(" %d ",strus[0].values[j]);	
		}
	 printf("sende %d Bytes\n",sizeof(strus[0]));
	 int angenommen=fwrite(&strus[0],1,sizeof(strus[0]),f);
	 printf("Der Treiber hat %d bytes angenommen\n",angenommen);

	fclose(f);
}

	
	
	

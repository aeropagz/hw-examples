#include <stdio.h>

void main()
{
	
	
	char *buf;
	size_t num;
	
	for(int i=0; i<10;i++)
		{	
		FILE *f=fopen( "/dev/MessageKiel", "r");
		getline(&buf,&num,f);
		printf("Received: %s length: %d",buf,num);
		fclose(f);
		}	
}

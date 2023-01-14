#include <unistd.h>
#include <stdio.h>
void main()
{
	
	
	char buf [] ="Test";
	FILE* f=fopen( "/dev/MessageKiel", "w");
	
	
	
	for(int i=0;i<50;i++)
	{
	fwrite(buf,1,sizeof(buf),f);
	}
fclose(f);
}

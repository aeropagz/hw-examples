#include <stdio.h>

struct myStruct{
	char nachricht[12];
	double d;
	int i;
	
	};

struct myStruct2{
	double d;
	int i;
	char nachricht[12];
	};

void main()
{
	struct myStruct stru;
	printf("Groesse des Strings %d\n",sizeof(stru.nachricht));
	printf("Groesse double %d\n",sizeof(double));
	printf("Groesse int %d\n",sizeof(int));
	printf("Groesse der Struktur %d\n",sizeof(stru));
	printf("\n");
	
	printf("Adresse der Struktur %x\n",&stru);
	printf("Adresse des Strings %x\n",stru.nachricht);
	printf("Adresse double %x\n",&stru.d);
	printf("Adresse int %x\n",&stru.i);
	printf("\n");
	printf("\n");
	
	
	struct myStruct2 stru2;
	printf("Groesse double %d\n",sizeof(double));
	printf("Groesse int %d\n",sizeof(int));
	printf("Groesse des Strings %d\n",sizeof(stru2.nachricht));
	printf("Groesse der Struktur %d\n",sizeof(stru2));
	printf("\n");
	printf("Adresse der Struktur %x\n",&stru2);
	printf("Adresse double %x\n",&stru2.d);
	printf("Adresse int %x\n",&stru2.i);
	printf("Adresse des Strings %x\n",stru2.nachricht);
	
	printf("\n");
	printf("\n");
	
}

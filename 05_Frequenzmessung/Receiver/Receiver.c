#include <unistd.h>
#include <stdio.h>
void main()
{
    FILE* f=fopen("/dev/FANCY_DEVICE","r");
    unsigned long interrupts=0;

    for (int i = 0; i < 50; i++)
    {
        fread(&interrupts,sizeof(interrupts),1,f);
        printf("Frequenz %f kHz\n", (interrupts/1000.0));
        sleep(1);
    }
    fclose(f);
}

#include "../include/input.h"
#include "../include/cpu.h"

void printStatus(CPU *cpu)
{
    printf("Tempo %d - %c \n", cpu->time, cpu->description);
    printf("Fila:  ");

    size_t sizeArrayProcessQueue = sizeof(cpu->queueProcess)/sizeof(cpu->queueProcess[0]); 
    for (int i = 0; i < sizeArrayProcessQueue; i++)
    {
        printf("P%d() - ", cpu->queueProcess->number);
    }
    printf("\n");
    printf("Na CPU: P%d\n \n", cpu->processInCpu->number);
}

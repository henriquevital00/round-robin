#include "../include/input.h"
#include "../include/cpu.h"

void printStatus(CPU *cpu)
{
    printf("Tempo %d - ", cpu->time);
    printf("%s \n", cpu->description);
    printf("Fila:  ");

    for (int i = 0; i < cpu->sizeQueueProcess; i++)
    {
        printf("P%d(%d) - ", cpu->queueProcess->number, cpu->queueProcess->duration);
    }
    printf("\n");
    printf("Na CPU: P%d\n \n", cpu->processInCpu->number);
}

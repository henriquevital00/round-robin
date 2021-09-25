#include "../include/input.h"
#include "../include/cpu.h"

void printStatus(CPU *cpu)
{
    printf("Tempo %d - ", cpu->time);
    printf("%s \n", cpu->description);
    printf("Fila:  ");

    for (int i = 0; i < cpu->sizeprocessQueue; i++)
    {
        printf("P%d(%d) - ", cpu->processQueue->number, cpu->processQueue->duration);
    }
    printf("\n");
    printf("Na CPU: P%d\n \n", cpu->runningProcess->number);
}

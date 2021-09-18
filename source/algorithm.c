#include "../include/input.h"
#include "../include/process.h"


void calcula(Process *arrayProcess)
{
    printf("%d\n", arrayProcess);
    int n = sizeof(arrayProcess) / sizeof(arrayProcess[0]);

    for (int i = 0; i < n; i++)
    {
        int sizeInterruptions = sizeof(arrayProcess->interruptions) / sizeof(arrayProcess->interruptions[0]);

        printf("interruptions %d\n", arrayProcess[i].duration);
        
    }
}
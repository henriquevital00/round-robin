#include "../include/input.h"
#include "../include/process.h"
#include "../include/stack.h"

void calculate(Process *processes)
{
    for (int i = 0; i < numberProcess; i++)
    {

        for (int j = 0; j < processes[i].numberIO; j++)
        {
            printf("interruptions: %d\n", processes[i].interruptions[j]);
        }
    }
}

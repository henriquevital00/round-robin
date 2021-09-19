#ifndef STACK_H_
#define STACK_H_
#include "../include/process.h"

typedef struct
{
    int time;
    char description;
    int* queueProcess;
    Process processInCpu;
} Stack;

#endif
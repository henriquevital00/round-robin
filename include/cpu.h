#ifndef CPU_H_
#define CPU_H_
#include "../include/process.h"

typedef struct
{
    int time;
    char* description;
    int sizeQueueProcess;
    Process* queueProcess;
    Process* processInCpu;
} CPU;

#endif
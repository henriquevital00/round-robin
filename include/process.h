#ifndef PROCESS_H_
#define PROCESS_H_

typedef struct
{
    int number;
    int duration;
    int startDuration;
    int quantumCount;
    int arrival;
    int *interruptions;
    int numberIO;
    int startTime;
    int finalTime;
} Process;

int numberProcess;

#endif
#include "../include/input.h"
#include "../include/process.h"
#include "../include/queue.h"

/* INSERTION */

bool isInserting(Process *processes, int time)
{
    for (int n = 0; n < numberProcess; n++)
    {
        Process process = processes[n];
        if (process.arrival == time)
            return true;
    }
    return false;
}

void onInsertAtTime(Process *processes, int time)
{

    for (int n = 0; n < numberProcess; n++)
    {
        Process process = processes[n];
        if (process.arrival == time)
        {
            push(process);
            printf("Chegada do processo: P%d\n", process.number);
        }
    }
}

/* QUANTUM */

bool isQuantumOverflow(int quantum)
{
    Process *current = first();
    if (current)
    {
        if (current->quantumCount == quantum)
            return true;
    }
    return false;
}

void onOverflowQuantum()
{
    Process *current = first();
    printf("fim de quantum: P%d\n", current->number);
    dequeueProcess();
}

void incrementQuantum()
{
    Process *current = first();
    if (current)
        current->quantumCount++;
}

/* INTERRUPTION */

bool isInterrupting()
{

    Process *current = first();

    if (current)
    {
        for (int i = 0; i < current->numberIO; i++)
        {

            int remainingTime = current->startDuration - current->duration;

            if (current->interruptions[i] == remainingTime)
                return true;
        }
    }

    return false;
}

void onInterruptProcess(int quantum)
{

    Process current = *first();

    printf("operação de I/O: P%d\n", current.number);

    dequeueProcess();
}

/* Utils */

void dequeueProcess()
{
    /* Move to the end of queue*/
    Process current = *first();
    current.quantumCount = 0;
    pop();
    push(current);
}

void incrementProcess(int time)
{
    Process *current = first();

    if (current->duration == current->startDuration)
        current->startTime = time;

    current->duration--;
    //current->quantumCount++;
}

int calculateTotalDuration(Process *processes)
{
    int duration = 0;
    for (int i = 0; i < numberProcess; i++)
        duration += processes[i].duration;
    return duration;
}

void calculateProcessWaitTime(int *totalWaitTime)
{
    Process *current = first();

    int waitTime = (current->finalTime - current->startTime);
    (*totalWaitTime) += waitTime;
    printf("Tempo de espera: %d ms\n", waitTime);
}

float calculateWaitTimeAverage(int *totalWaitTime)
{
    return *totalWaitTime / numberProcess;
}

void onExitProcess(int time, int *totalWaitTime)
{
    Process *current = first();

    if (current->duration == 0)
    {
        printf("fim de processo: P%d\n", current->number);
        current->finalTime = time;
        calculateProcessWaitTime(totalWaitTime);
        pop();
    }
}

void roundRobbin(Process *processes)
{

    int totalDuration = calculateTotalDuration(processes) + 1;
    int quantum = 4;
    int totalWaitTime = 0;

    for (int t = 0; t < totalDuration; t++)
    {

        printf("\n\nTempo: %d - ", t);
        incrementQuantum();
        bool hasInsertion = isInserting(processes, t);
        bool hasInterrupt = isInterrupting();
        bool hasQuantum = isQuantumOverflow(quantum);

        if (hasInsertion && hasInterrupt)
        {
            onInterruptProcess(quantum);
            onInsertAtTime(processes, t);
        }
        else if (hasInterrupt || (hasQuantum && hasInterrupt))
            onInterruptProcess(quantum);
        else if (hasInsertion)
            onInsertAtTime(processes, t);
        else if (hasQuantum)
            onOverflowQuantum();

        showQueue();
        onExitProcess(t, &totalWaitTime);

        Process *current = first();
        if (current)
        {
            printf("Na CPU: P%d \n", current->number);
            incrementProcess(t);
        }
    }

    printf("Tempo médio de espera = %.2f", calculateWaitTimeAverage(&totalWaitTime));
}

void calculate(Process *processes)
{
    createQueue();
    roundRobbin(processes);
}

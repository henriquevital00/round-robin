#include "../include/input.h"
#include "../include/process.h"
#include "../include/queue.h"

/* UTILS */
Process *(*currentProcess)() = first;

void requeueProcess()
{
    Process current = pop();
    current.quantumCount = 0;
    push(current);
}

void incrementTime(int time)
{
    currentProcess()->quantumCount++;
    currentProcess()->duration--;
}

int calculateTotalDuration(Process *processes)
{
    int duration = 0;
    for (int i = 0; i < numberProcess; i++)
        duration += processes[i].duration;
    return duration + 1;
}

void calculateProcessWaitTime(int *waitTimeArray)
{
    waitTimeArray[currentProcess()->number - 1] = (currentProcess()->finalTime - (currentProcess()->arrival + currentProcess()->startDuration));
}

void showWaitTimeAverage(int *waitTimeArray)
{
    float totalTime = 0;
    printf("\nTempos de espera:\n\n");

    for (int n = 0; n < numberProcess; n++)
    {
        printf("P%d: %d ms\n", n + 1, waitTimeArray[n]);
        totalTime += waitTimeArray[n];
    }
    float waitTimeAverage = (float)(totalTime) / (float)numberProcess;
    printf("\nTempo médio de espera = %.2f\n", waitTimeAverage);
    free(waitTimeArray);
}

void onExitProcess(int time, int *waitTimeArray)
{
    if (currentProcess())
    {
        Process var = *currentProcess();
        if (currentProcess()->duration == 0)
        {
            printf("fim de processo: P%d\n", currentProcess()->number);
            currentProcess()->finalTime = time;
            calculateProcessWaitTime(waitTimeArray);

            pop();
        }
    }
}

/* INSERTION */
bool isProcessArrive(Process *processes, int time)
{
    for (int n = 0; n < numberProcess; n++)
    {
        if (processes[n].arrival == time)
            return true;
    }
    return false;
}

int sortProcesses(const void *curr, const void *next)
{
    int currDuration = ((Process *)curr)->duration;
    int nextDuration = ((Process *)next)->duration;
    return currDuration - nextDuration;
}

Process *getConcurrentProcessesSorted(Process *processes, int time, int *concurrentsNumber)
{
    Process *sortedProcesses = malloc(sizeof(Process) * numberProcess);

    for (int n = 0; n < numberProcess; n++)
    {
        Process process = processes[n];
        if (process.arrival == time)
            sortedProcesses[(*concurrentsNumber)++] = process;
    }

    qsort(sortedProcesses, *concurrentsNumber, sizeof(Process), sortProcesses);
    return sortedProcesses;
}

void onProcessArrive(Process *processes, int time)
{
    int concurrentsNumber = 0;
    Process *sortedProcesses = getConcurrentProcessesSorted(processes, time, &concurrentsNumber);

    for (int n = 0; n < concurrentsNumber; n++)
    {
        push(sortedProcesses[n]);
        printf("Chegada do processo: P%d\n", sortedProcesses[n].number);
    }

    free(sortedProcesses);
}

/* QUANTUM */
bool isQuantumOverflow(int quantum)
{
    return currentProcess() ? currentProcess()->quantumCount == quantum : false;
}

void onOverflowQuantum()
{
    printf("fim de quantum: P%d\n", currentProcess()->number);
    requeueProcess();
}

/* INTERRUPTION */
bool isInterruption()
{
    if (currentProcess())
    {
        for (int i = 0; i < currentProcess()->numberIO; i++)
        {
            int remainingTime = currentProcess()->startDuration - currentProcess()->duration;

            if (currentProcess()->interruptions[i] == remainingTime)
                return true;
        }
    }
    return false;
}

void onInterruptProcess()
{
    printf("operação de I/O: P%d\n", currentProcess()->number);
    requeueProcess();
}

/* ALGORITHM */
void roundRobbin(Process *processes, int quantum)
{
    printf("Quantum: %d\n", quantum);
    int totalDuration = calculateTotalDuration(processes);
    int *waitTimeArray = malloc(sizeof(int) * numberProcess);

    for (int t = 0; t < totalDuration; t++)
    {
        printf("\n\nTempo: %d - ", t);

        bool hasProcessArriving = isProcessArrive(processes, t);
        bool hasInterruption = isInterruption();
        bool hasQuantumOverflow = isQuantumOverflow(quantum);

        if (hasProcessArriving && hasInterruption)
        {
            onInterruptProcess();
            onProcessArrive(processes, t);
        }
        else if (hasInterruption || (hasQuantumOverflow && hasInterruption))
            onInterruptProcess();
        else if (hasProcessArriving)
            onProcessArrive(processes, t);
        else if (hasQuantumOverflow)
            onOverflowQuantum();

        showQueue();
        onExitProcess(t, waitTimeArray);

        if (currentProcess())
        {
            printf("Na CPU: P%d \n", currentProcess()->number);
            incrementTime(t);
        }
    }
    showWaitTimeAverage(waitTimeArray);
}

void calculate(Process *processes, int quantum)
{
    createQueue();
    roundRobbin(processes, quantum);
}

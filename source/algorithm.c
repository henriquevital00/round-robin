#include "../include/input.h"
#include "../include/process.h"
#include "../include/cpu.h"
#include "../include/output.h"
#include "../include/queue.h"

/*
Alterna entre processos (preempção)
Existência de uma fatia de tempo para execução (quantum)
Percorre a fila circularmente, alocando a CPU a cada processo por 1 quantum de tempo
O processo pode parar sua execução antes de terminar seu 1 quantum de tempo
*/

int calculateTotalDuration(Process *processes)
{
    int duration = 0;
    for (int i = 0; i < numberProcess; i++)
    {
        duration += processes[i].duration;
    }
    return duration;
}

void setProcessOnTime(Process *processes, int time)
{
    bool hasRunningProcess = first() != NULL;

    if (hasRunningProcess)
    {
        Process current = *(first());
        for (int n = 0; n < numberProcess; n++)
        {
            Process process = processes[n];
            if (process.arrival == time)
            {
                removeData();
                insert(process);
                insert(current);
                return;
            }
        }
    }
    else
    {
        insert(processes[0]);
    }
}

bool hasInterruption(Process current, int time)
{
    for (int i = 0; i < current.numberIO; i++)
    {
        if (current.interruptions[i] == time)
        {
            removeData();
            insert(current);
            return true;
        }
    }
    return false;
}

void roundRobbin(Process *processes)
{
    int totalDuration = calculateTotalDuration(processes);
    int quantum = 4;

    for (int t = 0; t < totalDuration; t++)
    {
        showQueue();
        printf("\n\nTime: %d\n", t);
        setProcessOnTime(processes, t);
        if (!isEmpty())
        {
            Process* current = first();
            printf("Currennt process: %d\n", current->number);
            if (hasInterruption(*current, t))
                break;

            if (!current->duration--)
                removeData();
        }
        showQueue();
    }
}

void calculate(Process *processes)
{
    createQueue();
    int totalDuration = calculateTotalDuration(processes);
    CPU *cpuTimes = malloc(sizeof(CPU) * totalDuration);

    roundRobbin(processes);
    //cpuTimes[currentProcess.time] = currentProcess;

    //printStatus(cpuTimes);
}

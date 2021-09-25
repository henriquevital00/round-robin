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

void roundRobbin(Process *processes)
{
    int totalDuration = calculateTotalDuration(processes);
    int quantum = 4;

    for (int t = 0; t < totalDuration; t++)
    {
        printf("Time: %d\n", t);
        for (int n = 0; n < numberProcess; n++)
        {
            Process process = processes[n];
            if (process.arrival == t)
            {
                insert(process);
            }
        }
        if (size())
        {
            Process current = processArray[front];
            printf("Currennt process: %d\n", current.number);
            bool hasInterruption = false;
            for (int i = 0; i < current.numberIO; i++)
            {
                if (current.interruptions[i] == t)
                {
                    hasInterruption = true;
                    removeData();
                    insert(current);
                }
            }
            if (hasInterruption)
                break;

            current.duration--;

            if (!current.duration)
                removeData();
        }
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

#include "../include/input.h"
#include "../include/process.h"
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

bool setProcessOnTime(Process *processes, int time)
{
    bool hasRunningProcess = first() != NULL;

    for (int n = 0; n < numberProcess; n++)
    {
        Process process = processes[n];
        if (process.arrival == time)
        {
            if (hasRunningProcess)
            {
                Process current = *(first());
                insert(process);
            }
            else
            {
                insert(process);
            }
            printf("Chegada do processo: P%d\n", process.number);

            return true;
        }
    }
    return false;
}

bool hasInterruption(Process current, int quantum, bool flagTime)
{

    if (current.quantumCount == quantum)
    {
        printf("fim de quantum: P%d\n", current.number);
        removeData();
        insert(current);
        return true;
    }
    for (int i = 0; i < current.numberIO; i++)
    {
        if (current.interruptions[i] == (current.startDuration - current.duration))
        {
            printf("operação de I/O: P%d\n", current.number);
            current.interruptions[i] = 0;
            if (flagTime)
            {
                Process lastData = processArray[size() - 1];
                processArray[size() - 1] = current;
                removeData();
                insert(lastData);
            }
            else
            {
                removeData();
                insert(current);
            }
            return true;
        }
    }
    return false;
}

void incrementProcess(Process *process, int time)
{
    // processo acabou de começar
    if(process->duration == process->startDuration){
        process->startTime = time;
    }
    process->duration--;
    process->quantumCount++;
}

void roundRobbin(Process *processes)
{
    int totalDuration = calculateTotalDuration(processes);
    int quantum = 4;


    for (int t = 0; t < totalDuration + 1; t++)
    {
        printf("\n\nTempo: %d - ", t);
        bool arriveProcess = setProcessOnTime(processes, t);

        if (!isEmpty())
        {
            Process *current = first();

            if (hasInterruption(*current, quantum, arriveProcess))
            {
                current->quantumCount = 0;
                showQueue();
            }
            else
            {

                showQueue();

                if (current->duration == 0)
                {
                    printf("fim de processo: P%d\n", current->number);
                    current->finalTime = t;
                    printf("Tempo de espera: %d ms\n", current->finalTime - current->startTime);
                    removeData();
                }
            }
            printf("Na CPU: P%d \n", current->number);
            incrementProcess(current, t);
        }
        else if (t > totalDuration)
        {
            break;
        }
    }
}

void calculate(Process *processes)
{
    createQueue();

    roundRobbin(processes);
}

#include "../include/input.h"
#include "../include/process.h"
#include "../include/cpu.h"
#include "../include/output.h"

/*
Alterna entre processos (preempção)
Existência de uma fatia de tempo para execução (quantum)
Percorre a fila circularmente, alocando a CPU a cada processo por 1 quantum de tempo
O processo pode parar sua execução antes de terminar seu 1 quantum de tempo
*/

#define MAX_ARRIVAL 99999999

void calculate(Process *processes)
{
    CPU* cpuTimes = malloc(sizeof(CPU) * 15);

    CPU actualProcess;
    int quantum = 4;

    int minArrival = MAX_ARRIVAL;
    Process* firstProcess = NULL;

    // check based on arrival
    for (int i = 0; i < numberProcess; i++)
    {
        if(processes[i].arrival < minArrival){
            minArrival = processes[i].arrival;
            firstProcess = &processes[i];
        }
    }
    actualProcess.time = 0;
    actualProcess.description = "início";
    actualProcess.processInCpu = firstProcess;
    actualProcess.queueProcess =  firstProcess;
    actualProcess.sizeQueueProcess = 1;

    cpuTimes[actualProcess.time] = actualProcess;

    

    printStatus(cpuTimes);
}

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

CPU getFirstProcessInQueue(Process* processes){
    int minArrival = processes[0].arrival;
    Process* firstProcess = NULL;

    // check based on arrival
    for (int i = 0; i < numberProcess; i++)
    {
        if(processes[i].arrival < minArrival){
            minArrival = processes[i].arrival;
            firstProcess = &processes[i];
        }
    }
    CPU currentProcess = {0, "inicio", 1, firstProcess, firstProcess};
    return currentProcess;
}



void calculate(Process *processes)
{
    CPU* cpuTimes = malloc(sizeof(CPU) * 15);

    CPU currentProcess = getFirstProcessInQueue(processes);
    int quantum = 4;

    cpuTimes[currentProcess.time] = currentProcess;

    printStatus(cpuTimes);
}

#include "../include/input.h"
#include "../include/process.h"
#include "../include/queue.h"

/* INSERTION */

bool isInserting(Process* processes, int time){
    for (int n = 0; n < numberProcess; n++){
        Process process = processes[n];
        if (process.arrival == time)
            return true;
    }
}

bool onInsertAtTime(Process *processes, int time){
    
    for (int n = 0; n < numberProcess; n++){
        Process process = processes[n];
        if (process.arrival == time){
            insert(process);
            printf("Chegada do processo: P%d\n", process.number);
            return true;
        }
    }
    return false;
}



/* INTERRUPTION */

bool isInterrupting(int quantum){

    Process* current = first();

    if(current){
    
      if (current->quantumCount == quantum)
          return true;

      for (int i = 0; i < current->numberIO; i++){

          int remainingTime = current->startDuration - current->duration;

          if (current->interruptions[i] == remainingTime)
            return true;
              
      }
    }

    return false;

}

void onInterruptProcess(int quantum){

    Process current = *first();

    bool isQuantumInterruption = current.quantumCount == quantum;

    if (isQuantumInterruption)
      printf("fim de quantum: P%d\n", current.number);
    else
      printf("operação de I/O: P%d\n", current.number);

    /* Move to the end of queue*/
    removeData();
    insert(current);

    (first())->quantumCount = 0;
}

/* Utils */
void incrementProcess(int time){
    Process* current = first();

    if (current->duration == current->startDuration)
        current->startTime = time;

    current->duration--;
    current->quantumCount++;
}

int calculateTotalDuration(Process *processes){
    int duration = 0;
    for (int i = 0; i < numberProcess; i++)
        duration += processes[i].duration;
    return duration;
}

void calculateProcessWaitTime(int* totalWaitTime){
  Process* current = first();

  int waitTime = (current->finalTime - current->startTime);
  (*totalWaitTime) += waitTime;
  printf("Tempo de espera: %d ms\n", waitTime);
}

float calculateWaitTimeAverage(int* totalWaitTime){
  return *totalWaitTime / numberProcess;
}

bool onExitProcess(int time, int* totalWaitTime){
  Process* current = first();

  if (current->duration == 0){
      printf("fim de processo: P%d\n", current->number);
      current->finalTime = time;
      calculateProcessWaitTime(totalWaitTime);
      removeData();
  }
}



void roundRobbin(Process *processes){

    int totalDuration = calculateTotalDuration(processes);
    int quantum = 4;
    int totalWaitTime = 0;

    for (int t = 0; t < totalDuration; t++){
      printf("\n\nTempo: %d - ", t);
      bool hasInsertion = isInserting(processes, t);
      bool hasInterrupt = isInterrupting(quantum);

      if(hasInsertion && hasInterrupt){
        onInterruptProcess(quantum);
        onInsertAtTime(processes, t);
      }
      else if (hasInsertion)
        onInsertAtTime(processes, t);
      else if (hasInterrupt)
        onInterruptProcess(quantum);
      

      showQueue();
      
      onExitProcess(t, &totalWaitTime);
      printf("Na CPU: P%d \n",  first()->number);
      incrementProcess(t);
    }

    printf("Tempo médio de espera = %.2f", calculateWaitTimeAverage(&totalWaitTime));
}

void calculate(Process *processes){
    createQueue();
    roundRobbin(processes);
}

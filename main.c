#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "include/algorithm.h"
#include "include/input.h"
#include "include/process.h"
#include "include/queue.h"

int main(){
    int quantum;
    printf("Digite o valor do quantum: ");
    scanf("%d", &quantum);
    
    Process* processes = input();
    calculate(processes, quantum);

    clearQueue();
    clearProcess(processes);

    return 0;
}

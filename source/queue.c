#include "../include/queue.h"

Process *processArray;
int itemCount = 0;

void createQueue(){
    processArray = malloc(sizeof(Process) * numberProcess);
}

Process *first(){
    if (!isEmpty())
        return processArray;
    return NULL;
}

bool isEmpty(){
    return itemCount == 0;
}

int size(){
    return itemCount;
}

void push(Process data){
    processArray[size()] = data;
    itemCount++;
}

Process pop(){
    if (!isEmpty()){
        Process data = *(first());

        for (int i = 0; i < size() - 1; i++){
            processArray[i] = processArray[i + 1];
        }

        itemCount--;
        return data;
    }
}

void showQueue(){
    printf("Fila: ");
    for (int i = 0; i < size(); i++){
        if (processArray[i].duration)
            printf("P%d (%d) - ", processArray[i].number, processArray[i].duration);
    }
    printf("\n");
}

void clearQueue(){
  free(processArray);
}
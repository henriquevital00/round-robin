#include "../include/queue.h"

Process *processArray;
int front = 0;
int rear = -1;
int itemCount = 0;

void createQueue()
{
    processArray = malloc(sizeof(Process) * numberProcess);
}

Process peek()
{
    return processArray[front];
}

bool isEmpty()
{
    return itemCount == 0;
}

int size()
{
    return itemCount;
}

void insert(Process data)
{
    processArray[++rear] = data;
    itemCount++;
}

Process removeData()
{
    Process data = processArray[front++];

    itemCount--;
    return data;
}
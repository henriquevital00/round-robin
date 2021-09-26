#include "../include/queue.h"

Process *processArray;
int rear = -1;
int itemCount = 0;

void createQueue()
{
    processArray = malloc(sizeof(Process) * numberProcess);
}

Process* first()
{
    if (!isEmpty())
        return processArray;
    return NULL;
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
    processArray[size()] = data;
    itemCount++;
}

Process removeData()
{
    if (!isEmpty())
    {
        Process data = *(first());
        for (int i = size() - 1; i > 0; i--)
            processArray[i - 1] = processArray[i];

        itemCount--;
        return data;
    }
    return;
}

void showQueue()
{
    printf("Queue: ");
    for (int i = 0; i < size(); i++)
    {
        printf("%d ", processArray[i].number);
    }
    printf("\n");
}
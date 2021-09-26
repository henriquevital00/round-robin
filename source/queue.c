#include "../include/queue.h"

Process *processArray;
int rear = -1;
int itemCount = 0;

void createQueue()
{
    processArray = malloc(sizeof(Process) * numberProcess);
}

Process *first()
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

        for (int i = 0; i < size() - 1; i++)
        {
            processArray[i] = processArray[i+1];
        }

        itemCount--;
        return data;
    }
}

void showQueue()
{
    printf("Fila: ");
    for (int i = 0; i < size(); i++)
    {
      if (processArray[i].duration)
        printf("P%d (%d) - ", processArray[i].number, processArray[i].duration);
    }
    printf("\n");
}
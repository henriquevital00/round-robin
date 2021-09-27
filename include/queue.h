#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "process.h"

Process *processArray;
int rear;
int itemCount;

void createQueue();
Process* first();
bool isEmpty();
int size();
void push(Process data);
Process pop();
void showQueue();

#endif
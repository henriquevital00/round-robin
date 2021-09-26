#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "include/algorithm.h"
#include "include/input.h"
#include "include/process.h"

int main()
{
    int var = 5;
    Process* processes = input();
    calculate(processes);
    clearProcess(processes);

    return 0;
}
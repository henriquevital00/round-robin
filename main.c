#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "include/algorithm.h"
#include "include/input.h"
#include "include/process.h"

int main()
{
    //Process* processes = input();

    Process p1;
    p1.number = 1;
    p1.duration = 9;
    p1.arrival = 10;
    p1.numberIO = 4;
    p1.startDuration = 9;
    p1.quantumCount = 0;
    int interrumptios1[4] = {2, 4, 6, 8};
    p1.interruptions = interrumptios1;

    Process p2;
    p2.number = 2;
    p2.duration = 10;
    p2.arrival = 4;
    p2.numberIO = 1;
    p2.startDuration = 10;
    p2.quantumCount = 0;
    int interrumptios2[1] = {5};
    p2.interruptions = interrumptios2;

    Process p3;
    p3.number = 3;
    p3.duration = 5;
    p3.arrival = 0;
    p3.numberIO = 1;
    p3.startDuration = 5;
    p3.quantumCount = 0;
    int interrumptios3[1] = {2};
    p3.interruptions = interrumptios3;

    Process p4;
    p4.number = 4;
    p4.duration = 7;
    p4.arrival = 1;
    p4.numberIO = 2;
    p4.startDuration = 7;
    p4.quantumCount = 0;
    int interrumptios4[2] = {3, 6};
    p4.interruptions = interrumptios4;

    Process p5;
    p5.number = 5;
    p5.duration = 2;
    p5.arrival = 17;
    p5.numberIO = 0;
    p5.startDuration = 2;
    p5.quantumCount = 0;

    Process processesArrayu[5] = {p1, p2, p3, p4, p5};
    Process *processes = processesArrayu;
    numberProcess = 5;
    calculate(processes);
    //clearProcess(processes);

    return 0;
}
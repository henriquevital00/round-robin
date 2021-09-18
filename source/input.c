#include "../include/input.h"
#include "../include/process.h"

Process* arrayProcessos;
Process* receberInput()
{
    int numberProcess = 0;
    int numberIO = 0;

    printf("Quantos processos você deseja inserir? \n");
    scanf("%d", &numberProcess);

    Process arrayProcess[numberProcess];

    for (int i = 0; i < numberProcess; i++)
    {
        Process process;

        printf("Criando o processo %d \n", i + 1);
        printf("Qual a duração do processo? \n");
        scanf("%d", &process.duration);

        printf("Qual a chegada do processo? \n");
        scanf("%d", &process.arrival);

        printf("Quantas I/O existem no processo? \n");
        scanf("%d", &numberIO);

        int arrayIO[numberIO];

        for (int j = 0; j < numberIO; j++)
        {
            printf("Quando ocorre a I/O? \n");
            scanf("%d", &arrayIO[j]);
        }
        process.interruptions = arrayIO;

        arrayProcess[i] = process;
    }

    arrayProcessos = arrayProcess;
    return arrayProcessos;
}
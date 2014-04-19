#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "xorerFunct.h"
#include "misc.h"
#include <string.h>
#include <sys/wait.h>

#define _RD 0
#define _WR 1

#define P 2

int main (int argc, char* argv[])
{

	if (argc < 2)
	{
		printf("Falta el nombre del archivo\n");
		return 1;
	}

	FILE* ptrFile ;
	char fname[strlen(argv[1])+1];  
	long fsize;
	long nbytes;
	int pid;
	strcpy(fname, argv[1]);

	ptrFile = fopen(fname, "r");

	if (ptrFile!=NULL)
	{
		fsize = fsof(ptrFile);
		nbytes = fsize/P;
		if((fsize % P)!=0){// si no es división exacta, le da un byte más.
			nbytes++;
		}
	}
	else
	{
		printf("Error al abrir el archivo\n");
		return 1;
	} 

	int** pipes = (int**) malloc(sizeof(int*)*2*P);

	for (int i=0; i< (2*P); i++)
	{
		pipes[i] = (int*) malloc(sizeof(int)*2);
	}

	for (int i=0; i< (2*P); i++)
	{
		pipe(pipes[i]);
	}

	printf("Los valores de los pipes son:\n\n");
	printf("\tR\tW\n");
	for (int i=0; i< (2*P); i++)
	{
		printf("p%d:\t%d\t%d \n", i, pipes[i][_RD], pipes[i][_WR]);
	}

	for (int i=0; i< P; i++)
	{
		pid = fork();

		if (pid == -1)
		{
			printf("No se pudo crear al hijo \n");
			return 1;
		}
		else if (pid == 0) //hijo
		{
			com_p* pipesHijo;
			switch (i)
			{
				case 0:
					pipesHijo = new_compipe(-1,-1,pipes[0][_WR], pipes[1][_RD]);
					break;
				default:
					pipesHijo = new_compipe(pipes[i*2-2][_RD], pipes[i*2-1][_WR], pipes[i*2][_WR], pipes[i*2+1][_RD]);
					break;

			}
			printf("Hijo %d creado \n", i+1);

			int ok = comunicar(fname, i+1, i*nbytes, nbytes, pipesHijo);

			if (ok !=0)
			{
				printf("Algo andubo mal \n");
			}
			return 0; 
		}
	}

	// Ejecucion del padre
	
	int ok = crear_xor(fname, nbytes, pipes[P*2-2][_RD], pipes[P*2-1][_WR]);

	if (ok==0)
	{
		printf("todo a salido ok ( creo )\n");
	}
	else
	{
		printf("Hubieron problemas\n");
	} 
	/*
	printf("Esperando último hijo...\n");
	waitpid(pid, NULL, 1);
	printf("Último hijo terminado.\n");
	*/
	return 0;
}

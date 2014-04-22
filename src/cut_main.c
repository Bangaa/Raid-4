#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "xorerFunct.h"
#include "misc.h"
#include <string.h>
#include <sys/wait.h>

#define _RD 0
#define _WR 1

#define P 3

int main (int argc, char* argv[])
{

	if (argc < 2)
	{
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
		fclose(ptrFile);
	}
	else
	{
		printf("Error: No se encontro el archivo <%s>. Operacion abortada\n", fname);
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

	for (int i=0; i< P; i++)
	{
		pid = fork();

		if (pid == -1)
		{
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

			int ok = comunicar(fname, i+1, i*nbytes, nbytes, pipesHijo);

			return 0; 
		}
	}

	// Ejecucion del padre
	
	int ok = crear_xor(fname, nbytes, pipes[P*2-2][_RD], pipes[P*2-1][_WR]);

	if (ok==0)
	{
		printf("<%s> fue dividido con exito en %i partes.\n", argv[1], P);
	}
	else
	{
		printf("Error: La division no ha podido llevarse a cabo\n");
	} 

	return 0;
}

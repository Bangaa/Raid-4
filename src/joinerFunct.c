#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "joinerFunct.h"
#include "misc.h"

int missing(char fname[], int total)
{
	FILE * sfile;
	int i_faltante = 0;
	int cuantas=0;

	for (int i=1; i<= total; i++)
	{
		if ((sfile = fopen_part(fname, i, "r")) != NULL)
			fclose(sfile);

		else
		{
			i_faltante = i;
			cuantas++;
		} 

		if (cuantas > 1)
		{
			return -1; 
		} 
	}

	return i_faltante; 
}

int recovery(char fname[], int n_proc, int i_faltante, com_p* pipes )
{
	FILE* file_in;				//< Archivo de entrada y salida
	void* data_f;				//< Bytes leidos del archivo
	void* data_p;				//< Bytes leidos del pipe
	int rdbytes_f, rdbytes_p;	//< Numero de bytes leidos del archivo y pipe

	if (i_faltante != n_proc)
	{
		file_in = fopen_part(fname, n_proc, "r");
	}
	else
	{
		file_in = fopen_xor(fname, "r");
		fseek(file_in, 2*sizeof(int), SEEK_SET);
	}

	if ((data_f = malloc(TASA)) == NULL)
		return 1;		// No hay espacio en memoria

	if ((data_p = malloc(TASA)) == NULL)
		return 1;		// No hay espacio en memoria 

	do
	{
		rdbytes_f = rdbytes_p = 0;
		rdbytes_f = fread(data_f, 1, TASA, file_in);

		if (pipes->left_in != -1)
		{
			rdbytes_p = read(pipes->left_in, data_p, TASA);
			write(pipes->left_out, "1", 2);
		}

		int hndata = (rdbytes_f > rdbytes_p ? rdbytes_f:rdbytes_p);	//numero mas grande de datos

		limpiar(data_f, rdbytes_f, TASA);
		limpiar(data_p, rdbytes_p, TASA);

		xor_(data_f, data_p, TASA);

		char trash[2];

		write(pipes->right_out, data_f, hndata);
		
		if(feof(file_in)) 
			break;

		else
		{
			read(pipes->right_in, trash, 2);
		}

	}
	while (!feof(file_in));

	free(data_f);
	free(data_p);

	fclose(file_in);

	return 0;
}

int rebuild(char fname[], int i_faltante, int left_in, int left_out)
{
	FILE* file_out, * filexor;
	long bytes_left;
	void* data_p;
	char* foutname = (char*) malloc(strlen(fname)+ 10);
	char* xorname = (char*) malloc(strlen(fname)+ 5);

	if ((filexor = fopen_xor(fname, "r")) == NULL)
		return 1;

	if ((data_p = malloc(TASA)) == NULL)
		return 1;

	bytes_left = fsof(filexor)-2*sizeof(int);
	fclose(filexor);

	file_out = fopen_part(fname, i_faltante, "w");

	while (bytes_left > 0)
	{
		int rdbytes_p;

		rdbytes_p = read(left_in, data_p, TASA);
		write(left_out, "1", 2);
		
		bytes_left-= rdbytes_p;
		
		fwrite(data_p, 1, rdbytes_p, file_out); 
	}
	fclose(file_out); 

	return 0;
}

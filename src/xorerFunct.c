#include <stdio.h>
#include <unistd.h>
#include "xorerFunct.h"
#include <string.h>

#define TASA 2000

com_p* new_compipe(int p_in_l, int p_out_l, int p_out_r, int p_in_r)
{
	com_p* pipes = (com_p) malloc(sizeof(com_p));

	pipes->left_in = p_in_l;
	pipes->left_out = p_out_l;
	pipes->right_in = p_in_r;
	pipes->right_out = p_out_r;

	return pipes;
}

int comunicar(char fname[], int n_proc, long r_from, long nbytes, com_p* pipes )
{
	FILE* file_in, *file_out;	//< Archivo de entrada y salida
	void* data_f;				//< Bytes leidos del archivo
	void* data_p;				//< Bytes leidos del pipe
	long bytes_left = nbytes;	//< Bytes que me quedan por leer
	int rdbytes_f, rdbytes_p;	//< Numero de bytes leidos del archivo y pipe
	char* foutname = (char*) malloc(strlen(fname)+6);

	foutname = strcat(fname, "part");
	foutname = strcat(fname, inttostring(n_proc));

	if ((file_in = fopen(fname, "r")) == NULL)
		return 1;		// No existe fichero

	if (fseek(file_in, r_from, SEEK_SET) != 0)
		return 1;		// El archivo no es tan largo

	if ((data_f = malloc(TASA)) == NULL)
		return 1;		// No hay espacio en memoria

	file_out = fopen(foutname, "w");

	while (bytes_left > 0)
	{
		rdbytes_f = rdbytes_p = 0;

		if (!feof(file_in)) // respaldo
		{ 
			if (bytes_left >= TASA)
			{
				rdbytes_f = fread(data_f, 1, TASA, file_in);
				bytes_left -= rdbytes_f;
			}
			else if (bytes_left < TASA)
			{
				rdbytes_f = fread(data_f, 1, bytes_left, file_in);
				bytes_left -= rdbytes_f;
			}

			fwrite(data_f, 1, rdbytes_f, file_out);
		}

		if (pipes->left_in != -1)	// pueden haber problemas con este bloque, revisar luego
		{
			rdbytes_p = read(pipes->left_in, data_p, TASA);
			write(pipes->left_out, "1", 2);
		}

		blanquear(data_f, rdbytes_f, TASA);
		blanquear(data_p, rdbytes_p, TASA); 

		xor_(data_f, data_p, rdbytes_p);

		char trash[2];

		read(pipes->right_in, trash, 2);
		write(pipes->right_out, data_f, rdbytes_p);

	} 

	free(data_f);
	free(data_p);

	return 0;
}

void xor_(void* ptr1, void* ptr2, int lenght)
{
	for (int i=0; i < lenght; i++)
	{
		ptr1[i] = ptr1[i] ^ ptr2[i]; 
	}
}

void blanquear(void* ptr, int wspaces, int lenght)
{
	for (int i=wspaces+1; i<lenght; i++)
	{
		ptr[i] = 0;
	}
}

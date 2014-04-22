#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "misc.h"

int missing(char fname[], int total)
{
	FILE * sfile;
	int i_faltante;
	int cuantas=0;
	int fnamelenght = strlen(fname);
	char sname = (char*) malloc(fnamelenght + 5);

	strcpy(sname, fname);

	for (int i=1; i<= total; i++)
	{
		char * num = inttostring(i);
		strcat(sname, num);

		if ((sfile = fopen(sname, "r")) != NULL)
			fclose(sfile);

		else
		{
			i_faltante = i;
			cuantas++;
		} 

		if (cuantas > 1)
		{
			free(num);
			return -1; 
		}

		sname[fnamelenght] = '\0';
		free(num);
	}

	return i_faltante; 
}

int recovery(char fname[], int n_proc, int imissing, int sobra, com_p* pipes )
{
	FILE* file_in;	//< Archivo de entrada y salida
	void* data_f;				//< Bytes leidos del archivo
	void* data_p;				//< Bytes leidos del pipe
	long bytes_left;			//< bytes que me faltan por leer
	int rdbytes_f, rdbytes_p;	//< Numero de bytes leidos del archivo y pipe
	char* finname = (char*) malloc(strlen(fname)+10);

	strcpy(finname, fname);
	strcat(finname, ".XOR");

	if ((file_in = fopen(finname, "r")) != NULL)
	{
		bytes_left = fsof(file_in);
		fseek(file_in, 8, SEEK_SET);
	}
	else
		return 1;

	if (imissing != n_proc)
	{
		fclose(file_in);
		char * num = inttostring(n_proc);
		finname[strlen(fname)] = '\0';
		strcat(finname, num);


	}



	if (fseek(file_in, r_from, SEEK_SET) != 0)
		return 1;		// El archivo no es tan largo

	if ((data_f = malloc(TASA)) == NULL)
		return 1;		// No hay espacio en memoria

	if ((data_p = malloc(TASA)) == NULL)
		return 1;		// No hay espacio en memoria


	strcpy(finname, fname);
	strcat(finname, ".part");
	strcat(finname, inttostring(n_proc));

	file_out = fopen(finname, "w");

	while (bytes_left > 0)
	{
		rdbytes_f = rdbytes_p = 0;
		if (!feof(file_in)) // respaldo
		{ 
			if (bytes_left >= TASA)
			{
				rdbytes_f = fread(data_f, 1, TASA, file_in);
			}
			else if (bytes_left < TASA)
			{
				rdbytes_f = fread(data_f, 1, bytes_left, file_in);
			}

			int aux = fwrite(data_f, 1, rdbytes_f, file_out);
		}

		if (pipes->left_in != -1)
		{
			rdbytes_p = read(pipes->left_in, data_p, TASA);
			write(pipes->left_out, "1", 2);
		}

		blanquear(data_f, rdbytes_f, TASA);
		blanquear(data_p, rdbytes_p, TASA);

		xor_(data_f, data_p, TASA);

		char trash[2];
		int cuantos = (rdbytes_p >rdbytes_f ? rdbytes_p:rdbytes_f);

		write(pipes->right_out, data_f, cuantos);
		
		bytes_left -= cuantos;

		if(bytes_left<=0){//no espera confirmación al enviar el último pack de datos.
			break;
		}
		else
		{
			read(pipes->right_in, trash, 2);
		}

	} 

	free(data_f);
	free(data_p);

	fclose(file_in);
	fclose(file_out);

	return 0;
}

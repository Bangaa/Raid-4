#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "xorerFunct.h"
#include "misc.h"
#include <string.h>


com_p* new_compipe(int p_in_l, int p_out_l, int p_out_r, int p_in_r)
{
	com_p* pipes = (com_p*) malloc(sizeof(com_p));

	pipes->left_in = p_in_l;
	pipes->left_out = p_out_l;
	pipes->right_in = p_in_r;
	pipes->right_out = p_out_r;

	return pipes;
}

int comunicar(char fname[], int n_proc, long r_from, long nbytes, com_p* pipes )
{
	printf("%d: Mis pipes\n", n_proc); //DEBUG
	printf("%d: \tR\tW\n", n_proc); //DEBUG
	printf("%d: l|\t%d\t%d \n", n_proc, pipes->left_in, pipes->left_out); //DEBUG
	printf("%d: r|\t%d\t%d \n", n_proc, pipes->right_in, pipes->right_out); //DEBUG
	FILE* file_in, *file_out;	//< Archivo de entrada y salida
	void* data_f;				//< Bytes leidos del archivo
	void* data_p;				//< Bytes leidos del pipe
	long bytes_left = nbytes;	//< Bytes que me quedan por leer
	int rdbytes_f, rdbytes_p;	//< Numero de bytes leidos del archivo y pipe
	char* foutname = (char*) malloc(strlen(fname)+6);

	if ((file_in = fopen(fname, "r")) == NULL)
		return 1;		// No existe fichero

	if (fseek(file_in, r_from, SEEK_SET) != 0)
		return 1;		// El archivo no es tan largo

	if ((data_f = malloc(TASA)) == NULL)
		return 1;		// No hay espacio en memoria

	if ((data_p = malloc(TASA)) == NULL)
		return 1;		// No hay espacio en memoria

	foutname = strcat(fname, ".part");
	foutname = strcat(fname, inttostring(n_proc));

	file_out = fopen(foutname, "w");

	while (bytes_left > 0)
	{
		rdbytes_f = rdbytes_p = 0;

		if (!feof(file_in)) // respaldo
		{ 
			printf("%d: voy a leer de archivo\n", n_proc); //DEBUG
			if (bytes_left >= TASA)
			{
				rdbytes_f = fread(data_f, 1, TASA, file_in);
				bytes_left -= rdbytes_f;
			}
			else if (bytes_left < TASA)
			{
				printf("%d:############################################\n",n_proc);
				rdbytes_f = fread(data_f, 1, bytes_left, file_in);
				bytes_left -= rdbytes_f;
			}
			printf("%d: lei: %d\n", n_proc, rdbytes_f); //DEBUG
			printf("%d: voy a escribir a archivo\n", n_proc); //DEBUG

			fwrite(data_f, 1, rdbytes_f, file_out);
			printf("%d: escribi archivo\n", n_proc); //DEBUG
		}

		if (pipes->left_in != -1)	// pueden haber problemas con este bloque, revisar luego
		{
			printf("%d: voy a leer del pipe %d...\n", n_proc, pipes->left_in); //DEBUG
			rdbytes_p = read(pipes->left_in, data_p, TASA);
			printf("%d: pipe leido\n", n_proc); //DEBUG
			printf("%d: enviando confirmacion a pipe %d...\n", n_proc, pipes->left_out); //DEBUG
			write(pipes->left_out, "1", 2);
			printf("%d: confirmacion enviada\n", n_proc); //DEBUG
		}


		blanquear(data_f, rdbytes_f, TASA);
		blanquear(data_p, rdbytes_p, TASA);

		printf("%d: voy a hacer el xor...\n", n_proc); //DEBUG
		xor_(data_f, data_p, TASA);
		printf("%d: xor hecho\n", n_proc); //DEBUG

		char trash[2];
		int cuantos = (rdbytes_p >rdbytes_f ? rdbytes_p:rdbytes_f);

		printf("%d: enviando datos por pipe %d...\n", n_proc, pipes->right_out); //DEBUG
		write(pipes->right_out, data_f, cuantos);
		printf("%d: datos enviados \n", n_proc); //DEBUG
		if(bytes_left==0){//no espera confirmación al enviar el último pack de datos.
			break;
		}
		printf("%d: voy a leer confirmacion de envio del pipe %i...\n", n_proc, pipes->right_in); //DEBUG
		read(pipes->right_in, trash, 2);
		printf("%d: confirmacion leida\n", n_proc); //DEBUG

	} 
	printf("%d: listo\n", n_proc); //DEBUG

	fclose(file_out);
	fclose(file_in);
	free(data_f);
	free(data_p);

	return 0;
}

void xor_(void* ptr1, void* ptr2, int lenght)
{
	char* cpptr1 = ptr1;
	char* cpptr2 = ptr2;

	for (int i=0; i < lenght; i++)
	{
		cpptr1[i] = cpptr1[i] ^ cpptr2[i]; 
	}
}

void blanquear(void* ptr, int wspaces, int lenght)
{
	char* cpptr = ptr;

	for (int i=wspaces+1; i<lenght; i++)
	{
		cpptr[i] = '\0';
	}
}

int crear_xor(char fname[], long nbytes, int left_in, int left_out)
{
	FILE* fout;
	long bytes_left = nbytes;
	char* fout_name;
	void* data_p;

	fout_name = strcat(fname, ".XOR");

	if ((fout = fopen(fout_name, "w")) == NULL)
		return 1;

	if ((data_p = malloc(TASA)) == NULL)
		return 1;

	while (bytes_left > 0)
	{
		int rdbytes_p;

		printf("P: voy a leer del pipe %d...\n", left_in);	//DEBUG
		rdbytes_p = read(left_in, data_p, TASA);
		printf("P: pipe leido %d bytes\n", rdbytes_p);	//DEBUG
		printf("P: voy a escribir confirmacion ...\n");	//DEBUG
		write(left_out, "1", 2);
		printf("P: confirmacion enviada\n");	//DEBUG
		
		bytes_left-= rdbytes_p;
		
		printf("P: voy a escribir en archivo\n");	//DEBUG
		fwrite(data_p, 1, rdbytes_p, fout);

	}
	printf("P: listo\n");	//DEBUG
	fclose(fout);

	return 0;
}

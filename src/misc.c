/**
 *	Se debe compilar con std 99:
 *	gcc -std=c99
 */

#include <stdlib.h>
#include <stdio.h>
#include "misc.h"

char * inttostring(int num)
{
	char cuantos = 0;
	char * str;
	int left = num;

	while (left!=0)
	{
		left = left/10;
		cuantos++;
	}

	if ((str = (char*)malloc(cuantos+1)) == NULL)
		return NULL;

	for (int i=cuantos-1; i>=0; i--)
	{
		str[i] = BASE_ASCII + num%10;
		num/= 10;
	}
	str[cuantos]=0;

	return str; 
}

long fsof(FILE * ptrFILE)
{
	long size;
	long current;

	if (ptrFILE == NULL)
	{
		return -1;
	}

	current = ftell(ptrFILE);

	fseek(ptrFILE, 0, SEEK_END);
	size = ftell(ptrFILE);
	fseek(ptrFILE, current, SEEK_SET);

	return size; 
}



/**
 *	Se debe compilar con std 99:
 *	gcc -std=c99
 */

#include <stdlib.h>
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



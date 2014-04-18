#define BASE_ASCII ((int)'0') //<! Valor ASCII del 0 

/**
 * Funcion que transforma un entero en un string.
 * @param num Es el entero que se transformara
 * @return El string terminado en caracter NULL que represente al entero
 */
char * inttostring(int num);

/**
 * Dice el tamaño del archivo del descriptor ptrFILE.
 * @param ptrFILE Es el puntero que apunta al archivo ya abierto
 * @return El tamaño del archivo en bytes si es que no hubo problemas, o -1 si
 * 		el puntero no ha sido inicializado
 */
long fsof(FILE * ptrFILE);

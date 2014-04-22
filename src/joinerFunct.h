
/**
 * Encuantra la parte faltante del archivo fname luego de ser cortado
 * por el programa CUT.
 *
 * @param fname Es el nombre del archivo original
 * @param total Es el numero total de partes en que fue cortado fname
 * @return El numero de la parte que falta o -1 si falta mas de una parte
 *
 *  - Ej. Si falta la parte 3 (<archivo>.part3) devuelve 3
 */
int missing(char fname[], int total);

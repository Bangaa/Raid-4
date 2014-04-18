/**
 * Estructura que encapsula los pipes.
 */
typedef struct
{
	int left_in, left_out;		//< pipes hacia el proceso hermano izquierdo
	int right_in, right_out;	//< pipes hacia el proceso hermano derecho
}com_p;

/**
 * Funcion que genera un nueva estructura com_p que tendra encapsulados
 * los descriptores.
 * @param p_in_l Es el descriptor del pipe del cual leer los bytes del proceso
 * 				hermano izquierdo.
 * @param p_out_l Es el descriptor del pipe en el cual se manda el mensaje de 
 * 				confirmacion de lectura al proceso hermano izquierdo.
 * @param p_out_r Es el descriptor del pipe en el cual mandar los bytes al 
 * 				proceso hermano derecho.
 * @param p_in_r Es el descriptor del pipe en al cual recibir el mensaje de 
 * 				confirmacion de lectura del proceso hermano derecho.
 */
com_p* new_compipe(int p_in_l, int p_out_l, int p_out_r, int p_in_r);

/**
 * Comunica los bytes leidos entre procesos hermanos. Hace que el proceso lea
 * del archivo fname cada cierta tasa de bytes y se los pase al hermano para
 * que le aplique el XOR. Escribe ademas los bytes leidos en su archivo de 
 * respaldo, y dependiendo el numero del proceso va a escribir en un archivo de
 * tipo .part[nro_proceso] o en uno .XOR
 *
 * @param fname Es el nombre del archivo del cual va a leer
 * @param n_proc Es el numero del proceso
 * @param r_from Indica desde donde leera el proceso
 * @param nbytes Indica la cantidad de bytes que debe leer
 * @param pipes Es el puntero a com_p de donde sacara los descriptores de los 
 * 			pipes que va a utilizar
 */
int comunicar(char fname[], int n_proc, long r_from, long nbytes, com_p* pipes );

/**
 * Rellena con ceros los espacios de la memoria no ocupados.
 * @param ptr Es el puntero al espacio de memoria que queremos blanquear
 * @param wspaces Son los espacios que si estamos ocupando en bytes.
 * @param lenght Es el tamanio de la memoria en bytes
 */
void blanquear(void* ptr, int wspaces, int lenght);
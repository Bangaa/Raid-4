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


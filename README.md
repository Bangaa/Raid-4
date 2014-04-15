Algoritmos
==========

Algoritmo para el XORer
-----------------------

__Padre__

Una vez dados las _P_ partes en las que se dividira el archivo de entrada.

 * Se crearan _2*(P-1)_ pipes los cuales serviran como comunicacion entre hijos
 consecutivos. Uno para enviar los datos leidos del archivo de entrada y el
 otro para recibir la señal de que han sido leidos.
 * Para cada _i_ de 1 a _P_ hacer:
   * Se crea un proceso hijo.
   * Si el pid del proceso creado es 0 (hijo) entonces se llamara a la funcion execve() o derivado para convertir al proceso en XOR.
   * (Se deben pasar a este hijo como argumento: el nombre del archivo a dividir junto con los descriptores de los pipes de los hermanos, y el numero de proceso)
 * Esperar a que los hijos terminen de hacer lo que tengan que hacer

__Hijos__

 * Se debe crear un FILE\* para lectura y otro para escritura.
 * Mientras no lea todo mi bloque asignado hacer:
   * leer 100 bytes del bloque
   * escribir los bytes en el archivo de salida: `<nombre_archivo>.part[numero_proceso]`
   * Si el descriptor del pipeIN izquierdo no es -1
   * leer los bytes del pipe
   * mandar un mensaje por pipeOUT izquierdo que se ha leido
   * hacer la operacion XOR con los bytes leidos del archivo
   * Si el descriptor del pipeIN derecho no es -1
   * leer mensaje del pipeIN derecho
   * escribir los bytes en el pipeOUT derecho
 * cerrar ambos FILE\*
 * terminar

Algoritmo para el JOINer
------------------------

...

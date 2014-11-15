# Laboratorio N°1 SO: RAID 4

---
## Acerca del programa

(Se llenara mas adelante). Para mas info pinche [aquí](http://es.wikipedia.org/wiki/RAID#RAID_4 "Raid 4")

## Compilación

Ubíquese en la carpeta principal (donde se encuentra el Makefile) y ejecute `make`
para compilar los 3 ejecutables: raid4, CUT y JOIN. El código objeto se compilara 
en la carpeta "build/obj" y los ejecutables en la carpeta "build/".


## Ejecución

Diríjase a la carpeta `build/'.

Para la ejecucion debe ejecutar el programa principal __`raid4`__ junto a las
opciones __`--cut N <input>`__ si quiere cortar el archivo _input_ en _N_ partes, o con
__`--join <archivo-original>`__ si quiere restaurar el archivo original.

Ejm:

> Si quiere cortar el archivo doc.pdf en 6 partes debe ejecutar:  
> __`$ ./raid4 --cut 6 doc.pdf`__  
>
> Si quiere volver volver a unir doc.pdf entonces:  
> __`$ ./raid4 --join doc.pdf`__

El programa JOIN recuperara la parte faltante - si es que hubiera - y unira todas
las partes para restaurar el programa original.

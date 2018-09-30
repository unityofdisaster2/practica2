/*
Definiciones de algoritmos de busqueda 
fecha: 30-septiembre-2018
version: 1.0.2
cambios respecto a version anterior: se agrega version de hilos de busqueda binaria
Autores: Raymundo Rosales Reyes, Martin Hernandez Cruz, Jose Manuel Martinez Quevedo 
*/

#include "busqueda.h"
#include "tiempo.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*cuando se va a a ejecutar programa en el prompt se debe ingresar como argumento opt
lo siguiente: 
1 tamanio del arreglo
2 numero buscado
3 indice del algoritmo que se desea utilizar
4 archivo con los numeros en el que requiera cada algoritmo
ejemplo:  ./prueba_busqueda 1000 322486 1 < 10millones.txt
*/
int main(int argc, char **argv)
{
    int opcion,tamanio,numero_buscado,i,j,respuesta;
    int *arreglo;

    double utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para medición de tiempos
    
    apu_raiz raiz;
    raiz = NULL;
    //se guardan valores ingresados en la linea de comando
    tamanio = atoi(argv[1]);
    numero_buscado = atoi(argv[2]);
    opcion = atoi(argv[3]);

    //se declaran variables con las que se manejaran los hilos
    valores_hilo *val_hilo;
    pthread_t hilo[4];
    pthread_attr_t atributos;
    arreglo = (int *)malloc(sizeof(int)*tamanio);
    //se llena el arreglo para las opciones que lo requieren previamente ordenado
    if (opcion == 1 || opcion == 2 || opcion == 4 || opcion == 5)
    {
        for(i = 0;i<tamanio;i++)
        {
            scanf("%d",&arreglo[i]);
        }
    }

    //se comienza a medir el tiempo
    uswtime(&utime0, &stime0, &wtime0);
    switch(opcion)
    {
        case 1:
            respuesta = busqueda_lineal(arreglo,tamanio,numero_buscado);
            if (respuesta != -1)
            {
                respuesta = 1;
            }
        break;
        case 2:
            respuesta = busqueda_binaria(arreglo,0,tamanio,numero_buscado);
            if (respuesta != -1)
            {
                respuesta = 1;
            }
        break;
        case 3:
            respuesta = tree_search(&raiz,numero_buscado,tamanio);
        break;
        case 4:
            //se inicializan variables que se utilizaran en la funcion de hilos

            pthread_attr_init(&atributos);
            
            val_hilo = (valores_hilo *)malloc(sizeof(valores_hilo));
            val_hilo->n = tamanio;
            val_hilo->arreglo = (int*)malloc(sizeof(int)*tamanio);
            val_hilo->arreglo = arreglo;
            val_hilo->numero_buscado = numero_buscado;
            val_hilo->respuesta = -1;
            for(j = 0; j<4; j++)
            {
                pthread_create(&hilo[j],&atributos,busqueda_lineal_hilos,val_hilo);
            }
            for(j = 0; j<4; j++)
            {
                pthread_join(hilo[j],NULL);		
            }            
            respuesta = val_hilo->respuesta;
        break;
        case 5:
            //se inicializan variables que se utilizaran en la funcion de hilos
            respuesta = busqueda_main(arreglo,tamanio,numero_buscado);
            if(respuesta !=-1)
            {

                pthread_attr_init(&atributos);
                
                val_hilo = (valores_hilo *)malloc(sizeof(valores_hilo));
                val_hilo->n = tamanio;
                val_hilo->arreglo = (int*)malloc(sizeof(int)*tamanio);
                val_hilo->arreglo = arreglo;
                val_hilo->numero_buscado = numero_buscado;
                val_hilo->respuesta = -1;
                for(j = 0; j<4; j++)
                {
                    pthread_create(&hilo[j],&atributos,busqueda_lineal_hilos,val_hilo);
                }
                for(j = 0; j<4; j++)
                {
                    pthread_join(hilo[j],NULL);		
                }            
                respuesta = val_hilo->respuesta;        
            }
                
        break;
        default:
        break;
    }
    //se termina de medir el tiempo
    uswtime(&utime1, &stime1, &wtime1);
	printf("%d,",  opcion);
    printf("%d,",numero_buscado);
    printf("%d,",tamanio);
    printf("%.10e,",  wtime1 - wtime0);
    printf("%d\n",respuesta);
    return 0;
}




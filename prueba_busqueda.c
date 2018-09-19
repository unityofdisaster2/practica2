/*
Archivo de pruebas
Autores: Raymundo Rosales Reyes, Martin, José Manuel
version: v1.0.0
*/

#include "busqueda.h"
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
    
    apu_raiz raiz;
    raiz = NULL;
    
    tamanio = atoi(argv[1]);
    numero_buscado = atoi(argv[2]);
    opcion = atoi(argv[3]);
    valores_hilo *val_hilo;
    pthread_t hilo[4];
    pthread_attr_t atributos;
    arreglo = (int *)malloc(sizeof(int)*tamanio);
    if (opcion == 1 || opcion == 2 || opcion == 4 || opcion == 5)
    {
        for(i = 0;i<tamanio;i++)
        {
            scanf("%d",&arreglo[i]);
        }
    }

    switch(opcion)
    {
        case 1:
            respuesta = busqueda_lineal(arreglo,tamanio,numero_buscado);
            if (respuesta != -1)
            {
                printf("numero encontrado en indice: %d\n",respuesta);
            }
            else
            {
                printf("numero no encontrado\n");
            }
        break;
        case 2:
            respuesta = busqueda_binaria(arreglo,0,tamanio,numero_buscado);
            if (respuesta != -1)
            {
                printf("numero encontrado en indice: %d\n",respuesta);
            }
            else
            {
                printf("numero no encontrado\n");
            }
            break;
        case 3:
            respuesta = tree_search(&raiz,numero_buscado,tamanio);
            if (respuesta != -1)
            {
                printf("numero encontrado en indice: %d\n",respuesta);
            }
            else
            {
                printf("numero no encontrado\n");
            }
            break;
        case 4:
            //primer caso utilizando hilos
            

            pthread_attr_init(&atributos);
            val_hilo = (valores_hilo *)malloc(sizeof(valores_hilo));
            val_hilo->n = tamanio;
            val_hilo->arreglo = (int*)malloc(sizeof(int)*tamanio);
            val_hilo->arreglo = arreglo;
            val_hilo->inicio = 0;
            val_hilo->fin = tamanio;
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
            printf("la respuesta del hilo es %d\n",val_hilo->respuesta);
            break;
        case 5:
            break;
        case 6:
            break;
        default:
           break;
    }
    return 0;
}




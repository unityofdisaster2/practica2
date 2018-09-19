/*
Archivo de pruebas
Autores: Raymundo Rosales Reyes, Martin, José Manuel
version: v1.0.0
*/

#include "busqueda.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
int main(int argc, char **argv)
{
    int opcion,tamanio,numero_buscado,i,j;
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
            printf("encontrado en: %d\n",busqueda_lineal(arreglo,tamanio,numero_buscado));
            break;
        case 2:
            printf("encontrado en: %d\n",busqueda_binaria(arreglo,0,tamanio,numero_buscado));
            break;
        case 3:
            tree_search(&raiz,numero_buscado,tamanio);
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
            for(j = 0; j<4; j++)
            {
                pthread_create(&hilo[j],&atributos,busqueda_lineal_hilos,val_hilo);
            }
            for(j = 0; j<4; j++)
            {
                pthread_join(hilo[j],NULL);		
            }            
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




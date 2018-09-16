#include "busqueda.h"
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
    int opcion,tamanio,numero_buscado,i;
    int *arreglo;
    
    apu_raiz raiz;
    raiz = NULL;
    
    tamanio = atoi(argv[1]);
    numero_buscado = atoi(argv[2]);
    opcion = atoi(argv[3]);

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
            break;
        case 5:
            break;
        case 6:
            break;
        default:
           break;
    }
<<<<<<< HEAD
    
=======
    printf("cambio sutil amiguito");
>>>>>>> eef7dace3395a51ae74422c1d6240066e676f9df
    return 0;
}




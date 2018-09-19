#include "busqueda.h"


int min = 0;
int max = 0;
int respuesta_hilo=-1;

int busqueda_lineal(int *arreglo, int n,int numero_buscado)
{
    int i,indice=-1,lock=0;
    for(i = 0;i<n && lock == 0;i++)
    {
        if(arreglo[i] == numero_buscado)
        {
            indice = i; 
            lock = 1;
        }
    }
    return indice;
}

int busqueda_binaria(int *arreglo, int inicio, int fin, int numero_buscado)
{
    int indice;
    while (inicio <= fin) 
    { 
        indice = inicio + (fin-inicio)/2; 
  
        if (arreglo[indice] == numero_buscado)
            { 
            return indice;
            } 
  
        if (arreglo[indice] < numero_buscado) 
            inicio = indice + 1; 
        else
            fin = indice - 1; 
    } 
    return -1;  
}


void insertar(apu_raiz *raiz,int numero)
{
    /*se crean dos variables auxiliares, la primera contendra el nodo que 
     deseamos insertar, la segunda sera una copia del nodo raiz
    */
    apu_raiz aux,aux2;
    int condicion_paro = 0;
    aux = malloc(sizeof(nodo));
    aux2 = malloc(sizeof(nodo));
    aux2 = *raiz;
    aux->valor = numero;
    aux->izq = NULL;
    aux->der = NULL;
    /*
     se hace un ciclo para recorrer los nodos del arbol binario de acuerdo
     al valor numerico (con base en el primer numero ingresado(raiz) se insertaran
     del lado izquierdo los que sean menores y del lado derecho los que 
     sean mayores)
     */
    while((aux2 != NULL) && (condicion_paro!=1))
    {
        /*
         se verifica que el numero ingresado sea menor al que contenga el 
         nodo auxiliar
         */
        if(numero <= aux2->valor)
        {
            /*
             se verifica que el nodo izquierdo sea distinto de nulo, si esto
             se cumple se recorre el nodo para visitar la siguiente subraiz.
             */
            if(aux2->izq != NULL)
            {
             aux2 = aux2->izq;   
            }       
            else
            {
                /*
                 si no se cumple la condicion anterior significa que se ha 
                 encontrado el lugar donde se insertara el nuevo nodo.
                 */
                aux2->izq = aux;
                condicion_paro = 1;
            }
        }
        else
        {
            /*
             cuando el numero sea mayor se verifica que el nodo derecho 
             sea distinto, si esto se cumple se visita la siguiente subraiz.
             */
            if(aux2->der != NULL)
            {
             aux2 = aux2->der;   
            }       
            else
            {
                /*
                 si no se cumple la condicion anterior significa que se ha 
                 encontrado el lugar donde se insertara el nuevo nodo. 
  
                 */
                aux2->der = aux;
                condicion_paro = 1;
            }            
        }
    }
    /*
     esta condicion solo se activara si se esta ingresando un valor por primera
     vez al arbol, es decir la raiz.
    */
    if(*raiz == NULL)
    {
        *raiz = aux;
    }
}


int busca_nodo(apu_raiz *raiz, int numero_buscado)
{
    apu_raiz nodo_viajero;
    int condicion_paro = 0,respuesta=-1;
    nodo_viajero = malloc(sizeof(nodo));
    nodo_viajero = *raiz;
    while((nodo_viajero != NULL) && (condicion_paro!=1))
    {
        if(nodo_viajero->valor == numero_buscado)
        {
            printf("encontrado\n");
            respuesta = 1;
            condicion_paro = 1;
        }
        if(numero_buscado <= nodo_viajero->valor)
        {
            if(nodo_viajero->izq != NULL)
            {
             nodo_viajero = nodo_viajero->izq;   
            }
            else
            {
                condicion_paro = 1;
            }
        }
        else
        {
            if(nodo_viajero->der != NULL)
            {
             nodo_viajero = nodo_viajero->der;   
            }            
            else
            {
                condicion_paro = 1;
            }
        }
    }
    return respuesta;
}
int tree_search(apu_raiz *raiz,int numero_buscado,int n)    
{
    int i,numero,r;
    for(i = 0; i<n;i++)
    {
        scanf("%d",&numero);
        insertar(raiz,numero);
    }
    r = busca_nodo(raiz,numero_buscado);
    return r;
}




/*
variantes de busquedas con hilos
*/
void *busqueda_lineal_hilos(void *valor)
{
	int i;
	min = max;
	max = max + ((valores_hilo*)valor)->n/4; 
	for(i=min; i<max;i++)
	{
		if(((valores_hilo*)valor)->arreglo[i] == ((valores_hilo*)valor)->numero_buscado)
		{
			((valores_hilo*)valor)->respuesta = 1;
			break;
		}
	}
    pthread_exit(NULL);
}
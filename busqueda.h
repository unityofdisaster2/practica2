/*
Definiciones de algoritmos de busqueda 
fecha: 30-septiembre-2018
version: 1.0.2
cambios respecto a version anterior: se agrega version de hilos de busqueda binaria
Autores: Raymundo Rosales Reyes, Martin Hernandez Cruz, Jose Manuel Martinez Quevedo 
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


//estructura basica que modela el nodo de un arbol binario
typedef struct nodo
{
    int valor;
    struct nodo *izq,*der;
}nodo;

typedef nodo *apu_raiz;


//estructura que sera utilizada como argumento de las funciones que requieren manejo de hilos
typedef struct estructura
{
	int n,numero_buscado,respuesta;
	int *arreglo;
}valores_hilo;

/*
funcion que recorre un arreglo de forma lineal hasta encontrar un valor solicitado.
recibe como argumento un arreglo con su tamano n y el numero que se desea buscar. 
*/
int busqueda_lineal(int *arreglo, int n,int numero_buscado);



/*
funcion que recorre un arreglo dividiendolo en subarreglos hasta encontrar un valor solicitado.
recibe como argumento un arreglo de numeros, el indice en el que inicia, indice final y el numero 
que se desea buscar.
*/
int busqueda_binaria(int *arreglo, int inicio, int fin, int numero_buscado);


/*
funcion para insertar valores en un arbol binario.
recibe como argumento la raiz del arbol y el numero que se desea agregar
*/
void insertar(apu_raiz *raiz,int numero);

/*
funcion que realiza la busqueda de un valor en los nodos del arbol.
recibe como argumento la raiz del arbol y el numero que se desea buscar.
*/
int busca_nodo(apu_raiz *raiz,int numero_buscado);





/*
version de algoritmos de busqueda implementadas con hilos
reciben como argumento una estructura que contiene los valores necesarios para 
que el algoritmo de busqueda funcione de forma correcta.
*/
void *busqueda_lineal_hilos(void *valor);

int busqueda_main(int *arreglo,int n,int numero_buscado);

void  *busqueda_binaria_hilos(void *val_hilo);

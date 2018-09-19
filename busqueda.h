#include <stdio.h>
#include <stdlib.h>


typedef struct nodo
{
    int valor;
    struct nodo *izq,*der;
}nodo;

typedef nodo *apu_raiz;

typedef struct estructura
{
	int n,inicio,fin,num_hilo,numero_buscado;
	int *arreglo;
}valores_hilo;


int busqueda_lineal(int *arreglo, int n,int numero_buscado);

int busqueda_binaria(int *arreglo, int inicio, int fin, int numero_buscado);


void insertar(apu_raiz *raiz,int numero);


int busca_nodo(apu_raiz *raiz,int numero_buscado);


int tree_search(apu_raiz *raiz, int numero_buscado,int n);




void *busqueda_lineal_hilos(void *valor);
/*
void *busqueda_binaria_hilos(void *estructura);

void *tree_search(void *estructura);
*/
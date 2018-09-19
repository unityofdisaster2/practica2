#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

typedef struct estructura
{
	int n,inicio,fin,num_hilo,numero_buscado;
	int *arreglo;
}valores_hilo;


int min = 0;
int max = 0;

void *busqueda_lineal_hilos(void *valor)
{
	int i;
	min = max;
	max = max + ((valores_hilo*)valor)->n/4; 
	
	
	for(i=min; i<max;i++)
	{
		if(((valores_hilo*)valor)->arreglo[i] == ((valores_hilo*)valor)->numero_buscado)
		{
			printf("encontrado en %d\n",i);
			break;
		}
	}
	return 0;
}


int main(int argc, char **argv)
{
	int j;
	int n=16;
	int arr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};


	valores_hilo *val_hilo;

	pthread_t hilo[4];
	pthread_attr_t atributos;
	pthread_attr_init(&atributos);

	val_hilo = (valores_hilo *)malloc(sizeof(valores_hilo));
	val_hilo->n = n;
	val_hilo->arreglo = (int*)malloc(sizeof(int)*n);
	val_hilo->arreglo = arr;
	val_hilo->inicio = 0;
	val_hilo->fin = 16;
	val_hilo->numero_buscado = 10;
	for(j = 0; j<4; j++)
	{
		pthread_create(&hilo[j],&atributos,busqueda_lineal_hilos,val_hilo);
	}

	for(j = 0; j<4; j++)
	{
		pthread_join(hilo[j],NULL);		
	}
	return 0;
}

/*
Definiciones de algoritmos de busqueda 
fecha: 30-septiembre-2018
version: 1.0.2
cambios respecto a version anterior: se agrega version de hilos de busqueda binaria
Autores: Raymundo Rosales Reyes, Martin Hernandez Cruz, Jose Manuel Martinez Quevedo 
*/

#include "busqueda.h"


int min = 0;
int max = 0;
int respuesta_hilo=-1;






/*
Este algoritmo consiste en revisar de forma lineal cada elemento del arreglo
y cuando se encuentre el valor solicitado se detiene la ejecucion y se devuelve
el indice donde fue encontrado. 
*/
int busqueda_lineal(int *arreglo, int n,int numero_buscado)
{
    int i,indice=-1,lock=0;
    for(i = 0;i<n && lock == 0;i++)
    {
        if(arreglo[i] == numero_buscado)
        {
            /*
            cuando se encuentra el valor se guarda el indice donde se encontro,
            tambien se cambia el valor de lock para salir del ciclo y asi no 
            recorrer el arreglo completo
            */
            indice = i; 
            lock = 1;
        }
    }
    return indice;
}




/*
este algoritmo de busqueda consiste en dividir el problema en subarreglos descartando 
los que no cumplan con cierta condicion de tener valores mayores o menores al numero solicitado.
*/
int busqueda_binaria(int *arreglo, int inicio, int fin, int numero_buscado)
{
    int indice;
    while (inicio <= fin) 
    { 
        //se selecciona como indice la mitad del subarreglo
        indice = inicio + (fin-inicio)/2; 
  
        if (arreglo[indice] == numero_buscado)
            { 
            return indice;
            } 
  
        if (arreglo[indice] < numero_buscado) 
        {
            /*
            si el numero es mayor al que se encuentra en la mitad del subarreglo
            se recorre el valor de inicio del arreglo hasta el que corresponde a la mitad
            descartando la parte izquierda del arreglo 
            */
            inicio = indice + 1; 
        }
        else
        {
            /*
            si no se cumple lo anterior se toma como fin un numero anterior a la mitad 
            del subarreglo y con esto se descarta la parte derecha del arreglo en general
            */
            fin = indice - 1; 
        }
    } 
    return -1;  
}



/*
se requiere funcion insertar en el arbol ya que se recibiran los valores de un archivo
de texto y se ordenaran de acuerdo a las reglas definidas por el arbol de busqueda.
*/
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

/*
esta funcion tiene una estructura similar a la de insercion, siguiendo las 
reglas establecidas para un arbol binario de busqueda. Con dichas reglas 
se hace que un nodo auxiliar viaje a traves del arbol hasta encontrar una
coincidencia. 
*/
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

/*
en la funcion tree_search se implementan las dos funciones anteriores.
Primero se insertan los n valores que se requiera en el arbol y posteriormente
se realiza la busqueda de un valor en sus nodos.
cabe destacar que se deben ingresar los numeros en desorden ya que de lo contrario
el desempeño temporal del arbol sera de forma lineal. 
*/
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
variante de funciones de busqueda implementadas con hilos. 
cuentan con la misma estructura solo que en estas se hace uso de variables
globales para indicar a cada hilo que trabaje con distintas partes de los arreglos.
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




/*
esta funcion se encarga de verificar desde el main si es necesario realizar busqueda
binaria utilizando hilos o si se encuentra directamente el valor solicitado a la mitad
del arreglo principal.
*/
int busqueda_main(int *arreglo,int n,int numero_buscado)
{
    int respuesta;
    if(arreglo[n/2]==numero_buscado)
    {
        respuesta = -1;
    }
    else
    {
        /*
        si el numero no se encuentra a la mitad se modifican las variables globales.
        si el numero es mayor al encontrado en la mitad se modifican las variables de tal
        forma que se descarte la primera mitad del arreglo. Por otro lado si esto no se cumple
        se modifican de tal forma que se descarte la segunda mitad
        */
        if(numero_buscado>arreglo[n/2])
        {
            min = n/2+1;
            max = n;
            respuesta = 1;
        }
        else
        {
            min = 0;
            max = n/2;
            respuesta = 1;
        }
    }
    return respuesta;
}



void  *busqueda_binaria_hilos(void *val_hilo)
{
    int indice,inicio,fin;
    inicio = min;
    fin = max/2;
    min = max/2;
    max = max*2;
    while (inicio <= fin) 
    { 
        indice = inicio + (fin-inicio)/2; 
  
        if (((valores_hilo*)val_hilo)->arreglo[indice] == ((valores_hilo*)val_hilo)->numero_buscado)
            { 
                ((valores_hilo*)val_hilo)->respuesta = 1;
                printf("%d\n",indice);
                return 0;
            } 
  
        if (((valores_hilo*)val_hilo)->arreglo[indice] < ((valores_hilo*)val_hilo)->numero_buscado) 
            inicio = indice + 1; 
        else
            fin = indice - 1; 
    } 
    return 0;  
}

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "cola.h"


/* ******************************************************************
 *                                      	    NODO
 * *****************************************************************/
 
typedef struct nodo {
	void* dato;
	struct nodo *prox;
} nodo_t;

/* ******************************************************************
 *                               	   COLA
 * *****************************************************************/
struct cola {
	nodo_t* cola_primero;
	nodo_t* cola_ultimo;
}; 

/* ******************************************************************
				CREAR_NODO
 * *****************************************************************/
 
//nodo_t* crear_nodo(void* valor){
//	nodo_t* nodo= malloc (sizeof(nodo_t));
//	if (!nodo) return NULL;
//	nodo->prox=NULL;
//	nodo->dato=valor;
//	return nodo;
//}

/* ******************************************************************
				COLA_CREAR
 * *****************************************************************/

cola_t* cola_crear(){
	cola_t* cola = malloc(sizeof(cola_t));
	if (!cola) return NULL;
	cola->cola_primero=NULL;
	return cola;
}

/* ******************************************************************
				COLA_DESTRUIR
 * *****************************************************************/

void cola_destruir(cola_t *cola, void destruir_dato(void*)){
	if (destruir_dato){
		nodo_t* nodo=cola->cola_primero;
		while (nodo){
			destruir_dato(nodo->dato);
			nodo=nodo->prox;
		}
	}
	
	nodo_t* nodo=cola->cola_primero;
	if (cola->cola_primero==NULL){
		free(cola);
		return;
	}
	while (nodo){
		nodo_t* proximo=nodo->prox;
		free(nodo);
		nodo=proximo;
	}
	free(cola);
}
/* ******************************************************************
				COLA_ESTA_VACIA
 * *****************************************************************/

bool cola_esta_vacia(const cola_t *cola){
	if (cola->cola_primero==NULL){
		return true;
	}
	return false;
}

/* ******************************************************************
				COLA_ENCOLAR
 * *****************************************************************/

bool cola_encolar(cola_t *cola, void* valor){
	nodo_t* nodo=crear_nodo(valor);
	if (nodo==NULL) return false;
	
	if (cola_esta_vacia(cola)){
			cola->cola_primero=nodo;
			cola->cola_ultimo=nodo;
			return true;
	}
	
	cola->cola_ultimo->prox=nodo;
	cola->cola_ultimo=nodo;	
	return true;
}

/* ******************************************************************
				COLA_VER_PRIMERO
 * *****************************************************************/

void* cola_ver_primero(const cola_t *cola){
	if (cola_esta_vacia(cola)) return NULL;
	return cola->cola_primero->dato;
}

/* ******************************************************************
				COLA_DESENCOLAR
 * *****************************************************************/	
	
void* cola_desencolar(cola_t *cola){
	if (cola_esta_vacia(cola)){
		cola->cola_primero=NULL;
		cola->cola_ultimo=NULL;
		return NULL;
	}
		
	nodo_t* aux=cola->cola_primero; // se guarda el primer nodo de la cola en una variable auxiliar
	cola->cola_primero=aux->prox; 
	void *el_dato = aux->dato;
	free(aux);
	return el_dato;
}









#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "lista.h"
#include "hash.h"


#define CONSTANTE 500



/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

 struct hash{
	lista_t** vector;
	size_t cantidad;
	size_t tamanio;
	hash_destruir_dato_t destruir;
};

typedef struct bloque{
	char* clave;
	char* valor;
}bloque_t;

struct hash_iter{
	lista_iter_t* actual;
	const hash_t* hash;
	int posicion;
};


size_t hash_tamanio(const hash_t* hash){
	return hash->tamanio;
}

char* bloque_clave(bloque_t* bloque){
	return bloque->clave;
}

char* bloque_valor(bloque_t* bloque){
	return bloque->valor;
}

/* ******************************************************************
 *                	Función HASHING
 * *****************************************************************/

int hashing(const hash_t* hash ,const char* clave){
	int contador=0;
	for (int i=0 ; i<strlen(clave) ; i++){
		contador+= clave[i];
	}
	contador = contador % hash_tamanio(hash);
	return contador;
}

char* strdup(const char *str){
	size_t n = strlen(str) + 1;
	char *dup = malloc(n);
	if (dup) {
		strcpy(dup, str);
	}
return dup;
}

/* ******************************************************************
 *                	Primitivas Bloque
 * *****************************************************************/

bloque_t* bloque_crear(char* clave , char* valor){
	bloque_t* bloque = malloc ( sizeof ( bloque_t));
	if ( !bloque ) return NULL;
	bloque->clave = clave;
	bloque->valor = valor;
	return bloque;
}

void bloque_destruir(bloque_t* bloque){
	free(bloque_clave(bloque));
	free(bloque);
}

/* ******************************************************************
 *                	Primitivas HASH
 * *****************************************************************/

void hash_poner_en_cero(hash_t* hash){
	for ( int i=0 ; i < hash->tamanio ; i++){
		hash->vector[i] = NULL;
	}
}

hash_t* hash_crear(hash_destruir_dato_t destruir_dato){
	hash_t* hash = malloc (sizeof(hash_t));
	if (!hash) return NULL;
	hash->cantidad=0;
	hash->tamanio=CONSTANTE;
	hash->vector = malloc(CONSTANTE * sizeof(lista_t*));
	hash->destruir= destruir_dato;
	hash_poner_en_cero(hash);
	return hash;
}

bool hash_redimensionar(hash_t* hash, float aumento){
	lista_t** aux = hash->vector;
	size_t tam_original = hash->tamanio;
	hash->tamanio = (size_t) (hash->tamanio * aumento);
	hash->cantidad = 0;
	hash->vector = malloc(hash->tamanio * sizeof(lista_t*));
	if (!hash->vector) return false;
	hash_poner_en_cero(hash);
		
	for ( int i = 0 ; i < tam_original ; i++){
		if ( aux[i] ){
			while (!lista_esta_vacia(aux[i])){
				bloque_t* bloque = lista_borrar_primero( aux[i] );
				hash_guardar(hash, bloque_clave(bloque), bloque_valor(bloque));
				free(bloque_clave(bloque));
				free(bloque);
			}
			lista_destruir(aux[i] , NULL);
		}
	}
	free(aux);
	return true;
}

bool hash_guardar(hash_t* hash, const char* clave, void* valor){
	int posicion = hashing( hash, clave);
	if (posicion >= hash->tamanio) return false;

	if ( hash_cantidad(hash) / hash_tamanio(hash)*1.0 >= 0.6 ){
		hash_redimensionar(hash,2);
	}

	if (!hash->vector[posicion]){ 
		char* copia_clave = strdup(clave);
		bloque_t* bloque= bloque_crear(copia_clave, valor);
		lista_t* lista = lista_crear();
		lista_insertar_primero(lista, bloque);
		hash->cantidad++;
		hash->vector[posicion]=lista;
		return true;
	}
	lista_t* lista = hash->vector[posicion];
	lista_iter_t* iter_lista = lista_iter_crear(lista);
	while (!lista_iter_al_final(iter_lista)){
		bloque_t* bloque= lista_iter_ver_actual(iter_lista);
		if ( strcmp(bloque_clave(bloque) , clave) == 0){
			if (hash->destruir){
				hash->destruir(bloque_valor(bloque));
			}
			bloque->valor = valor;
			
			lista_iter_destruir(iter_lista);
			return true;
		}
		lista_iter_avanzar(iter_lista);	
	}
	lista_iter_destruir(iter_lista);
	char* copia_clave = strdup(clave);
	bloque_t* bloque= bloque_crear(copia_clave , valor);
	lista_insertar_primero(lista, bloque);
	hash->cantidad++;
	return true;
}

void* hash_borrar(hash_t* hash, const char* clave){
	
	if ( hash_cantidad(hash) / hash_tamanio(hash)*1.0 >= 0.2 && hash_tamanio(hash) > CONSTANTE){
		hash_redimensionar(hash,0.5);
	}

	if (hash->cantidad == 0) return NULL;
	int posicion=hashing(hash, clave);
	if (!hash->vector[posicion]) return NULL;
	lista_t* lista = hash->vector[posicion];
	if (lista_largo(lista) == 0){
		free(lista);
		return NULL;
	}
	lista_iter_t* iter = lista_iter_crear(lista);
	while (!lista_iter_al_final(iter)){
		if (strcmp( bloque_clave(lista_iter_ver_actual(iter)) , clave) == 0){
			hash->cantidad--;
			bloque_t* bloque = lista_iter_ver_actual(iter);
			char* valor = bloque_valor(lista_borrar(lista, iter));
			if (lista_largo(lista) == 0){
				lista_destruir(lista, NULL);
				hash->vector[posicion]=NULL;
			}
			free(bloque_clave(bloque));
			free(bloque);
			lista_iter_destruir(iter);
			return valor;
		}
		lista_iter_avanzar(iter);	
	}
	lista_iter_destruir(iter);
	return NULL;
}

	
void* hash_obtener(const hash_t* hash, const char* clave){
	if ( hash_cantidad(hash) == 0 ) return NULL;
	int posicion=hashing(hash, clave);
	if (!hash->vector[posicion]) return NULL;
	lista_t* lista = hash->vector[posicion];
	lista_iter_t* iter = lista_iter_crear(lista);
	while (!lista_iter_al_final(iter)){
		if (strcmp(bloque_clave(lista_iter_ver_actual(iter)), clave) == 0){
			bloque_t* bloque = lista_iter_ver_actual(iter);
			lista_iter_destruir(iter);
			return bloque_valor(bloque);
		}
		lista_iter_avanzar(iter);
	}
	lista_iter_destruir(iter);
	return NULL;
}

bool hash_pertenece (const hash_t* hash, const char* clave){
	if ( hash_cantidad(hash) == 0 ) return false;
	int posicion=hashing(hash, clave);
	if (!hash->vector[posicion]) return false;
	lista_t* lista = hash->vector[posicion];
	lista_iter_t* iter = lista_iter_crear(lista);
	while (!lista_iter_al_final(iter)){

		if (strcmp(bloque_clave(lista_iter_ver_actual(iter)),clave) == 0){
			lista_iter_destruir(iter);
			return true;
		}
		lista_iter_avanzar(iter);
	}
	lista_iter_destruir(iter);
	return false;
}


size_t hash_cantidad(const hash_t* hash){
	return hash->cantidad;
}

void hash_destruir(hash_t* hash){
	if ( hash->cantidad == 0 ){
		free(hash->vector);
		free(hash);
		return;
	}
	for ( int i=0 ; i < hash->tamanio ; i++){
		if (hash->vector[i]){
			lista_t* lista = hash->vector[i];
			while (!lista_esta_vacia(lista)){
				bloque_t* bloque = lista_borrar_primero(lista);
				if (hash->destruir ){
					hash->destruir(bloque_valor(bloque));
				}
				free(bloque_clave(bloque));
				free(bloque);
			}
			lista_destruir(lista , NULL);
			hash->vector[i]=NULL;
		}
	}
	free(hash->vector);
	free(hash);
}
	
	
/* ******************************************************************
 *                	PRIMITIVAS HASH ITER
 * *****************************************************************/

void* hash_iter_actual(const hash_iter_t* iter){
	return iter->actual;
}

int hash_iter_posicion(const hash_iter_t* iter){
	return iter->posicion;
}

hash_iter_t* hash_iter_crear(const hash_t* hash){
	hash_iter_t* iter = malloc (sizeof(hash_iter_t));
	if (!hash) return NULL;
	iter->hash = hash;
	iter->posicion = 0;
	if (hash->cantidad == 0){
		return iter;
	}
	while (!hash->vector[hash_iter_posicion(iter)]){
		iter->posicion++;
	}

	lista_iter_t* iter_lista = lista_iter_crear (hash->vector[hash_iter_posicion(iter)]);
	iter->actual = iter_lista;
	return iter;
}

bool hash_iter_avanzar(hash_iter_t* iter){
	if (iter->posicion == iter->hash->tamanio){
				return false;
	}
	if (hash_cantidad(iter->hash) == 0) return false;
	if (!lista_iter_al_final(hash_iter_actual(iter))){
		lista_iter_avanzar(hash_iter_actual(iter));
		//return true;
	}
	if (iter->posicion == iter->hash->tamanio){
				return false;
	}
	if (lista_iter_al_final(hash_iter_actual(iter))){
		iter->posicion++;
		lista_iter_destruir(iter->actual);
		iter->actual = NULL;
		while (!iter->hash->vector[hash_iter_posicion(iter)]){
			iter->posicion++;
			if (iter->posicion == iter->hash->tamanio){
				return false;
			}
		}
		lista_t* lista= iter->hash->vector[hash_iter_posicion(iter)];
		lista_iter_t* iter_lista = lista_iter_crear(lista);
		iter->actual = iter_lista;
		return true;
	}
	return true;
}

const char *hash_iter_ver_actual(const hash_iter_t *iter){
	if (iter->posicion == iter->hash->tamanio){
				return NULL;
	}
	if ( hash_cantidad(iter->hash) == 0) return NULL;
	if (!iter->hash->vector[hash_iter_posicion(iter)]) return NULL;
	return bloque_clave(lista_iter_ver_actual(iter->actual));
}


bloque_t* hash_iter_ver_actual_bloque(const hash_iter_t* iter){
	if (iter->posicion == iter->hash->tamanio){
				return NULL;
	}
	if (!iter->hash->vector[hash_iter_posicion(iter)]) return NULL;
	return lista_iter_ver_actual(iter->actual);
}


bool hash_iter_al_final(const hash_iter_t* iter){
	if (iter->posicion == iter->hash->tamanio){
				return true;
	}
	lista_iter_t* iter_lista = hash_iter_actual(iter);
	int posicion = hash_iter_posicion(iter);
	if (hash_cantidad((iter->hash)) <= 1) return true;
	if (lista_iter_al_final(iter_lista)) {
		while (!iter->hash->vector[hash_iter_posicion(iter)]){
			posicion++;
			if (iter->posicion >= iter->hash->tamanio){
				return true;
			}
		}
		return false;
	} 
	return false;
}

void hash_iter_destruir( hash_iter_t* iter){
	if (!iter) return;
	if (iter->hash->cantidad != 0) lista_iter_destruir(iter->actual);
	free (iter);
}

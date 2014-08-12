#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hash.h"
#include "arbol.h"

/* ******************************************************************
 *                      FUNCIONES AUXILIARES
 * *****************************************************************/

/* Función auxiliar para imprimir si estuvo OK o no. */
void print_test(char* name, bool result)
{
    printf("%s: %s\n", name, result? "OK" : "ERROR");
}

/* ******************************************************************
 *                        PRUEBAS UNITARIAS
 * *****************************************************************/

void prueba_crear_arbol(){
	abb_t* arbol = abb_crear (NULL, NULL);
	
	char arreglo[] = "qwertyuiopasdfghjklzxcvbnm";
	
	print_test("Probando se creo el arbol", arbol);
	print_test("Probando que la cantidad de elementos sea 0", abb_cantidad(arbol) == 0);
	print_test("Probando que no se puede guardar", abb_guardar(arbol, &arreglo[2], &arreglo[2]) == false );	
	print_test("Probando que no se puede borrar", abb_borrar(arbol, &arreglo[2]) == false );
	
	abb_destruir(arbol);
}

void prueba_arbol_guardar(){
	
	//Creo un arbol
	
	abb_t* arbol = abb_crear(strcmp,NULL);
	
	print_test("Probando que la cantidad de elementos sea 0", abb_cantidad(arbol) == 0);
	
	//Agrego 20 letras
	
	char arreglo[] = "qwertyuiopasdfghjklzxcvbnm";
	
	bool estado = true;
	
	for (int i=0 ; i<20 ; i++){
		estado = abb_guardar(arbol, &arreglo[i], &arreglo[i]);
	}
	
	print_test("Probando agregar 20 elementos al arbol" , estado );
	print_test("Probando que la cantidad de elementos sea 20", abb_cantidad(arbol) == 20);
	print_test("Probando si el elemento esta en el arbol", abb_pertenece(arbol, &arreglo[1]));
	print_test("Probando si el elemento esta en el arbol", abb_obtener(arbol, &arreglo[1]));
	
	abb_destruir(arbol);
}
	
void prueba_arbol_borrar() {
	
	//Creo un arbol
	
	abb_t* arbol = abb_crear(strcmp,NULL);
	
	bool estado = true;
	
	void* arreglo[10] = {"6","2","1","4","9","8","3","5","7"};
	
	//char arreglo[] = "qwertyuiopasdfghjklzxcvbnm";
	
	for (int i=0 ; i<=8 ; i++){
		printf("GUARDO %s \n", (char*) arreglo[i]);
		estado = abb_guardar(arbol, arreglo[i], arreglo[i]);
	}
	
	//Elimino 10 elementos
	
	printf("cantidad de elementos antes de borrar %d \n", abb_cantidad(arbol));
	for (int i=0 ; i<=8 ; i++){
		printf("\n BORRO %s	\n", (char*) arreglo[i]);
		abb_borrar(arbol, arreglo[i]);
		printf("cantidad de elementos %d \n", abb_cantidad(arbol));
	}
	
	
	print_test("Probando que la cantidad de elementos sea 1", abb_cantidad(arbol) == 0);
	
	//Elimino el arbol
	abb_destruir(arbol);
}

void prueba_arbol_iterador(){
	abb_t* arbol = abb_crear(strcmp,NULL);
	
	bool estado = true;
	
	char arreglo[] = "qwertyuiopasdfghjklzxcvbnm";
	
	for (int i=0 ; i<20 ; i++){
		estado = abb_guardar(arbol, &arreglo[i], &arreglo[i]);
	}
	
	abb_iter_t* iter = abb_iter_in_crear(arbol);
	
	print_test("Probando que el actual es distinto a null", abb_iter_in_ver_actual(iter));

	for (int i=0 ; i<20 ; i++){
		abb_iter_in_avanzar(iter);
	}
	
	print_test("Probando que el iter esta al final", abb_iter_in_al_final(iter));

	

	abb_iter_in_destruir(iter);
	
	abb_destruir(arbol);
	
	////
	
	abb_t* arbol2 = abb_crear(strcmp, NULL);
	
	abb_iter_t* iter2 = abb_iter_in_crear(arbol2);
	
	print_test("Probando iterar en un arbol vacio", abb_iter_in_avanzar(iter2) == false);

	print_test("Probando iter al final", abb_iter_in_al_final(iter2));
	
	print_test("Probando ver actual es NULL", abb_iter_in_ver_actual(iter2) == NULL);
	
	
	abb_iter_in_destruir(iter2);
	
	abb_destruir(arbol2);	
	
}

void prueba_abb_in_order(){
	
	//Creo un arbol y le agrego 20 elementos
	
	abb_t* arbol = abb_crear(strcmp, NULL);
	char arreglo[] = "qwertyuiopasdfghjklzxcvbnm";
	bool estado = true;
	
	for (int i=0 ; i<20 ; i++){
		estado = abb_guardar(arbol, &arreglo[i], &arreglo[i]);
	}
	
	print_test("Probando agregar 20 elementos al arbol" , estado );
	print_test("Probando que la cantidad de elementos sea 20", abb_cantidad(arbol) == 20);
	
	//Creo una cola, recorro el arbol y agrego los datos a la cola.
	
	hash_t* hash = hash_crear(NULL);
	
	abb_in_order(arbol, hash_guardar, hash);
	
	// Destruyo la cola y el arbol
	
	hash_destruir(hash);
	abb_destruir(arbol);
}


int main(){
	
	prueba_crear_arbol();
	
	prueba_arbol_guardar();
	
	prueba_arbol_borrar();
	
	prueba_arbol_iterador();

	//prueba_abb_in_order();
	
	return 0;
}

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


#include "pila.h"

/* ******************************************************************
 *                        PRUEBAS UNITARIAS 
 * *****************************************************************/

/* Función auxiliar para imprimir si estuvo OK o no. */
void print_test(char* name, bool result) {
	printf("%s: %s\n", name, result? "OK" : "ERROR");
}

void prueba_pila(){
	
	//Declaro 3 pilas a utilizar
	pila_t *pila1, *pila2, *pila3;
	
	//Creo las 3 pilas
	pila1=pila_crear();
	pila2=pila_crear();
	pila3=pila_crear();
	
	//Creo dos variables para apliar
	int vector[]={1,2,3,4,5};
	char cadena[]="Hola, que tal?";
	
	//Apilo en una
	print_test("Apilo el vector en la pial2",pila_apilar(pila2,&vector));
	print_test("Apilo la cadena en la pila2", pila_apilar(pila2,&cadena));
	
	//Pruebo si estan vacias
	print_test("Probando si pila1 esta vacia (deberia estar vacia)", pila_esta_vacia(pila1) == true);
	print_test("Probando si pila2 esta vacia (no deberia estar vacia)", pila_esta_vacia(pila2) == false );
	
	//Prueba ver_tope
	print_test("Probando ver_tope de pila1", pila_ver_tope(pila1) == NULL);
	print_test("Probando ver_tope de pila2", pila_ver_tope(pila2) == cadena);
	
	//Prueba de agrandar pila, apilo 60 elementos
	print_test("Probando que datos de pila3 este vacio antes de agrandarla", pila_esta_vacia(pila3));
	int dato;
	for (dato=1 ; dato<=60 ; dato++){
		pila_apilar(pila3, &dato);
	}
	print_test("Probando que datos de pila 3 no este vacio", pila_esta_vacia(pila3) == false);
	
	//Pruebas de desapilar
	print_test("Probando desapilar de la pila2", pila_desapilar(pila2) == cadena);
	print_test("Probando desapilar de la pila2", pila_desapilar(pila2) == vector);
	print_test("Probando si pila2 esta vacia", pila_esta_vacia(pila2));
	print_test("Probando desapilar de la pila2 (no tiene mas elementos)", pila_desapilar(pila2) == NULL);
	int contador;
	for (contador=0 ; contador <= 60 ; contador++){
		pila_desapilar(pila3);
	}
	print_test("Ver tope de pila3", pila_ver_tope(pila3) == NULL);
	print_test("Probando si pila3 esta vacia" , pila_esta_vacia(pila3));

	
	//Destruyo las pilas
	pila_destruir(pila1);
	pila_destruir(pila2);
	pila_destruir(pila3);
	
}

int main(void){
	prueba_pila();
	return 0;
}

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "cola.h"

/* ******************************************************************
 *                        PRUEBAS UNITARIAS 
 * *****************************************************************/

/* Función auxiliar para imprimir si estuvo OK o no. */
void print_test(char* name, bool result) {
	printf("%s: %s\n", name, result? "OK" : "ERROR");
}

void prueba_cola(){
	
	//Declaro 3 colas a utilizar
	
	cola_t *cola1, *cola2, *cola3;
	
	//Creo las 3 colas
	
	cola1=cola_crear();
	cola2=cola_crear();
	cola3=cola_crear();	
	//Creo dos variables para encolar
	
	int vector[]={1,2,3,4,5};
	char cadena[]="Hola, que tal?";
	
	//Encolo en cola 2
	
	print_test("Encolo el vector en la cola 2",cola_encolar(cola2,&vector));
	print_test("Encolo la cadena en la cola 2", cola_encolar(cola2,&cadena));
	
	//Pruebo si estan vacias 
	print_test("Probando si cola 1 esta vacia (deberia estar vacia)", cola_esta_vacia(cola1) == true);
	print_test("Probando si cola 2 esta vacia (no deberia estar vacia)", cola_esta_vacia(cola2) == false );
	
	//Prueba ver_tope
	print_test("Probando ver_tope de cola 1", cola_ver_primero(cola1) == NULL);
	print_test("Probando ver_tope de cola 2", cola_ver_primero(cola2) == vector);
	
	
	
	//Pruebas de desencolar
	print_test("Probando desencolar de la cola2", cola_desencolar(cola2) == vector);
	print_test("Probando desencolar de la cola2", cola_desencolar(cola2) == cadena);
	print_test("Probando si cola2 esta vacia (deberia estar) ", cola_esta_vacia(cola2));
	print_test("Probando desencolar de la cola2 (no tiene mas elementos)", cola_desencolar(cola2) == NULL);
	
	//Prueba de agrandar cola, encolo 5  elementos
	print_test("Probando que cola 3 este vacia antes de agrandarla", cola_esta_vacia(cola3));
	int dato;
	for (dato=1 ; dato<=5 ; dato++){
		cola_encolar(cola3, &dato);
	}
	print_test("Probando que cola3 no este vacia despues de encolar elementos", cola_esta_vacia(cola3) == false);
	
	//Pruebas de desencolar cola3
	int contador;
	for (contador=0 ; contador <= 5 ; contador++){
		cola_desencolar(cola3);
	}
	print_test("Ver primero de cola3", cola_ver_primero(cola3) == NULL);
	print_test("Probando si cola3 esta vacia" , cola_esta_vacia(cola3) == true);

	int* puntero1;
	puntero1 = malloc (sizeof(void*));
	cola_encolar(cola1,puntero1);
	
	
	
	//Destruyo las colas
	
	cola_destruir(cola1 , free);
	cola_destruir(cola2 , NULL);
	cola_destruir(cola3 , NULL);
}

int main(void){
	prueba_cola();
	return 0;
}

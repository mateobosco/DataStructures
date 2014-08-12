
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "heap.h"

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
int micmp(const void* arreglo1, const void* arreglo2){
	return strcmp((char*) arreglo1, (char*) arreglo2);
}

void prueba_crear(){
	
	// Creo un Heap
	
	heap_t* heap = heap_crear(micmp);
	
	print_test("Probando se creo el heap", heap);
	
	print_test("Probando que la cantidad de elementos sea 0", heap_cantidad(heap) == 0);
	
	print_test("Probando desencolar con el heap vacio", heap_desencolar(heap) == NULL);
	
	print_test("Probando ver max en un heap vacio", heap_ver_max(heap) == NULL);
	
	//libero el heap
	
	heap_destruir(heap, NULL);
	
}

void prueba_guardar(){
	
	heap_t* heap = heap_crear(micmp);
	
	print_test("Probando se creo el heap", heap);
	
	print_test("Probando que el heap este vacio", heap_esta_vacio(heap));
	
	print_test("Probando que la cantidad de elementos sea 0", heap_cantidad(heap) == 0);
	
	char *clave1 = "1"; 
	char *clave2 = "2"; 
	char *clave3 = "3";
	
	heap_encolar(heap, clave1);
	heap_encolar(heap, clave2);
	heap_encolar(heap, clave3);
	
	print_test("Probando que la cantidad de elementos sea 3", heap_cantidad(heap) == 3);
	
	print_test("Probando que el heap no este  vacio", heap_esta_vacio(heap) == false);
		
	print_test("Probando que el ver maximo del heap sea la clave 3", heap_ver_max(heap) == clave3);
	
	char *clave4 = "4";
	
	heap_encolar(heap, clave4);
		
	print_test("Probando que la cantidad de elementos sea 4", heap_cantidad(heap) == 4);
	
	//mostrar_heap(heap);
	
	print_test("Probando que el ver maximo sea la clave4", heap_ver_max(heap) == clave4);
	
	print_test("Probando que la cantidad de elementos sea 4", heap_cantidad(heap) == 4);
	
	print_test("Probando el desencolar deberia desencolar el 4", heap_desencolar(heap) == clave4);
		
	print_test("Probando el desencolar deberia desencolar el 3", heap_desencolar(heap) == clave3);
		
	print_test("Probando el desencolar deberia desencolar el 2", heap_desencolar(heap) == clave2);
		
	print_test("Probando el desencolar deberia desencolar el 1", heap_desencolar(heap) == clave1);
		
	print_test("Probando el desencolar con el heap vacio", heap_desencolar(heap) == NULL);
	
	print_test("Probando que la cantidad de elementos sea 0", heap_cantidad(heap) == 0);
	
	char *clave20 = "15"; 
	char *clave8= "8"; 
	char *clave5 = "5";
	
	heap_encolar(heap, clave20);
	heap_encolar(heap, clave8);	
	heap_encolar(heap, clave5);
	
	print_test("Probando que la cantidad de elementos sea 0", heap_cantidad(heap) == 3);
		
	heap_destruir(heap, NULL);

}


void prueba_desencolar(){
	
	// creo el heap
	heap_t* heap = heap_crear(micmp);
	
	void* arreglo[10]={"2","3","4","1","6","9","8","7","5"};
	
	for (int i=0; i<9; i++){
		heap_encolar(heap, arreglo[i]);
	}
	
	print_test("Probando el desencolar deberia desencolar el 9", heap_desencolar(heap) == arreglo[5]);
	print_test("Probando el desencolar deberia desencolar el 8", heap_desencolar(heap) == arreglo[6]);
	print_test("Probando el desencolar deberia desencolar el 7", heap_desencolar(heap) == arreglo[7]);
	print_test("Probando el desencolar deberia desencolar el 6", heap_desencolar(heap) == arreglo[4]);
	print_test("Probando el desencolar deberia desencolar el 5", heap_desencolar(heap) == arreglo[8]);
	print_test("Probando el desencolar deberia desencolar el 4", heap_desencolar(heap) == arreglo[2]);
	print_test("Probando el desencolar deberia desencolar el 3", heap_desencolar(heap) == arreglo[1]);
	print_test("Probando el desencolar deberia desencolar el 2", heap_desencolar(heap) == arreglo[0]);
	print_test("Probando el desencolar deberia desencolar el 1", heap_desencolar(heap) == arreglo[3]);

	// Destruyo el heap
	heap_destruir(heap, NULL);
	
}
	
	

void prueba_heapsort(){
	void* elementos[10]={"2","3","4","1","6","9","8","7","5"};
	
	heapsort(elementos, 9, micmp);
	
	printf(" SE ORDENO EL ARREGLO Y QUEDO ASI : \n");
	for (int w=0; w < 9; w++){
		printf (" %d - %s  \n", w, (char*) elementos[w]);
	}
	
	void* elementos2[10]={"8","9","1","2","7","3","5","4","6"};
	
	heapsort(elementos2, 9, micmp);
	
	printf(" SE ORDENO EL ARREGLO Y QUEDO ASI : \n");
	for (int y=0; y < 9; y++){
		printf (" %d - %s  \n", y, (char*) elementos2[y]);
	}
	
	
	void* elementos3[10]={"casa","bar","diario","elefante","iris","guiterra","hola","ala","flan"};
	
	heapsort(elementos3, 9, micmp);
	
	printf(" SE ORDENO EL ARREGLO Y QUEDO ASI : \n");
	for (int x=0; x < 9; x++){
		printf (" %d - %s  \n", x, (char*) elementos3[x]);
	}

	
	
}

void prueba_volumen(){
	
	heap_t* heap = heap_crear(micmp);

	void* arreglo[25]={"2","3","4","1","6","9","8","7","5","2","3","5","6","7","8","9","1","3","4","5","6","1","3","8","6"};
	
	for (int i=0; i<24; i++){
		heap_encolar(heap, arreglo[i]);
	}
	
	print_test("Probando que la cantidad de elementos sea 25", heap_cantidad(heap) == 24);

	for (int j=0; j<24; j++){
		heap_desencolar(heap);
	}

	print_test("Probando que la cantidad de elementos sea 0", heap_cantidad(heap) == 0);
	
	heap_destruir(heap, NULL);
}

void prueba_volumen2(){
	
	heap_t* heap = heap_crear(micmp);

	char* clave2 = "hola";
	
	for (int i=0; i<60; i++){
		heap_encolar(heap, clave2);
	}
	
	print_test("Probando que la cantidad de elementos sea 60", heap_cantidad(heap) == 60);

	for (int j=0; j<60; j++){
		heap_desencolar(heap);
	}
	
	print_test("Probando que la cantidad de elementos sea 0", heap_cantidad(heap) == 0);
	
	heap_destruir(heap, NULL);
	
}


void prueba_destruir(){
	heap_t* heap = heap_crear(micmp);
	char* clave = malloc (sizeof (char*));
	heap_encolar(heap, clave);
	heap_destruir(heap, free);
}

int main(){
	prueba_crear();
	prueba_guardar();
	prueba_desencolar();
	prueba_heapsort();
	prueba_volumen();
	prueba_volumen2();
	prueba_destruir();
	
	return 0;
}




#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "lista.h"


/* Función auxiliar para imprimir si estuvo OK o no*/

void print_test (char* name, bool result){
	printf("%s: %s\n", name, result? "OK" : "ERROR");
	}

void lista_prueba(){
	
	//Pruebo crear listas
	lista_t* lista1 = lista_crear();
	lista_t* lista2 = lista_crear();
	lista_t* lista3 = lista_crear();
	
	print_test("Probando si lista1 se creo bien", lista1!=NULL);
	print_test("Probando si lista1 esta vacia", lista_esta_vacia(lista1));
	print_test("Probando si el largo de lista2 es 0", lista_largo(lista2)==0);
	
	int vector[]={ 1, 2, 3, 4};
	char vector2[]="hola que tal";
	
	// Probando insertar en la lista;
	
	print_test("Probando si se inserta al principio un elemento en la lista1", lista_insertar_primero(lista1, &vector));
	print_test("Probando si se inserta al final un elemento en la lista1", lista_insertar_ultimo(lista1, &vector2));
	
	// Probando el largo de la lista con 2 elementos
	
	print_test("Probando que el largo de la lista1 sea dos", lista_largo(lista1)==2);
	
	// Probando el lista borrar primero en la lista 1
	
	print_test("Probando si se borra el primer elemento en la lista1", lista_borrar_primero(lista1) == vector);
	
	// Probando el lista ver primero
	
	print_test("Probando ver el primero de la lista 1", lista_ver_primero(lista1) == vector2 );
	
	// Probando agregar al principio en lista 3
	
	print_test("Probando si se inserta al principio un elemento en la lista3", lista_insertar_primero(lista3, &vector));
	
	lista_insertar_ultimo(lista3, &vector2);
	
	// PRUEBAS CON EL ITERADOR CON LA LISTA 3
	
	lista_iter_t* iter = lista_iter_crear(lista3);
	
	// Probando el iter avanzar
	
	print_test("Probando el iter avanzar", lista_iter_avanzar(iter));

	//  Probando el iter ver actual
	
	print_test("Probando el iter ver actual", lista_iter_ver_actual(iter) == vector2);
	
	// Probando el iter al final
		
	print_test("Probando el iter avanzar", lista_iter_avanzar(iter));
	print_test("Probando el iter avanzar (no puede avanzar mas)", lista_iter_avanzar(iter) == false);

	print_test("Probando el iter al final", lista_iter_al_final(iter));
	print_test("Probando si el iter esta el final el ver_actual", lista_iter_ver_actual(iter) == NULL); 
	
	lista_iter_destruir(iter);
	
	// Probando lista_insertar con iterador
	
	lista_iter_t* iter2 = lista_iter_crear(lista2);
	
	char vector3[]="chau";
	
	print_test("Probando el lista_insertar en la lista con el iter", lista_insertar(lista2,iter2,&vector3));
	print_test("Probando ver el primero de la lista2", lista_ver_primero(lista2) == &vector3 );
	print_test("Probando borrar con el iter", lista_borrar(lista2,iter2) == vector3 );
	print_test("Probando el lista_ver_primero con los nodos borrados", lista_ver_primero(lista2) == NULL );
	print_test("Probando el largo de una lista vacia", lista_largo(lista2) == 0 );
	print_test("Probando el lista_borrar_primero en una lista vacia", lista_borrar_primero(lista2) == NULL );
	
	lista_iter_destruir(iter2);
	
	// Pruebo Agregar 30 Datos y luego borrarlos
	
	for ( int i=0 ; i < 30 ; i++){
		lista_insertar_ultimo(lista2, &i);
	}
	print_test("Probando el largo de la lista2 luego de agregar 30 elementos", lista_largo(lista2) == 30);
	
	lista_iter_t* iter3=lista_iter_crear(lista2);
	
	while (!lista_iter_al_final(iter3)){
		lista_borrar(lista2,iter3);
	}
	
	print_test("Probando que se borraron todos los elementos" , lista_largo(lista2) == 0);
	print_test("Prubando borrar un elemento en una lista vacia" , lista_borrar(lista2,iter3) == NULL);
	
	lista_iter_destruir(iter3);
	
	//Finalmente, pruebo si estan vacias las 3 listas
	
	print_test( "Probando que la lista1 no este vacia", lista_esta_vacia(lista1) == false );
	print_test( "Probando que la lista2 este vacia", lista_esta_vacia(lista2) );
	print_test( "Probando que la lista3 no este vacia", lista_esta_vacia(lista3) == false );
	
	//Elimino las 3 listas
	
	lista_destruir(lista1, NULL);
	lista_destruir(lista2, NULL);
	lista_destruir(lista3, NULL);
	
	/* ******************************************************************
	*               Pruebas con lista 4
	* *****************************************************************/
	
	//Creo otra lista y le inserto 10 nodos
	
	lista_t* lista4 = lista_crear();
	
	for( int num=1; num <= 10 ; num++){
		int elemento=1;
		lista_insertar_ultimo(lista4 , &elemento);
	}
	
	print_test("Probando largo de la lista 4", lista_largo(lista4) == 10 );
	
	lista_iter_t* iter4= lista_iter_crear(lista4);
	
	print_test("Probando que se creo el iter 4", iter4!=NULL);
	
	print_test("Probando que el iter 4 no este al final", lista_iter_al_final(iter4) == false);
	
	for (int j=1; j<=10; j++){
		lista_iter_avanzar(iter4);
	}
		
	print_test("Probando que el iter 4 este al final", lista_iter_al_final(iter4));
	
	char prueba[] = "prueba";
	
	print_test("Probando lista_insertar con el iter al final ", lista_insertar(lista4, iter4, &prueba));
	
	print_test("Probando que el iter 4 no este al final", lista_iter_al_final(iter4) == false);
	
	print_test("Probando avanzar con el iter 4 al final", lista_iter_avanzar(iter4));
	
	print_test("Probando lista_borrar con el iter 4 al final", lista_borrar(lista4,iter4) == NULL);
	
	print_test("Probando lista_insertar con el iter 4 al final ", lista_insertar(lista4, iter4, &prueba));
	
	print_test("Probando lista_borrar con el iter 4", lista_borrar(lista4,iter4) == prueba);
	
	for (int j=0; j<=10; j++){
		lista_borrar_primero(lista4);
	}
	
	print_test("Probando largo de la lista 4", lista_largo(lista4) == 0 );

	// elimino el iter 4
	
	lista_iter_destruir(iter4);


	//Elimino la lista
	
	lista_destruir(lista4, free);
	
	
	
	/* ******************************************************************
	*               Pruebas con lista 5
	* *****************************************************************/
	
	//Creo otra lista y le inserto 10 nodos
	
	lista_t* lista5 = lista_crear();
	
	// le creo un iter
	
	lista_iter_t* iter5= lista_iter_crear(lista5);
	
	print_test("Probando que se creo el iter 5", iter5!=NULL);
	
	for( int num=1; num <= 10 ; num++){
		char elemento2[]="hola";
		lista_insertar(lista5, iter5, &elemento2);
	}
	
	print_test("Probando largo de la lista 5", lista_largo(lista5) == 10 );
	
	print_test("Probando que el iter 5 no este al final", lista_iter_al_final(iter5) == false);
	
	char prueba2[] = "prueba";
	
	print_test("Probando lista_borrar con el iter 5 al principio", lista_borrar(lista5,iter5) != NULL);
	
	print_test("Probando lista_insertar con el iter 5 al principio", lista_insertar(lista5, iter5, &prueba2));
	
	print_test("Probando lista_borrar con el iter 5 ", lista_borrar(lista5,iter5) == prueba2);
	
	for (int j=0; j<=10; j++){
		lista_borrar(lista5, iter5);
	}
	
	print_test("Probando largo de la lista 5", lista_largo(lista5) == 0 );
	
	print_test("Probando que la lista 5 este vacia", lista_esta_vacia(lista5));
	
	print_test("Probando lista ver_primero de la lista 5", lista_ver_primero(lista5) == NULL);
	
	print_test("Probando avanzar con el iter 5 al final", lista_iter_avanzar(iter5) == false);
	
	print_test("Probando avanzar con el iter 5 al final", lista_iter_ver_actual(iter5) == NULL);
	
	
	// elimino el iter 5
	lista_iter_destruir(iter5);
	
	//Elimino la lista
	lista_destruir(lista5, free);


	/* ******************************************************************
	*               Pruebas con lista 6
	* *****************************************************************/
		
	// Creo una nueva Lista
		
	lista_t* lista6 = lista_crear();
	
	// le creo un iter
	
	lista_iter_t* iter6= lista_iter_crear(lista6);
	
	print_test("Probando que se creo el iter 6", iter6!=NULL);
	
	
	void* elemento = malloc(sizeof(void*)) ;
	
	print_test("Probando agregar un elemento con lista_insertar con la lista 6 vacia", lista_insertar(lista6, iter6, elemento));
	
	print_test("Probando largo de la lista 6", lista_largo(lista6) == 1 );
	
	print_test("Probando que el iter 6 no este al final", lista_iter_al_final(iter6) == false);
	
	print_test("Probando si puedo avanzar con el iter 6", lista_iter_avanzar(iter6));
	
	print_test("Probando que el iter 6 este al final", lista_iter_al_final(iter6));
		
	void* borrar=lista_borrar_primero(lista6);
	free(borrar);
	
	// elimino el iter 6
	
	lista_iter_destruir(iter6);

	//Elimino la lista 6
	
	lista_destruir(lista6, free);
	
	/* ******************************************************************
	*               Pruebas con lista 7
	* *****************************************************************/
	
	lista_t* lista7 = lista_crear();
	
	
	
	for (int x=1 ; x<=10 ; x++){
		lista_insertar_primero(lista7, &x);
	}
	
	lista_iter_t* iter7 = lista_iter_crear(lista7);
	
	print_test("Probando que el largo de la lista7 sea 10", lista_largo(lista7) == 10);
	
	while (!lista_iter_al_final(iter7)){
		lista_iter_avanzar(iter7);
	}
	
	void* y;
	
	print_test("Probando si se puede ver el elemento actual del iter", lista_iter_ver_actual(iter7) == NULL);
	print_test("Probando insetar un elemento al final de la lista7", lista_insertar(lista7, iter7, &y));
	print_test("Probando que el largo de la lista7 sea 11", lista_largo(lista7) == 11);
	print_test("Probando borrar el ultimo elemento de lista7", lista_borrar(lista7,iter7) == &y);
	print_test("Probando que el largo de la lista7 sea 10", lista_largo(lista7) == 10);
	print_test("Probando insetar un elemento al final de la lista7", lista_insertar(lista7, iter7, &y));
	print_test("Probando que el iter7 no quede al final", lista_iter_al_final(iter7) == false);
	
	
	lista_iter_destruir(iter7);
	lista_destruir(lista7, NULL);

	/* ******************************************************************
	*               Pruebas con lista 8
	* *****************************************************************/

	lista_t* lista8 = lista_crear();
	
	for (int x=1 ; x<=5 ; x++){
		lista_insertar_ultimo(lista8, &x);
	}
	print_test("Probando que el largo de la lista8 sea 5", lista_largo(lista8) == 5);
	
	lista_iter_t* iter8 = lista_iter_crear(lista8);
	
	int elem=0;
	print_test("Probando que el elemento actual del iter8 no es null", lista_iter_ver_actual(iter8) != NULL);
	print_test("Probando insertar al principio con el iter en lista8", lista_insertar(lista8, iter8, &elem));
	print_test("Probando que el largo de lista8 sea 6", lista_largo(lista8) == 6);
	print_test("Probando eliminar el primer elemento de la lista8 con el iter", lista_borrar(lista8, iter8) == &elem);
	print_test("Probado que el largo de la lista8 es 5", lista_largo(lista8) == 5);
	print_test("Probando insertar un elemento en la primera posicion de lista8", lista_insertar_primero(lista8, &elem));
	print_test("Probando que el actual del iter8 sea distinto que el primero de lista8", lista_ver_primero(lista8) != lista_iter_ver_actual(iter8));
	
	lista_iter_destruir(iter8);
	lista_destruir(lista8 , NULL);
	
	/* ******************************************************************
	*               Pruebas con lista 9
	* *****************************************************************/
	
	lista_t* lista9 = lista_crear();
	
	int num;
	
	print_test("Probando insertar el elemento en la lista9", lista_insertar_primero(lista9, &num));
	print_test("Probando que el largo de lista9 es 1", lista_largo(lista9));
	
	lista_iter_t* iter9 = lista_iter_crear(lista9);
	
	print_test("Probando que el elemento actual del iter9 no es null", lista_iter_ver_actual(iter9) != NULL);
	print_test("Probando borrar el elemento de lista9 con el iter", lista_borrar(lista9, iter9) == &num);
	print_test("Probando que el largo de lista9 es 0", lista_largo(lista9) == 0);
	print_test("Probando borrar un elemento de la lista9 que esta vacia", lista_borrar(lista9, iter9) == NULL);
	print_test("Probando avanzar en lista9 que esta vacia", lista_iter_avanzar(iter9) == false);
	print_test("Probando agregar un elemento con el iter9", lista_insertar(lista9, iter9, &num));
	print_test("Probando eliminar el ultimo elemento con el iter9", lista_borrar(lista9, iter9) == &num);
	print_test("Probando agregar un elemento en la lista9", lista_insertar_primero(lista9, &num));
	print_test("Probando eliminar el ultimo elemento con borrar primero", lista_borrar_primero(lista9) == &num);
	
	
	lista_iter_destruir(iter9);
	lista_destruir(lista9 , NULL);	
	
	lista_t* lista10= lista_crear();
	
	int i=0;
	
	print_test("Probando agregar un elemento a lista10", lista_insertar_primero(lista10 , &i));
	print_test("Probando eliminar primer elemento", lista_borrar_primero(lista10) != NULL);
	
	lista_destruir(lista10, NULL);
	
	

	
}

int main (){
	lista_prueba();
	return 0;
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

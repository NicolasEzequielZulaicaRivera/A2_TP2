#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TDA/lista.h"
#include "TDA/heap.h"


typedef struct cosa{
    int clave;
    char contenido[10];
}cosa;

cosa* crear_cosa(int clave){

    //static int count = 0;
    char aux [50];
    sprintf(aux,"CONT %i",clave);
    cosa* c = (cosa*)malloc(sizeof(cosa));
    if(c){
        c->clave = clave;
        strcpy( c->contenido , aux );
    }
    return c;
}

void destruir_cosa(void* c){
    free(c);
}

int comparar_cosas(void* elemento1, void* elemento2){
    if(!elemento1 || !elemento2)
        return 0;

    if(((cosa*)elemento1)->clave>((cosa*)elemento2)->clave)
        return 10;
    if(((cosa*)elemento1)->clave<((cosa*)elemento2)->clave)
        return -10;
    return 0;
}

int main(){
  printf("Hello World\n");

  heap_t* heap = heap_crear( comparar_cosas, destruir_cosa );

  heap_insertar( heap, crear_cosa(5) );
  heap_insertar( heap, crear_cosa(10) );
  heap_insertar( heap, crear_cosa(9) );
  heap_insertar( heap, crear_cosa(2) );
  heap_insertar( heap, crear_cosa(3) );
  heap_insertar( heap, crear_cosa(4) );
  heap_insertar( heap, crear_cosa(2) );
  heap_insertar( heap, crear_cosa(5) );
  heap_insertar( heap, crear_cosa(6) );
  heap_insertar( heap, crear_cosa(11) );

  while( heap_raiz(heap) ){
      cosa* pto = (cosa*) heap_raiz(heap);
      printf("%i - ", pto->clave );
      heap_borrar_raiz(heap);
  }

  heap_destruir(heap);

  return 0;
}

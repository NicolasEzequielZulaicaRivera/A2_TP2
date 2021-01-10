#include "heap.h"
#include <stdlib.h>

static const int EXITO =  0;
static const int FALLO = -1;

// El elemento desciende por el arbol mientras que sea mayor que sus hijos,
// siendo remplazado por el menor de ellos en cada paso
void sift_down( heap_t* heap, size_t n );

// El elemento asciende por el arbol mientras que sea menor que su padre
void sift_up( heap_t* heap, size_t n );

// Devuelve la posicion de un pariente segun la presentacion como array del arbol ( empieza en 0 )
size_t posicion_izquierda( size_t n );
size_t posicion_derecha( size_t n );
size_t posicion_padre( size_t n );

// intercambia los elementos de posicion
void intercambiar( heap_t* heap, size_t n, size_t m );


heap_t* heap_crear( heap_comparador comparador, heap_liberar_elemento destructor ){

  if(!comparador) return NULL;

  heap_t* heap = malloc( sizeof( heap_t ) );
  if( !heap ) return NULL;

  heap->comparador = comparador;
  heap->destructor = destructor;
  heap->tamanio = 0;

  return heap;
}

void* heap_raiz(heap_t* heap){
  if( !heap || !heap->tamanio ) return NULL;
  return heap->heap[0];
}


int heap_insertar(heap_t* heap, void* elemento){
  if(!heap) return FALLO;

  heap->heap[ heap->tamanio] = elemento;
  heap->tamanio ++;

  sift_up( heap, heap->tamanio -1  );

  return EXITO;
}

int heap_borrar_raiz(heap_t* heap ){
  if(!heap || !heap->tamanio) return FALLO;

  heap->destructor( heap->heap[0] );

  heap->heap[0] = heap->heap[ heap->tamanio-1 ];
  heap->tamanio --;

  sift_down(heap, 0);

  return EXITO;
}


void heap_destruir( heap_t* heap ){

  for( size_t i = 0 ; i<heap->tamanio ; i++ )
    heap->destructor( heap->heap[i] );

  free( heap );
}


void sift_down( heap_t* heap, size_t n ){

  if(!heap)return;

  size_t izq = posicion_izquierda(n);
  size_t menor = 0;// 0:izquierda | 1:derecha

  if( izq >= heap->tamanio ) return;

  if( izq != heap->tamanio-1 )
    menor = ( heap->comparador( heap->heap[izq],heap->heap[izq+1] ) <= 0 )? 0:1;

  if( heap->comparador( heap->heap[izq+menor],heap->heap[n] ) <= 0 ){
    intercambiar( heap, izq+menor, n );
    sift_down( heap, izq+menor );
  }

}
void sift_up( heap_t* heap, size_t n ){

  if( !heap || n>=heap->tamanio || !n ) return;

  if( heap->comparador( heap->heap[n],heap->heap[ posicion_padre(n) ] ) < 0 ){

    intercambiar( heap, n, posicion_padre(n) );
    sift_up( heap, posicion_padre(n) );
  }

  return;
}

size_t posicion_izquierda( size_t n ){
  return (n+1)*2-1;
}
size_t posicion_derecha( size_t n ){
  return (n+1)*2;
}
size_t posicion_padre( size_t n ){
  if(!n)return 0;
  return ( !(n+1)%2 )? (n+1)/2-1 : n/2-1;
}

void intercambiar( heap_t* heap, size_t n, size_t m ){

  if( !heap || n>=heap->tamanio || m>=heap->tamanio ) return;

  void* aux = heap->heap[n];
  heap->heap[n] = heap->heap[m];
  heap->heap[m] = aux;

}

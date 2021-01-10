#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TDA/lista.h"


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

int main(){
  printf("Hello World\n");

  lista_t* lls = lista_crear( destruir_cosa );

  lista_insertar( lls, crear_cosa(0) );
  lista_insertar( lls, crear_cosa(0) );
  lista_insertar( lls, crear_cosa(0) );
  lista_insertar( lls, crear_cosa(0) );
  lista_insertar( lls, crear_cosa(0) );

  lista_destruir( lls );

  return 0;
}

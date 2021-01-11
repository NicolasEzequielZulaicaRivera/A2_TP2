#include "aventura_pokemon.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>


int comparador_gimnasio( void* g1, void* g2 );
void destructor_gimnasio( void* g );
void destructor_pokemon( void* p );

juego_t* crear_juego(){

  juego_t* juego = malloc( sizeof(juego_t) );
  if(!juego) return NULL;

  juego->gimnasios = heap_crear(comparador_gimnasio,destructor_gimnasio);
  juego->jugador.pokemon_obetenidos = lista_crear(destructor_pokemon);
  juego->jugador.pokemon_batalla = lista_crear(destructor_pokemon);

  if( !juego->gimnasios || !juego->jugador.pokemon_obetenidos || !juego->jugador.pokemon_batalla  ){
    juego_destruir(juego);
    return NULL;
  }

  return juego;
}

void juego_destruir( juego_t* juego ){

  if(!juego) return;

  heap_destruir( juego->gimnasios );
  lista_destruir(juego->jugador.pokemon_obetenidos);
  lista_destruir(juego->jugador.pokemon_batalla);

  free(juego);

}

void cargar_entrenador( juego_t* juego, string archivo ){
  return;
}


void cargar_gimnasio( juego_t* juego, string archivo ){
  return;
}

int comparador_gimnasio( void* g1, void* g2 ){

  if(!g1 || !g2) return 0;

  if( ((gimnasio_t*)g1)->dificultad > ((gimnasio_t*)g2)->dificultad ) return 1;
  if( ((gimnasio_t*)g1)->dificultad < ((gimnasio_t*)g2)->dificultad ) return -1;

  return 0;
}
void destructor_gimnasio( void* g ){
  lista_destruir( ((gimnasio_t*)g)->entrenadores );
  free(g);
}
void destructor_pokemon( void* p ){
  free(p);
}

#include <stdio.h>
#include "aventura_pokemon.h"
#include "../Utilidades/Global.h"

static const size_t MAX_POKEMON_BATALLA = 6;

static const string FORMATO_POKEMON_JUGADOR = "%[^;];%i;%i;%i\n";

void cargar_nombre_jugador( void* jugador, void* lectura );
void cargar_pokemon_jugador( void* jugador, void* lectura );

#define CANT_ETIQUETAS_JUGADOR 2
const etiqueta_t ETIQUETAS_JUGADOR [CANT_ETIQUETAS_JUGADOR] ={
  {.etiqueta="E",.funcion=cargar_nombre_jugador},
  {.etiqueta="P",.funcion=cargar_pokemon_jugador}
};

// Compara dos gimnasios segun su dificultad
// n>0 si g1 es mas dificil que g2
// n<0 si g1 es mas facil que g2
// n=0 si son igual de dificil
int comparador_gimnasio( void* g1, void* g2 );

// Destructores (Liberan la memoria de las estructuras)
void destructor_gimnasio( void* g );
void destructor_entrenador( void* e );
void destructor_pokemon( void* p );

juego_t* crear_juego(){

  juego_t* juego = malloc( sizeof(juego_t) );
  if(!juego) return NULL;

  juego->gimnasios = heap_crear(comparador_gimnasio,destructor_gimnasio);
  juego->jugador.pokemon_obetenidos = lista_crear(destructor_pokemon);
  juego->jugador.pokemon_batalla = lista_crear(NULL);

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

void cargar_jugador( jugador_t* jugador, string ruta ){
  if(!jugador) return;
  FILE* archivo = fopen(ruta,"r");
  if(!archivo) return;

  etiqueta_t etiqueta_obj;
  string etiqueta, lectura;

  while(
  	fscanf( archivo, "%[^;];%[^\n]\n", etiqueta, lectura  ) != EOF
  ){

	  	etiqueta_obj = buscar_etiqueta( etiqueta,
	  		ETIQUETAS_JUGADOR, CANT_ETIQUETAS_JUGADOR );

	  	etiqueta_obj.funcion(jugador,lectura);
  }
  fclose(archivo);
}


void cargar_gimnasio( juego_t* juego, string archivo ){

  gimnasio_t* gimnasio = malloc(sizeof(gimnasio_t));
  if(!gimnasio)return;

  gimnasio->entrenadores = lista_crear( destructor_entrenador );
  if(!gimnasio->entrenadores){
    free(gimnasio);
    return;
  }

  return;
}

int comparador_gimnasio( void* g1, void* g2 ){

  if(!g1 || !g2) return 0;

  if( ((gimnasio_t*)g1)->dificultad > ((gimnasio_t*)g2)->dificultad ) return 1;
  if( ((gimnasio_t*)g1)->dificultad < ((gimnasio_t*)g2)->dificultad ) return -1;

  return 0;
}
void destructor_entrenador( void* e ){
  lista_destruir( ((entrenador_t*)e)->pokemon_batalla );
  free(e);
}
void destructor_gimnasio( void* g ){
  lista_destruir( ((gimnasio_t*)g)->entrenadores );
  free(g);
}
void destructor_pokemon( void* p ){
  free(p);
}

void cargar_nombre_jugador( void* jugador, void* lectura ){
  if( !jugador || !lectura ) return;
  strcpy( ((jugador_t*)jugador)->nombre, lectura );
}
void cargar_pokemon_jugador( void* jugador, void* lectura ){

  if( !jugador || !lectura ) return;
  pokemon_t* pokemon = malloc(sizeof(pokemon_t));
  if(!pokemon) return;

  sscanf( lectura, FORMATO_POKEMON_JUGADOR,
    pokemon->nombre,&(pokemon->velocidad),&(pokemon->ataque),&(pokemon->defensa));

  lista_insertar( ((jugador_t*)jugador)->pokemon_obetenidos, pokemon );

  if( ((jugador_t*)jugador)->pokemon_batalla->cantidad < MAX_POKEMON_BATALLA )
    lista_insertar( ((jugador_t*)jugador)->pokemon_batalla, pokemon );
}

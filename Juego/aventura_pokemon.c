#include <stdio.h>
#include <unistd.h>
#include "aventura_pokemon.h"
#include "../Utilidades/Global.h"

static const size_t MAX_POKEMON_BATALLA = 6;
static const int MAX_BONUS = 63;

static const string FORMATO_ETIQUETAS = "%[^;];%[^\n]\n";
static const string FORMATO_POKEMON_JUGADOR = "%[^;];%i;%i;%i\n";
static const string FORMATO_POKEMON_GIMNASIO = "%[^;]; %i; %i; %i\n";
static const string FORMATO_DATOS_GIMNASIO = "%[^;]; %lu; %lu\n";

void cargar_nombre_jugador( void* jugador, void* lectura );
void cargar_pokemon_jugador( void* jugador, void* lectura );

#define CANT_ETIQUETAS_JUGADOR 2
const etiqueta_t ETIQUETAS_JUGADOR [CANT_ETIQUETAS_JUGADOR] ={
  {.etiqueta="E",.funcion=cargar_nombre_jugador},
  {.etiqueta="P",.funcion=cargar_pokemon_jugador}
};

void cargar_datos_gimnasio( void* gimnasio, void* lectura );
void cargar_lider_gimnasio( void* gimnasio, void* lectura );
void cargar_entrenador_gimnasio( void* gimnasio, void* lectura );
void cargar_pokemon_gimnasio( void* gimnasio, void* lectura );

#define CANT_ETIQUETAS_GIMNASIO 4
const etiqueta_t ETIQUETAS_GIMNASIO [CANT_ETIQUETAS_GIMNASIO] ={
  {.etiqueta="G",.funcion=cargar_datos_gimnasio},
  {.etiqueta="L",.funcion=cargar_lider_gimnasio},
  {.etiqueta="E",.funcion=cargar_entrenador_gimnasio},
  {.etiqueta="P",.funcion=cargar_pokemon_gimnasio}
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

// crea una copia de un pokemon valido y la devuelve, en caso de fallo devuelve NULL
pokemon_t* copia_pokemon(pokemon_t* pokemon );

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
  if(!jugador || access( ruta, F_OK ) ) return;
  FILE* archivo = fopen(ruta,"r");
  if(!archivo) return;

  etiqueta_t etiqueta_obj;
  string etiqueta, lectura;

  while(
  	fscanf( archivo, FORMATO_ETIQUETAS, etiqueta, lectura  ) != EOF
  ){

	  	etiqueta_obj = buscar_etiqueta( etiqueta,
	  		ETIQUETAS_JUGADOR, CANT_ETIQUETAS_JUGADOR );

	  	etiqueta_obj.funcion(jugador,lectura);
  }
  fclose(archivo);
}


void cargar_gimnasio( juego_t* juego, string ruta ){

  if( !juego || access( ruta, F_OK ) )return;

  gimnasio_t* gimnasio = NULL;

  FILE* archivo = fopen(ruta,"r");
  if(!archivo){ destructor_gimnasio(gimnasio); return;};
  etiqueta_t etiqueta_obj;
  string etiqueta, lectura;
  while(fscanf( archivo, FORMATO_ETIQUETAS, etiqueta, lectura  ) != EOF){
    if( !strcmp( etiqueta, ETIQUETAS_GIMNASIO[0].etiqueta ) ){
      if( gimnasio ) heap_insertar( juego->gimnasios, gimnasio );
      gimnasio = malloc(sizeof(gimnasio_t));
      if(!gimnasio){fclose(archivo);return;};
      gimnasio->entrenadores = lista_crear( destructor_entrenador );
      if(!gimnasio->entrenadores){ fclose(archivo);free(gimnasio); return;}
    }

	  etiqueta_obj = buscar_etiqueta( etiqueta,
	  	ETIQUETAS_GIMNASIO, CANT_ETIQUETAS_GIMNASIO );

	  etiqueta_obj.funcion(gimnasio,lectura);
  }
  fclose(archivo);
  if( gimnasio ) heap_insertar( juego->gimnasios, gimnasio );
}

void jugador_cambiar_pokemon(jugador_t* jugador, size_t saliente, size_t entrante){

  if(!jugador) return;

  if( saliente > jugador->pokemon_batalla->cantidad || saliente >= MAX_POKEMON_BATALLA ||
      entrante > jugador->pokemon_obetenidos->cantidad ) return;

  pokemon_t* pokemon = (pokemon_t*)lista_elemento_en_posicion(jugador->pokemon_obetenidos,entrante);

  if( pokemon->en_uso ) return;
  pokemon->en_uso=true;

  ((pokemon_t*)lista_elemento_en_posicion(jugador->pokemon_batalla,saliente))->en_uso = false;
  lista_borrar_de_posicion(jugador->pokemon_batalla,saliente);
  lista_insertar_en_posicion(jugador->pokemon_batalla,pokemon,saliente);

}

bool juego_tomar_pokemon(juego_t* juego, size_t pos_pokemon){
  pokemon_t* pokemon = lista_elemento_en_posicion(
    ( (entrenador_t*)lista_tope(( (gimnasio_t*)heap_raiz(juego->gimnasios) )->entrenadores) )->pokemon_batalla,
    pos_pokemon
  );
  pokemon_t* copia = copia_pokemon(pokemon);
  if(!copia)return false;
  copia->en_uso=false;
  lista_insertar( juego->jugador.pokemon_obetenidos, copia );
  if( juego->jugador.pokemon_batalla->cantidad >= MAX_POKEMON_BATALLA )return true;
  copia->en_uso=true;
  lista_insertar( juego->jugador.pokemon_batalla, copia );

  return true;
}

void pokemon_mejorar( pokemon_t* pokemon, int velocidad, int ataque, int defensa ){
  if(!pokemon)return;
  pokemon->velocidad_bonus += velocidad;
  pokemon->ataque_bonus += ataque;
  pokemon->defensa_bonus += defensa;

  if( pokemon->velocidad_bonus > MAX_BONUS ) pokemon->velocidad_bonus = MAX_BONUS;
  if( pokemon->ataque_bonus > MAX_BONUS ) pokemon->ataque_bonus = MAX_BONUS;
  if( pokemon->defensa_bonus > MAX_BONUS ) pokemon->defensa_bonus = MAX_BONUS;
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

  pokemon->velocidad_bonus = pokemon->ataque_bonus = pokemon->defensa_bonus = 0;
  pokemon->en_uso = false;

  if( ((jugador_t*)jugador)->pokemon_batalla->cantidad >= MAX_POKEMON_BATALLA ) return;

  pokemon->en_uso = true;
  lista_insertar( ((jugador_t*)jugador)->pokemon_batalla, pokemon );
}

void cargar_datos_gimnasio( void* gimnasio, void* lectura ){

  if(!gimnasio || !lectura) return;

  sscanf(lectura,FORMATO_DATOS_GIMNASIO, ((gimnasio_t*)gimnasio)->nombre,
    &((gimnasio_t*)gimnasio)->dificultad, &((gimnasio_t*)gimnasio)->indice_funcion_batalla);
}
void cargar_lider_gimnasio( void* gimnasio, void* lectura ){
  if(!gimnasio || !lectura) return;
  entrenador_t* entrenador = malloc(sizeof(entrenador_t));
  if(!entrenador) return;
  entrenador->pokemon_batalla = lista_crear(destructor_pokemon);
  if( !entrenador->pokemon_batalla ){ free(entrenador); return; }
  sscanf(lectura,"%[^\n]\n",entrenador->nombre);

  lista_insertar( ((gimnasio_t*)gimnasio)->entrenadores, entrenador );
}
void cargar_entrenador_gimnasio( void* gimnasio, void* lectura ){
  if(!gimnasio || !lectura) return;
  entrenador_t* entrenador = malloc(sizeof(entrenador_t));
  if(!entrenador) return;
  entrenador->pokemon_batalla = lista_crear(destructor_pokemon);
  if( !entrenador->pokemon_batalla ){ free(entrenador); return; }
  sscanf(lectura,"%[^\n]\n",entrenador->nombre);

  lista_apilar( ((gimnasio_t*)gimnasio)->entrenadores, entrenador );

}
void cargar_pokemon_gimnasio( void* gimnasio, void* lectura ){
  if(!gimnasio || !lectura || !lista_tope(((gimnasio_t*)gimnasio)->entrenadores) ) return;
  entrenador_t* entrenador = (entrenador_t*)lista_tope(((gimnasio_t*)gimnasio)->entrenadores);

  pokemon_t* pokemon = malloc(sizeof(pokemon_t));
  if(!pokemon) return;

  sscanf( lectura, FORMATO_POKEMON_GIMNASIO,
    pokemon->nombre,&(pokemon->velocidad),&(pokemon->ataque),&(pokemon->defensa));

  pokemon->velocidad_bonus = pokemon->ataque_bonus = pokemon->defensa_bonus = 0;
  pokemon->en_uso = false;

  if( entrenador->pokemon_batalla->cantidad >= MAX_POKEMON_BATALLA ) return;

  pokemon->en_uso = true;
  lista_insertar( entrenador->pokemon_batalla, pokemon );

}
pokemon_t* copia_pokemon(pokemon_t* pokemon ){
  if(!pokemon) return NULL;
  pokemon_t* copia = malloc(sizeof(pokemon_t));
  if(!copia) return NULL;

  strcpy( copia->nombre, pokemon->nombre );
  copia->velocidad = pokemon->velocidad;
  copia->ataque = pokemon->ataque;
  copia->defensa = pokemon->defensa;
  copia->velocidad_bonus = pokemon->velocidad_bonus;
  copia->ataque_bonus = pokemon->ataque_bonus;
  copia->defensa_bonus = pokemon->defensa_bonus;
  copia->en_uso = pokemon->en_uso;

  return copia;
}

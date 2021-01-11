#ifndef __AVENTURA_POKEMON__
#define __AVENTURA_POKEMON__

#include "../Utilidades/Global.h"
#include "../TDA/lista.h"
#include "../TDA/heap.h"

const string RUTA_ENTRENADORES = "../Entrenadores/";
const string RUTA_GIMNASIOS = "../Gimnasios/";

typedef struct pokemon {
  string nombre;
  size_t velocidad;
  size_t ataque;
  size_t defensa;
} pokemon_t;

typedef struct entrenador {
  string nombre;
  lista_t* pokemon_batalla;
} entrenador_t;

typedef struct jugador {
  string nombre;
  lista_t* pokemon_obetenidos;
  lista_t* pokemon_batalla;
} jugador_t;

typedef struct gimnasio {
  string nombre;
  size_t dificultad;
  size_t indice_funcion_batalla;
  lista_t* entrenadores;// pila
} gimnasio_t;

typedef struct juego {
  jugador_t jugador;
  heap_t* gimnasios;
} juego_t;

// Crea un objeto de Juego de Aventura Pokemon, reservando la memoria necesaria
// Devuelve una referencia al juego, o NULL si falla al crearlo
juego_t* crear_juego();

// Libera la memoria reservada por un objeto de Juego de Aventura Pokemon
void juego_destruir( juego_t* juego );

// carga un Entrenador a un objeto de Juego de Aventura Pokemon
// a partir de un archivo ( con referencia a RUTA_ENTRENADORES )
void cargar_entrenador( juego_t* juego, string archivo );

// carga un Gimnasio a un objeto de Juego de Aventura Pokemon
// a partir de un archivo ( con referencia a RUTA_GIMNASIOS )
void cargar_gimnasio( juego_t* juego, string archivo );


#endif /* __AVENTURA_POKEMON__ */

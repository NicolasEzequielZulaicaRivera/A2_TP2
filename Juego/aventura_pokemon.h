#ifndef __AVENTURA_POKEMON__
#define __AVENTURA_POKEMON__

#include "../Utilidades/Global.h"
#include "../TDA/lista.h"
#include "../TDA/heap.h"

typedef struct pokemon {
  string nombre;
  int velocidad;
  int ataque;
  int defensa;
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

// carga un Jugador a un objeto de Juego de Aventura Pokemon
// a partir de un archivo
void cargar_jugador( jugador_t* jugador, string ruta );

// carga un Gimnasio a un objeto de Juego de Aventura Pokemon
// a partir de un archivo
void cargar_gimnasio( juego_t* juego, string archivo );


#endif /* __AVENTURA_POKEMON__ */

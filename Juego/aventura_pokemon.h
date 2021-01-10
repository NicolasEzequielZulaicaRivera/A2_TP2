#ifndef __AVENTURA_POKEMON__
#define __AVENTURA_POKEMON__

#include "../TDA/lista.h"
#include "../TDA/heap.h"

typedef char string [64];

typedef struct pokemon {
  string nombre;
  size_t velocidad;
  size_t ataque;
  size_t defensa;
} pokemon_t;

typedef struct entrenador {
  string nombre;
  lista* pokemon_batalla;
} entrenador_t;

typedef struct jugador {
  string nombre;
  lista* pokemon_obetenidos;
  lista* pokemon_batalla;
} jugador_t;

typedef struct gimnasio {
  string nombre
  lista* entrenadores;
} gimnasio_t;

typedef struct juego {
  jugador_t jugador;
  heap_t* gimnasios;
} juego_t;


#endif /* __AVENTURA_POKEMON__ */

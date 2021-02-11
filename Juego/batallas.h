#ifndef __BATALLAS_H__
#define __BATALLAS_H__

#define CANTIDAD_FUNCIONES_BATALLA 5
#define GANO_PRIMERO 1
#define GANO_SEGUNDO -1

/*
 * Se deberan implementar las 5 funciones de batalla.
 * Las reglas para decidir al ganador las inventan ustedes
 *
 * Si el ganador es el primer pokemon, se devolvera 1
 * Si el ganador es el segundo pokemon, se devolvera -1
 *
 * No habran empates.
 */

int funcion_batalla_1(void* pkm_1, void* pkm_2);

int funcion_batalla_2(void* pkm_1, void* pkm_2);

int funcion_batalla_3(void* pkm_1, void* pkm_2);

int funcion_batalla_4(void* pkm_1, void* pkm_2);

int funcion_batalla_5(void* pkm_1, void* pkm_2);


/*int (*funciones_batalla[CANTIDAD_FUNCIONES_BATALLA])(void*,void*) =
  {funcion_batalla_1,funcion_batalla_2,funcion_batalla_3,funcion_batalla_4,funcion_batalla_5};*/

#endif /* __BATALLAS_H__ */

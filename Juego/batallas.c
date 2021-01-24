#include "batallas.h"
#include "aventura_pokemon.h"

int maximo( int* num, size_t tope ){
  int max = num[0];
  for(size_t i=1;i<tope;i++)
    if( num[i]>max )max=num[i];
  return max;
}

int funcion_batalla_1(void* pkm_1, void* pkm_2){

  int poder1 = ((pokemon_t*)pkm_1)->velocidad+((pokemon_t*)pkm_1)->ataque + ((pokemon_t*)pkm_1)->defensa +
    ((pokemon_t*)pkm_1)->velocidad_bonus+((pokemon_t*)pkm_1)->ataque_bonus + ((pokemon_t*)pkm_1)->defensa_bonus;

  int poder2 = ((pokemon_t*)pkm_2)->velocidad+((pokemon_t*)pkm_2)->ataque + ((pokemon_t*)pkm_2)->defensa +
    ((pokemon_t*)pkm_2)->velocidad_bonus+((pokemon_t*)pkm_2)->ataque_bonus + ((pokemon_t*)pkm_2)->defensa_bonus;

  if( poder2 > poder1 ) return GANO_SEGUNDO;

  return GANO_PRIMERO;
}

int funcion_batalla_2(void* pkm_1, void* pkm_2){
  int poder1 =
    ( ((pokemon_t*)pkm_1)->velocidad+ ((pokemon_t*)pkm_1)->velocidad_bonus )*
    ( ((pokemon_t*)pkm_1)->ataque   + ((pokemon_t*)pkm_1)->ataque_bonus )*
    ( ((pokemon_t*)pkm_1)->defensa  + ((pokemon_t*)pkm_1)->defensa_bonus);

  int poder2 =
    ( ((pokemon_t*)pkm_2)->velocidad+ ((pokemon_t*)pkm_2)->velocidad_bonus )*
    ( ((pokemon_t*)pkm_2)->ataque   + ((pokemon_t*)pkm_2)->ataque_bonus )*
    ( ((pokemon_t*)pkm_2)->defensa  + ((pokemon_t*)pkm_2)->defensa_bonus);

  if( poder2 > poder1 ) return GANO_SEGUNDO;
  return GANO_PRIMERO;
}

int funcion_batalla_3(void* pkm_1, void* pkm_2){

  int poder1[3] =
    {( ((pokemon_t*)pkm_1)->velocidad+ ((pokemon_t*)pkm_1)->velocidad_bonus ),
     ( ((pokemon_t*)pkm_1)->ataque   + ((pokemon_t*)pkm_1)->ataque_bonus ),
     ( ((pokemon_t*)pkm_1)->defensa  + ((pokemon_t*)pkm_1)->defensa_bonus) };
  int poder2[3] =
    {( ((pokemon_t*)pkm_2)->velocidad+ ((pokemon_t*)pkm_2)->velocidad_bonus ),
     ( ((pokemon_t*)pkm_2)->ataque   + ((pokemon_t*)pkm_2)->ataque_bonus ),
     ( ((pokemon_t*)pkm_2)->defensa  + ((pokemon_t*)pkm_2)->defensa_bonus) };

  if( maximo(poder2,3) > maximo(poder1,3) ) return GANO_SEGUNDO;
  return GANO_PRIMERO;
}

int funcion_batalla_4(void* pkm_1, void* pkm_2){
  int poder1[3] =
    {( ((pokemon_t*)pkm_1)->velocidad+ ((pokemon_t*)pkm_1)->velocidad_bonus ),
     ( ((pokemon_t*)pkm_1)->ataque   + ((pokemon_t*)pkm_1)->ataque_bonus ),
     ( ((pokemon_t*)pkm_1)->defensa  + ((pokemon_t*)pkm_1)->defensa_bonus) };
  int poder2[3] =
    {( ((pokemon_t*)pkm_2)->velocidad+ ((pokemon_t*)pkm_2)->velocidad_bonus ),
     ( ((pokemon_t*)pkm_2)->ataque   + ((pokemon_t*)pkm_2)->ataque_bonus ),
     ( ((pokemon_t*)pkm_2)->defensa  + ((pokemon_t*)pkm_2)->defensa_bonus) };

  int gana2 = (poder2[0]>poder1[0])?1:-1 + (poder2[1]>poder1[1])?1:-1 +(poder2[2]>poder1[2])?1:-1;
  if( gana2>0 ) return GANO_SEGUNDO;
  return GANO_PRIMERO;
}

int funcion_batalla_5(void* pkm_1, void* pkm_2){
  int poder1[3] =
    {( ((pokemon_t*)pkm_1)->velocidad+ ((pokemon_t*)pkm_1)->velocidad_bonus ),
     ( ((pokemon_t*)pkm_1)->ataque   + ((pokemon_t*)pkm_1)->ataque_bonus ),
     ( ((pokemon_t*)pkm_1)->defensa  + ((pokemon_t*)pkm_1)->defensa_bonus) };
  int poder2[3] =
    {( ((pokemon_t*)pkm_2)->velocidad+ ((pokemon_t*)pkm_2)->velocidad_bonus ),
     ( ((pokemon_t*)pkm_2)->ataque   + ((pokemon_t*)pkm_2)->ataque_bonus ),
     ( ((pokemon_t*)pkm_2)->defensa  + ((pokemon_t*)pkm_2)->defensa_bonus) };

  int gana2 = (poder2[2]>poder1[0])?1:-1 + (poder2[0]>poder1[1])?1:-1 +(poder2[1]>poder1[2])?1:-1;
  if( gana2>0 ) return GANO_SEGUNDO;
  return GANO_PRIMERO;
}

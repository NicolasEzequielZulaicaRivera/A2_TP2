#include <stdio.h>
#include <string.h>
#include "Utilidades/Global.h"
#include "Juego/aventura_pokemon.h"
#include "Juego/batallas.h"

const string RUTA_ENTRENADORES = "Entrenadores/";
const string RUTA_GIMNASIOS = "Gimnasios/";

static const int INVALIDO = -1;
static const int VALIDO = 0;
static const int PARTIDA_NORMAL = 1;
static const int PARTIDA_SIMULADA = 2;

static const int BATALLA_VICTORIA = 3;
static const int BATALLA_DERROTA = 4;
static const int BATALLA_SIGUIENTE = 5;

static const int OPCION_SALIR = -3;
static const int ERROR = -4;

static const size_t espaciado_mostrar_pokemon = 15;
bool mostrar_pokemon(void* pokemon, void* contexto);
void mostrar_jugador(jugador_t* jugador);
void mostrar_gimnasio(gimnasio_t* gimnasio);
void mostrar_entrenador(entrenador_t* entrenador);


// Funciones de Juego
void cargar_gimnasios(juego_t* juego);
void jugar_partida_normal(juego_t* juego);
void jugar_partida_simulada(juego_t* juego);
bool pedir_pokemon_prestado(juego_t* juego);

// Menus
int menu_error();
int menu_inicio(juego_t* juego);
int menu_inicio_opcion(juego_t* juego, char entrada, bool* entrenador);
int menu_gimnasio(juego_t* juego);
int menu_gimnasio_opcion(juego_t* juego, char entrada);
int menu_batalla(juego_t* juego);
int menu_victoria(juego_t* juego);
int menu_derrota(juego_t* juego);
int cambiar_pokemon_batalla(jugador_t* jugador);
int menu_gimnasio_simulado(juego_t* juego);
int menu_batalla_simulado(juego_t* juego);

int main(){

  juego_t* juego = crear_juego();
  if(!juego) return menu_error();
  cargar_gimnasios(juego);

  int modo = menu_inicio(juego);

  if( modo == PARTIDA_NORMAL )
    jugar_partida_normal(juego);
  else if( modo == PARTIDA_SIMULADA )
    jugar_partida_simulada(juego);

  juego_destruir(juego);
  return 0;
}

int menu_error(){
  printf("\n\n [ HA HABIDO UN ERROR ] \n\n" );
  tocar_para_continuar();
  return INVALIDO;
}
int menu_inicio(juego_t* juego){
  bool entrenador = false;
  char entrada;
  int opcion;
  while(true){
    system("clear");
    printf("\n AVENTURA POKEMON \n");

    printf("\n E - Cargar entrenador principal ");
    printf("\n A - Cargar un gimnasio ");
    if(entrenador){
      printf("\n I - Comenzar partida ");
      printf("\n S - Simular partida ");
    }
    printf("\n ");
    scanf("%c",&entrada);
    opcion = menu_inicio_opcion(juego,entrada,&entrenador);
    if( opcion != INVALIDO ) return opcion;
  }
  return INVALIDO;
}
int menu_inicio_opcion(juego_t* juego, char entrada , bool* entrenador){
  string lectura, archivo;
  switch (entrada) {
    case 'e':
    case 'E':
      printf("\n\n Nombre del archivo: %s", RUTA_ENTRENADORES );
      scanf("%s", lectura );
      strcpy( archivo, RUTA_ENTRENADORES );strcat(archivo, lectura);
      cargar_jugador( &(juego->jugador), archivo );
      mostrar_jugador(&(juego->jugador));
      *entrenador = ( juego->jugador.pokemon_obetenidos->cantidad > 0 );
      break;
    case 'a':
    case 'A':
      printf("\n\n Nombre del archivo: %s", RUTA_GIMNASIOS );
      scanf("%s", lectura );
      strcpy( archivo, RUTA_GIMNASIOS );strcat(archivo, lectura);
      cargar_gimnasio( juego, archivo );
      break;
    case 'i':
    case 'I': if(entrenador) return PARTIDA_NORMAL;
    case 's':
    case 'S': if(entrenador) return PARTIDA_SIMULADA;
    case 'z':
    case 'Z':
      cargar_jugador( &(juego->jugador), "Entrenadores/E1.txt");
      return PARTIDA_SIMULADA;
  };
  return INVALIDO;
}
int menu_gimnasio(juego_t* juego){
  if(!juego ) return menu_error();
  if(!juego->gimnasios->tamanio) return BATALLA_VICTORIA;
  char entrada;
  int opcion = INVALIDO;
  while( ((gimnasio_t*)heap_raiz( juego->gimnasios ))->entrenadores->cantidad > 0 ){
    system("clear");
    printf("\n AVENTURA POKEMON \n");

    printf("\n E - Informacion de entrenador principal ");
    printf("\n G - Informacion de gimnasio ");
    printf("\n C - Cambiar pokemon de batalla ");
    printf("\n B - Comenzar proxima batalla ");
    printf("\n ");
    scanf("%c",&entrada);
    opcion = menu_gimnasio_opcion(juego,entrada);
    if( opcion == OPCION_SALIR ) return OPCION_SALIR;
  }
  heap_borrar_raiz(juego->gimnasios);
  return opcion;
}
int menu_gimnasio_opcion(juego_t* juego, char entrada){
  int retorno;
  switch (entrada) {
    case 'e':
    case 'E':
      mostrar_jugador(&(juego->jugador));
      break;
    case 'g':
    case 'G':
      mostrar_gimnasio( (gimnasio_t*)heap_raiz(juego->gimnasios) );
      break;
    case 'c':
    case 'C':
      cambiar_pokemon_batalla( &(juego->jugador) );
      break;
    case 'b':
    case 'B':
      retorno = BATALLA_SIGUIENTE;
      while(retorno==BATALLA_SIGUIENTE) retorno = menu_batalla( juego );
      return retorno;
      break;
    case 'x':
    case 'X':
      return OPCION_SALIR;
  };
  return INVALIDO;
}
int menu_batalla( juego_t* juego ){
  system("clear");
  printf("\n MENU BATALLA \n\n");

  lista_iterador_t* jugador = lista_iterador_crear( juego->jugador.pokemon_batalla );
  lista_iterador_t* oponente = lista_iterador_crear(
    ( (entrenador_t*)lista_tope( ( (gimnasio_t*)heap_raiz(juego->gimnasios) )->entrenadores ) )->pokemon_batalla
  );
  if( !jugador || !oponente ){
    lista_iterador_destruir(jugador);lista_iterador_destruir(oponente);
    return ERROR;
  }
  size_t indice_batalla = ( (gimnasio_t*)heap_raiz(juego->gimnasios) )->indice_funcion_batalla;
  pokemon_t *p_jugador=NULL, *p_oponente=NULL;
  while ( lista_iterador_tiene_siguiente(jugador) && lista_iterador_tiene_siguiente(oponente) ) {
    p_jugador=lista_iterador_elemento_actual(jugador);
    p_oponente=lista_iterador_elemento_actual(oponente);

    printf("[ %s ]\n", juego->jugador.nombre );
    mostrar_pokemon(p_jugador, NULL);
    printf("\n --- VS --- \n\n");
    printf("[ %s ]\n", ( (entrenador_t*)lista_tope( ( (gimnasio_t*)heap_raiz(juego->gimnasios) )->entrenadores ) )->nombre );
    mostrar_pokemon(p_oponente, NULL);

    if( funciones_batalla[indice_batalla-1]( p_jugador, p_oponente ) == GANO_PRIMERO ){
      printf("Gana el jugador\n");
      pokemon_mejorar(p_jugador,1,1,1);
      lista_iterador_avanzar(oponente);
    }else{
      printf("Gana el oponente\n");
      pokemon_mejorar(p_oponente,1,1,1);/// esto
      lista_iterador_avanzar(jugador);
    }
    printf("\n N: Proximo combate \n");
    char c = ' ';
    while( c!='n' && c!='N' ) scanf("%c",&c );
  }
  bool victoria = !lista_iterador_tiene_siguiente(oponente);
  lista_iterador_destruir(jugador);lista_iterador_destruir(oponente);
  if( victoria && ((gimnasio_t*)heap_raiz(juego->gimnasios))->entrenadores->cantidad == 1 ) return menu_victoria(juego);
  if( !victoria ) return menu_derrota(juego);
  lista_desapilar(((gimnasio_t*)heap_raiz(juego->gimnasios))->entrenadores);
  return BATALLA_SIGUIENTE;
}
int menu_victoria(juego_t* juego){
  char opcion = ' ';
  bool pedir_prestado = true;

  while( opcion!='n' && opcion!='N' ){

    system("clear");
    printf("\n MENU VICTORIA \n");
    if( pedir_prestado )printf("\n T - Pedir pokemon prestado ");
    printf("\n C - Cambiar pokemon de batalla ");
    printf("\n N - Proximo gimnasio ");
    printf("\n ");
    scanf("%c",&opcion);

    if( opcion=='t' || opcion=='T' ) pedir_prestado = !pedir_pokemon_prestado(juego);
    if( opcion=='c' || opcion=='C' ) cambiar_pokemon_batalla( &(juego->jugador) );
    if( opcion=='x' || opcion=='X' ) return OPCION_SALIR;
  }

  tocar_para_continuar();

  lista_desapilar(((gimnasio_t*)heap_raiz(juego->gimnasios))->entrenadores);
  return BATALLA_VICTORIA;
}
int menu_derrota(juego_t* juego){
  char opcion = ' ';
  while( opcion!='r' && opcion!='R' ){

    system("clear");
    printf("\n MENU DERROTA \n");
    printf("\n C - Cambiar pokemon de batalla ");
    printf("\n R - Reintentar ");
    printf("\n F - Finalizar partida ");
    printf("\n ");
    scanf("%c",&opcion);

    if( opcion=='f' || opcion=='F' ) return OPCION_SALIR;
    if( opcion=='c' || opcion=='C' ) cambiar_pokemon_batalla( &(juego->jugador) );
  }

  tocar_para_continuar();
  return BATALLA_DERROTA;
}
int cambiar_pokemon_batalla(jugador_t* jugador){
  mostrar_jugador(jugador);
  size_t saliente, entrante;
  printf("\n Pokemon saliente :");
  scanf("%lu",&saliente );
  printf("\n Pokemon entrante :");
  scanf("%lu",&entrante );

  jugador_cambiar_pokemon(jugador, saliente-1, entrante-1);

  return VALIDO;
}

void cargar_gimnasios(juego_t* juego){
  cargar_gimnasio(juego,"Gimnasios/G1.txt");
}

void jugar_partida_normal(juego_t* juego){
  int opcion = INVALIDO;
  while (juego->gimnasios->tamanio > 0) {
    opcion = menu_gimnasio( juego );
    if(opcion==OPCION_SALIR)return;
  }
  system("clear");
  printf("\n\n >> Has finalizado la aventura pokemon <<\n\n");
  tocar_para_continuar();
}
void jugar_partida_simulada(juego_t* juego){
  int opcion = INVALIDO;
  while (juego->gimnasios->tamanio > 0) {
    opcion = menu_gimnasio_simulado( juego );
    if(opcion==BATALLA_DERROTA){
      printf("\n\n >> Has fallado la aventura pokemon <<\n\n");
      tocar_para_continuar();
      return;
    };
  }
  printf("\n\n >> Has finalizado la aventura pokemon <<\n\n");
  tocar_para_continuar();
}

int menu_gimnasio_simulado(juego_t* juego){
  int opcion;
  printf("\n [ %s ] \n", ((gimnasio_t*)heap_raiz( juego->gimnasios ))->nombre );
  while( ((gimnasio_t*)heap_raiz( juego->gimnasios ))->entrenadores->cantidad > 0 ){
    opcion = menu_batalla_simulado(juego);
    if( opcion == BATALLA_DERROTA ) return BATALLA_DERROTA;
  }
  heap_borrar_raiz(juego->gimnasios);
  return BATALLA_VICTORIA;
}
int menu_batalla_simulado( juego_t* juego ){

  lista_iterador_t* jugador = lista_iterador_crear( juego->jugador.pokemon_batalla );
  lista_iterador_t* oponente = lista_iterador_crear(
    ( (entrenador_t*)lista_tope( ( (gimnasio_t*)heap_raiz(juego->gimnasios) )->entrenadores ) )->pokemon_batalla
  );
  if( !jugador || !oponente ){
    lista_iterador_destruir(jugador);lista_iterador_destruir(oponente);
    return ERROR;
  }
  size_t indice_batalla = ( (gimnasio_t*)heap_raiz(juego->gimnasios) )->indice_funcion_batalla;
  pokemon_t *p_jugador=NULL, *p_oponente=NULL;
  while ( lista_iterador_tiene_siguiente(jugador) && lista_iterador_tiene_siguiente(oponente) ) {
    p_jugador=lista_iterador_elemento_actual(jugador);
    p_oponente=lista_iterador_elemento_actual(oponente);

    printf("[ %s ]\n", juego->jugador.nombre );
    mostrar_pokemon(p_jugador, NULL);
    printf("\n --- VS --- \n\n");
    printf("[ %s ]\n", ( (entrenador_t*)lista_tope( ( (gimnasio_t*)heap_raiz(juego->gimnasios) )->entrenadores ) )->nombre );
    mostrar_pokemon(p_oponente, NULL);

    if( funciones_batalla[indice_batalla-1]( p_jugador, p_oponente ) == GANO_PRIMERO ){
      printf("Gana el jugador\n");
      pokemon_mejorar(p_jugador,1,1,1);
      lista_iterador_avanzar(oponente);
    }else{
      printf("Gana el oponente\n");
      pokemon_mejorar(p_oponente,1,1,1);/// esto
      lista_iterador_avanzar(jugador);
    }
    printf("----------------------------------------------------------------\n");
    //tocar_para_continuar();
  }
  bool victoria = !lista_iterador_tiene_siguiente(oponente);
  lista_iterador_destruir(jugador);lista_iterador_destruir(oponente);
  if( victoria && ((gimnasio_t*)heap_raiz(juego->gimnasios))->entrenadores->cantidad == 1 )printf("\n\n >> Gimnasio superado <<\n\n");;
  if( !victoria ) return BATALLA_DERROTA;
  lista_desapilar(((gimnasio_t*)heap_raiz(juego->gimnasios))->entrenadores);
  return BATALLA_SIGUIENTE;
}

bool mostrar_pokemon(void* pokemon, void* contexto){
  if(!pokemon) return false;
  if(contexto) printf("%i]\t",(*(int*)contexto)++ );

  printf(" %s", ((pokemon_t*)pokemon)->nombre);

  for( size_t i = strlen( ((pokemon_t*)pokemon)->nombre ); i < espaciado_mostrar_pokemon; i++ )
    printf(" ");

  printf("[SPD: %i ]\t[ATK: %i ]\t[DEF: %i ]\n",
    ((pokemon_t*)pokemon)->velocidad + ((pokemon_t*)pokemon)->velocidad_bonus,
    ((pokemon_t*)pokemon)->ataque + ((pokemon_t*)pokemon)->ataque_bonus,
    ((pokemon_t*)pokemon)->defensa + ((pokemon_t*)pokemon)->defensa_bonus
  );
  return true;
}
void mostrar_jugador(jugador_t* jugador){
  size_t i=1;
  if(!jugador || !jugador->pokemon_obetenidos->cantidad ) return;
  printf("\n[[ %s  ]] \n", jugador->nombre );
  printf("\n[[ Pokemon de Batalla  ]] \n" );
  lista_con_cada_elemento(jugador->pokemon_batalla, mostrar_pokemon, &i);
  printf("\n[[ Pokemon Obtenidos  ]] (%lu) \n",jugador->pokemon_obetenidos->cantidad );
  i=1;
  lista_con_cada_elemento(jugador->pokemon_obetenidos, mostrar_pokemon, &i);
  tocar_para_continuar();
}
void mostrar_entrenador( entrenador_t* entrenador ){
  if(!entrenador ) return;
  size_t i=1;
  printf("\n[[ %s  ]] \n", entrenador->nombre );
  printf("\n[[ Pokemon de Batalla  ]] \n" );
  lista_con_cada_elemento(entrenador->pokemon_batalla, mostrar_pokemon, &i);
}
void mostrar_gimnasio(gimnasio_t* gimnasio){
  if(!gimnasio) return;
  printf("\n[[ %s  ]]", gimnasio->nombre );
  printf("\n[ Dificultad: %lu ]", gimnasio->dificultad );
  printf("\n[ Indice de funcion de Batalla: %lu ]", gimnasio->indice_funcion_batalla );

  if( gimnasio->entrenadores->cantidad > 0){
    printf("\n\n[ Proximo Combate ]");
    mostrar_entrenador( lista_primero(gimnasio->entrenadores));
  } else
    printf("\n\n[ No quedan batallas ]");

  tocar_para_continuar();
}
bool pedir_pokemon_prestado(juego_t* juego){
  system("clear");
  mostrar_entrenador(
    lista_primero(((gimnasio_t*)heap_raiz(juego->gimnasios))->entrenadores)
  );
  size_t pokemon;
  scanf("%lu", &pokemon );
  return juego_tomar_pokemon( juego, pokemon-1 );
}

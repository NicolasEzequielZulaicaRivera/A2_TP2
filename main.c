#include <stdio.h>
#include <string.h>
#include "Utilidades/Global.h"
#include "Juego/aventura_pokemon.h"

const string RUTA_ENTRENADORES = "Entrenadores/";
const string RUTA_GIMNASIOS = "Gimnasios/";

static const int INVALIDO = -1;
static const int PARTIDA_NORMAL = 1;
static const int PARTIDA_SIMULADA = 2;

static const size_t espaciado_mostrar_pokemon = 15;
bool mostar_pokemon(void* pokemon, void* contexto);
void mostrar_jugador(jugador_t* jugador);
void mostrar_gimnasio(gimnasio_t* gimnasio);
void mostrar_entrenador(entrenador_t* entrenador);


// Funciones de Juego
void cargar_gimnasios(juego_t* juego);
void jugar_partida_normal(juego_t* juego);
void jugar_partida_simulada(juego_t* juego);

// Menus
int menu_error();
int menu_inicio(juego_t* juego);
int menu_inicio_opcion(juego_t* juego, char entrada, bool* entrenador);
int menu_gimnasio(juego_t* juego);
int menu_gimnasio_opcion(juego_t* juego, char entrada);
int menu_batalla();
int menu_victoria();
int menu_derrota();

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
      return PARTIDA_NORMAL;
  };
  return INVALIDO;
}
int menu_gimnasio(juego_t* juego){
  if(!juego) return menu_error();
  if(!juego->gimnasios->tamanio) return INVALIDO;
  char entrada;
  int opcion;
  while(true){
    system("clear");
    printf("\n AVENTURA POKEMON \n");

    printf("\n E - Informacion de entrenador principal ");
    printf("\n G - Informacion de gimnasio ");
    printf("\n C - Cambiar pokemon de batalla ");
    printf("\n B - Comenzar proxima batalla ");
    printf("\n ");
    scanf("%c",&entrada);
    opcion = menu_gimnasio_opcion(juego,entrada);
    if( opcion != INVALIDO ) return opcion;
  }
  return INVALIDO;
}
int menu_gimnasio_opcion(juego_t* juego, char entrada){
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
      break;
    case 'b':
    case 'B':
      return PARTIDA_NORMAL;
    case 'z':
    case 'Z':
      heap_borrar_raiz(juego->gimnasios);
      return PARTIDA_NORMAL;
  };
  return INVALIDO;
}
int menu_batalla(){
  printf("\n MENU BATALLA");
  return 0;
}
int menu_victoria(){
  printf("\n MENU VICTORIA");
  return 0;
}
int menu_derrota(){
  printf("\n MENU DERROTA");
  return 0;
}

void cargar_gimnasios(juego_t* juego){
  cargar_gimnasio(juego,"Gimnasios/G1.txt");
  cargar_gimnasio(juego,"Gimnasios/G2.txt");
  cargar_gimnasio(juego,"Gimnasios/G3.txt");
  cargar_gimnasio(juego,"Gimnasios/G4.txt");
  cargar_gimnasio(juego,"Gimnasios/G5.txt");
}

void jugar_partida_normal(juego_t* juego){

  while (juego->gimnasios->tamanio > 0) {
    menu_gimnasio( juego );
  }

}
void jugar_partida_simulada(juego_t* juego){

}

bool mostar_pokemon(void* pokemon, void* contexto){
  if(!pokemon) return false;
  if(contexto) printf("%i]\t",(*(int*)contexto)++ );
  printf(" %s", ((pokemon_t*)pokemon)->nombre);

  for( size_t i = strlen( ((pokemon_t*)pokemon)->nombre ); i < espaciado_mostrar_pokemon; i++ )
    printf(" ");

  printf("[SPD: %i ]\t[ATK: %i ]\t[DEF: %i ]\n",((pokemon_t*)pokemon)->velocidad,
    ((pokemon_t*)pokemon)->ataque, ((pokemon_t*)pokemon)->defensa );
  return true;
}
void mostrar_jugador(jugador_t* jugador){
  if(!jugador || !jugador->pokemon_obetenidos->cantidad ) return;
  printf("\n[[ %s  ]] \n", jugador->nombre );
  printf("\n[[ Pokemon de Batalla  ]] \n" );
  lista_con_cada_elemento(jugador->pokemon_batalla, mostar_pokemon, NULL);
  printf("\n[[ Pokemon Obtenidos  ]] (%lu) \n",jugador->pokemon_obetenidos->cantidad );
  size_t i=1;
  lista_con_cada_elemento(jugador->pokemon_obetenidos, mostar_pokemon, &i);
  tocar_para_continuar();
}
void mostrar_entrenador( entrenador_t* entrenador ){
  if(!entrenador ) return;
  printf("\n[[ %s  ]] \n", entrenador->nombre );
  printf("\n[[ Pokemon de Batalla  ]] \n" );
  lista_con_cada_elemento(entrenador->pokemon_batalla, mostar_pokemon, NULL);
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

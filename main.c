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
bool mostar_pokemon(void* pokemon, void* contexto){
  if(!pokemon) return false;
  printf(" %s", ((pokemon_t*)pokemon)->nombre);

  for( size_t i = strlen( ((pokemon_t*)pokemon)->nombre ); i < espaciado_mostrar_pokemon; i++ )
    printf(" ");

  printf("[SPD: %i ][ATK: %i ][DEF: %i ]\n",((pokemon_t*)pokemon)->velocidad,
    ((pokemon_t*)pokemon)->ataque, ((pokemon_t*)pokemon)->defensa );
  return true;
}

void mostrar_jugador(jugador_t* jugador){
  if(!jugador) return;
  printf("\n[[ Jugador  ]] %s \n", jugador->nombre );
  printf("\n[[ Pokemon de Batalla  ]] \n" );
  lista_con_cada_elemento(jugador->pokemon_batalla, mostar_pokemon, NULL);
  printf("\n[[ Pokemon Obtenidos  ]] \n" );
  lista_con_cada_elemento(jugador->pokemon_obetenidos, mostar_pokemon, NULL);
  tocar_para_continuar();
}

// Funciones de Juego
void cargar_gimnasios(juego_t* juego);

// Menus
int menu_error();
int menu_inicio(juego_t* juego);
int menu_inicio_opcion(juego_t* juego, char entrada, bool* entrenador);
int menu_gimnasio();
int menu_batalla();
int menu_victoria();
int menu_derrota();

int main(){

  juego_t* juego = crear_juego();
  if(!juego) return menu_error();

  int modo = menu_inicio(juego);



  juego_destruir(juego);
  return modo;
}

int menu_error(){
  printf("\n\n [ HA HABIDO UN ERROR ] \n\n" );
  tocar_para_continuar();
  return -1;
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
      *entrenador = true;
      break;
    case 'a':
    case 'A':
      break;
    case 'i':
    case 'I': if(entrenador) return PARTIDA_NORMAL;
    case 's':
    case 'S': if(entrenador) return PARTIDA_SIMULADA;
  };
  return INVALIDO;
}
int menu_gimnasio(){
  printf("\n MENU GIMNASIO");
  return 0;
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

#include <stdio.h>
#include <string.h>
#include "Utilidades/Global.h"
#include "Juego/aventura_pokemon.h"

// Funciones de Juego
void cargar_gimnasios(juego_t* juego);

// Menus
int menu_error();
int menu_inicio(juego_t* juego);
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
  string buffer;
  scanf("%s",buffer);
  return -1;
}
int menu_inicio(juego_t* juego){
  bool entrenador = false;
  char entrada;
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
    switch (entrada) {
      case 'e':
      case 'E': entrenador = true;
        break;
      case 'a':
      case 'A':
        break;
      case 'i':
      case 'I': if(entrenador) return 1;
      case 's':
      case 'S': if(entrenador) return 0;
    }
  }
  return 0;
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

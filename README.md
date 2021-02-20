# ¡Una Aventura Pokémon!
![image](https://pbs.twimg.com/media/DEA1iygXsAAg7vC.jpg)

## Juego
  Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.
### Que
  Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.
### Como
  Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.
  
### Compilacion y Ejecucion
  Puede compilar el programa con la siguiente linea en la terminal :

  ` gcc */*.c *.c -Wall -Werror -Wconversion -std=c99 -o nombre_programa `
  > usaremos el compilador gcc nativo a cualquier distribucion linux para compilar todos los archivos c (\*.c)
    en el directorio, empleando diversos *flags* para prevenir errores,
    queda a discrecion del usuario elegir el nombre del programa

  Luego puede ejecutar el programa con la siguiente linea:

  `./nombre_programa`

  Cabe aclarar que la terminal debe encontrarse en el directorio donde se encuentran los archivos del programa para poder llevar su compilacion y ejecucion a cabo.

  Se recomienda  emplear un **makefile** para agilizar estas tareas.
  Se añade en los archivos un makefile que nos permitira usar la linea `make run` que compilara (de ser necesario) y ejecutara el programa.
  
### Comentarios
  Se emplea la libreria `stdlib` y se hace uso de la funcion `system` con comandos que solo aplican a distribuciones linux (algunas)
  Por lo que no se asegura su funcionamiento para todos los sistemas.

## Aventura Pokemon
  Se crea la libreria **aventura_pokemon.h** con el objetivo de proveer las herramientas para la creacion de juegos con tematica de pokemon.

## TDAS
* [Lista, Pila y Cola](https://github.com/NicolasEzequielZulaicaRivera/A2_TDA1)
* [Arbol binario de busqueda](https://github.com/NicolasEzequielZulaicaRivera/A2_TDA2) (no fue utilizado en esta implementacion)
* [Heap]()

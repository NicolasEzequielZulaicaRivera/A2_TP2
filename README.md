# ¡Una Aventura Pokémon!
![image](https://pbs.twimg.com/media/DEA1iygXsAAg7vC.jpg)

## Juego
  Emprende un viaje como entrenador Pokemon a travez del mudo, batallando contra otros entrenadores pokemon y lideres de Gimnasio para probar tus habilidades!
  
### Modo de Juego
  Seleccionando nuestro entrenador principal, el juego nos presentara con una sucesion de gimansios cada vez más desafiantes, donde deberemos derrotar a cada uno de los entrenadores y finalmente a su lider. Para ello deberemos selecionar los pokemones que querremos llevar a cada batalla, mejorar nuestros pokemones mediante victorias, pedir prestados pokemones a entrenadores que hayamos derrotado y decifrar las reglas de combate de cada gimnasio.
  
  El juego se desarrolla mediante una interfaz de texto a travez de una serie de menus que nos mostraran la informacion relevante y las opciones que se puedan tomar.
  
  A travez del menu principal podremos elegir nuestro entrenador principal ( se incluye en el juego el entrenador E1.txt, se favorece la creacion de entrenadores propios  ) y agregar gimnasios ( el juego carga 4 gimnasios incluidos en G1.txt de manera predeterminada e incluye el gimnasio G5.txt, se favorece la creacion de gimnasios propios ).
  
  Se incluye ademas un modo de juego simulado, donde las batallas se realizan automaticamente y el jugador ve el resultado de la aventura pokemon de manera instantanea.
  
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
  
### Implementacion del Juego
  Se implementa el programa en C con en estandar C99 implementando las librerias estandar `stdlib`, `stdio`, `stdbool`, `string`, `stddef`, `unistd`.
  Con un enfoque en las estructuras de datos y el uso de memoria dinamica se busca modularizar el codigo para mejorar su entendimiento.
  Encontraremos la logica de batalla que se aplica a los gimnasios segun su indice de batalla en el archivo `juego/batallas.c` y se espera que los archivos de juego pertinentes se encuentren en las carpetas `Gimnasios/` y `Entrenadores/`.
  
### Comentarios
  Se emplea la libreria `stdlib` y se hace uso de la funcion `system` con comandos que solo aplican a distribuciones linux (algunas)
  Por lo que no se asegura su funcionamiento para todos los sistemas.
  
  Se implementa la libreria `Global.h` como suplemento a caracteristicas que se consideraron escenciales. Lo cual incluye el tipo de dato `string` y `etiqueta_t`( que posee un funcionamiento simplificado al de un diccionario de funciones )

## Aventura Pokemon
  Se crea la libreria **aventura_pokemon.h** con el objetivo de proveer las herramientas para la creacion de juegos con tematica de pokemon.
  
  En ella se definen las estructuras: `pokemon`, `entrenador`, `jugador`, `gimnasio` y `juego` tanto asi como los metodos que se consideraron relevantes para implementar un juego.
  
  No se incluyen en la implementacion las logicas de batalla/juego ya que se considera que sean particulares de cada juego que se cree.

## TDAS
* [Lista, Pila y Cola](https://github.com/NicolasEzequielZulaicaRivera/A2_TDA1)
* [Arbol binario de busqueda](https://github.com/NicolasEzequielZulaicaRivera/A2_TDA2) (no fue utilizado en esta implementacion)
* [Heap(minimal)]()

### Implementacion de TDAS en el programa
* Pokemon: Se utiliza una lista ya que se querra acceder a todos los pokemon de manera simple.
* Entrenadores: Se utiliza una pila ya que los querremos enfrentar de manera secuencial en orden contrario al que esten en el archivo de gimnasio. 
* Gimnasios: Se utiliza un heap minimal ya que solo querremos acceder al gimnasio mas facil presente.

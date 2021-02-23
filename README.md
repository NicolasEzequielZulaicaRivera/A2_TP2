# ¡Una Aventura Pokémon!
![image](https://pbs.twimg.com/media/DEA1iygXsAAg7vC.jpg)

## Juego
  ¡Emprende un viaje como entrenador Pokémon a través del mudo, batallando contra otros entrenadores Pokémon y líderes de Gimnasio para probar tus habilidades!
  
### Modo de Juego
  Seleccionando nuestro entrenador principal, el juego nos presentara con una sucesión de gimnasios cada vez más desafiantes, donde deberemos derrotar a cada uno de los entrenadores y finalmente a su líder. Para ello deberemos seleccionar los pokemones que querremos llevar a cada batalla, mejorar nuestros pokemones mediante victorias, pedir prestados pokemones a entrenadores que hayamos derrotado y descifrar las reglas de combate de cada gimnasio.
  
  El juego se desarrolla mediante una interfaz de texto a través de una serie de menús que nos mostraran la información relevante y las opciones que se puedan tomar.
  
  A través del menú principal podremos elegir nuestro entrenador principal ( se incluye en el juego el entrenador E1.txt, se favorece la creación de entrenadores propios  ) y agregar gimnasios ( el juego carga 4 gimnasios incluidos en G1.txt de manera predeterminada e incluye el gimnasio G5.txt, se favorece la creación de gimnasios propios ).
  
  Se incluye además un modo de juego simulado, donde las batallas se realizan automáticamente y el jugador ve el resultado de la aventura Pokémon de manera instantánea.
  
### Compilación y Ejecución
  Puede compilar el programa con la siguiente línea en la terminal :

  ` gcc */*.c *.c -Wall -Werror -Wconversion -std=c99 -o nombre_programa `
  > usaremos el compilador gcc nativo a cualquier distribución Linux para compilar todos los archivos c (\*.c)
    en el directorio, empleando diversos *flags* para prevenir errores,
    queda a discreción del usuario elegir el nombre del programa

  Luego puede ejecutar el programa con la siguiente línea:

  `./nombre_programa`

  Cabe aclarar que la terminal debe encontrarse en el directorio donde se encuentran los archivos del programa para poder llevar su compilación y ejecución a cabo.

  Se recomienda emplear un **makefile** para agilizar estas tareas.
  Se añade en los archivos un makefile que nos permitirá usar la línea `make run` que compilara (de ser necesario) y ejecutara el programa.
  
### Implementación del Juego
  Se implementa el programa en C con en estándar C99 implementando las librerías estándar `stdlib`, `stdio`, `stdbool`, `string`, `stddef`, `unistd`.
  Con un enfoque en las estructuras de datos y el uso de memoria dinámica se busca modularizar el código para mejorar su entendimiento.
  Encontraremos la lógica de batalla que se aplica a los gimnasios según su índice de batalla en el archivo `juego/batallas.c` y se espera que los archivos de juego pertinentes se encuentren en las carpetas `Gimnasios/` y `Entrenadores/`.
  
### Comentarios
  Se emplea la librería `stdlib` y se hace uso de la función `system` con comandos que solo aplican a distribuciones Linux (algunas)
  Por lo que no se asegura su funcionamiento para todos los sistemas.
  
  Se implementa la librería `Global.h` como suplemento a características que se consideraron esenciales. Lo cual incluye el tipo de dato `string` y `etiqueta_t`( que posee un funcionamiento simplificado al de un diccionario de funciones )

## Aventura Pokémon
  Se crea la librería **aventura_pokemon.h** con el objetivo de proveer las herramientas para la creación de juegos con temática de Pokémon.
  
  En ella se definen las estructuras: `Pokémon`, `entrenador`, `jugador`, `gimnasio` y `juego` tanto así como los métodos que se consideraron relevantes para implementar un juego.
  
  No se incluyen en la implementación las lógicas de batalla/juego ya que se considera que sean particulares de cada juego que se cree.

## TDAS
* [Lista, Pila y Cola](https://github.com/NicolasEzequielZulaicaRivera/A2_TDA1)
* [Árbol binario de busqueda](https://github.com/NicolasEzequielZulaicaRivera/A2_TDA2) (no fue utilizado en esta implementación)
* [Heap(minimal)]()

### Implementación de TDAS en el programa
* Pokémon: Se utiliza una lista ya que se querrá acceder a todos los Pokémon de manera simple.
* Entrenadores: Se utiliza una pila ya que los querremos enfrentar de manera secuencial en orden contrario al que estén en el archivo de gimnasio. 
* Gimnasios: Se utiliza un heap minimal ya que solo querremos acceder al gimnasio más fácil presente.

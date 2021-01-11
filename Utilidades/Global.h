#ifndef __UTL_GLOBAL__
#define __UTL_GLOBAL__

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

typedef char string [64];

typedef struct etiqueta {

    string etiqueta;

    void (*funcion)( void* p, void* q );
} etiqueta_t;

//const etiqueta_t ETIQUETA_INVALIDA;

// Devuelve una etiqueta (obj) segun su etiqueta (string)
etiqueta_t buscar_etiqueta( string etiqueta,
		const etiqueta_t* vector_etiquetas, size_t cantidad_etiquetas );

#endif /* __UTL_GLOBAL__ */

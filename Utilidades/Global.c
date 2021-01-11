#include "Global.h"

const etiqueta_t ETIQUETA_INVALIDA = {
		.etiqueta = "",
		.funcion = NULL
	};

etiqueta_t buscar_etiqueta( string etiqueta,
	const etiqueta_t* vector_etiquetas, size_t cantidad_etiquetas ){

   	for( size_t i = 0; i < cantidad_etiquetas; i++ ){

   		if( strcmp( etiqueta, vector_etiquetas[i].etiqueta )==0 )
   			return vector_etiquetas[i];
   	}

   	return ETIQUETA_INVALIDA;
}

#ifndef _CAMARA_
#define _CAMARA_

#include "Algebra.h"

class Camara {

	public:
		// Posición de la cámara
		Punto posicion;
		// Vector de dirección de la cámara
		Punto look;
		// Ancho vertical en grados
		float fov;

		Camara();
		Camara(Punto posicion, Punto look, float fov);

		// Devuelve un vector obtenido a partir de la posicion de la camara
		// y del punto indicado
		Punto trazarRayo(Punto inicio, Punto direccion);
};

#endif

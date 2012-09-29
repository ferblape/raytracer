#include "Camara.h"

Camara::Camara() {};

Camara::Camara(Punto posicion, Punto look, float fov) {

	this->posicion = posicion;
	this->look = look;
	this->fov = fov;
};

// Traza un rayo desde inicio en la direccion indicada
Punto Camara::trazarRayo(Punto inicio, Punto direccion) {

	
};

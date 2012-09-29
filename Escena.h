#ifndef _ESCENA_
#define _ESCENA_

#include "Primitiva.h"
#include "FuenteLuminosa.h"
#include "Camara.h"
#include <vector>

#define MAXPROFUNDIDAD 3

typedef std::vector<Punto> VPuntos;

class Escena {

	public:
		// Vector de primitivas
		typedef std::vector<Primitiva*> VPrimitivas;
		VPrimitivas primitivas;

		// Vector de luces
		typedef std::vector<FuenteLuminosa*> VLuces;
		VLuces luces;
		VLuces luces_purgado;

		// Camara
		Camara camara;

		Escena();

		// Inserta una nueva primitva en la Escena
		void insertarPrimitiva(Primitiva* p);
	
		// Inserta una nueva fuente luminosa
		void insertarLuz(FuenteLuminosa* f);	
		
		// Modificar cámara
		void modificarCamara(Camara ncamara);

		// Dibuja todos los objetos de la escena
		void dibujar();
		
		// Traza un rayo para todas las primitivas de la escena 
		// y calcula sus interesecciones
		RGB trazarRayo(Punto origen, Punto direccion, int profundidad,int pos,float coeficiente);

		RGB trazarRayoGL(Punto origen, Punto direccion);

		void purgar(Punto interseccion, VLuces luces, VLuces *luces_purgado,Primitiva *primitiva);
		
};

#endif

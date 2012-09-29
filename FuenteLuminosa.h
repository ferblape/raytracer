#ifndef _FLUMINOSA_
#define _FLUMINOSA_

#include "Algebra.h"
#include "RGB.h"

#define AMBIENTAL 0
#define PUNTUAL 1
#define DIRECCIONAL 2
#define FOCALIZADA 3

class FuenteLuminosa {
	public:
		Punto direccion;
		Punto centro; 		// Punto donde está colocada la luz
		RGB i; 				// Intensidad de la luz
		float n; 			// Exponente de ....
		int tipo;
		
		// Devuelve la intensidad de la fuente emitida en la superficie 
		// en direccion al punto p, como un RGB
		virtual RGB intensidad(Punto p)=0;

		// Devuelve el vector unitario de iluminación sobre el punto p
		// de la superficie.
		// Si la luz es ambiente devuelve (0,0,0)
		virtual Punto L(Punto p)=0;

};


class Ambiental: public FuenteLuminosa {

	public:
		Ambiental(); 

		RGB intensidad(Punto p);
		Punto L(Punto p);
};

class Puntual : public FuenteLuminosa {

	public:
		Puntual(Punto centro_); 

		RGB intensidad(Punto p);
		Punto L(Punto p);
};

class Direccional : public FuenteLuminosa {

	public:
		Direccional(Punto direccion_); 

		RGB intensidad(Punto p);
		Punto L(Punto p);

};

class Focalizada : public FuenteLuminosa {

	public:
		float factor;
		Focalizada(Punto centro_, Punto direccion_, float factor_); 

		RGB intensidad(Punto p);
		Punto L(Punto p);
};

#endif

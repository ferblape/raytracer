#include "FuenteLuminosa.h"
#include "Primitiva.h"
#include <math.h>

/********************* A M B I E N T A L ********************/

Ambiental::Ambiental() {

		centro = Punto(); 	
		i = RGB(1,1,1); 		
		n = 50; 		
		tipo = AMBIENTAL;
}


RGB Ambiental::intensidad(Punto p) {

	return i;
}

Punto Ambiental::L(Punto p) { return Punto(0,0,0); }


/********************* P U N T U A L ********************/

Puntual::Puntual(Punto centro_) {

		centro = centro_; 	
		i = RGB(0.5,0.5,0.5); 		
		n = 100; 
		tipo = PUNTUAL;
}

RGB Puntual::intensidad(Punto p) {
	return i;
}

Punto Puntual::L(Punto p) { return centro - p; }


/********************* D I R E C C I O N A L ********************/

Direccional::Direccional(Punto direccion_) {

		direccion = direccion_;
		centro = Punto(); 	
		i = RGB(1,1,1); 		
		n = 100; 
		tipo = DIRECCIONAL;
}

RGB Direccional::intensidad(Punto p) {

	return i;
}

Punto Direccional::L(Punto p) { return direccion; }



/********************* F O C A L I Z A D A ********************/

Focalizada::Focalizada(Punto centro_, Punto direccion_, float factor_) {

		centro = centro_; 	
		factor = factor_;
		direccion = direccion_.normalizar();
		i = RGB(1,1,1); 		
		n = 200; 
		tipo = FOCALIZADA;
}

RGB Focalizada::intensidad(Punto p) {
	float t = direccion*(p-centro).normalizar();
	t = powf(t,factor);
	return i*t;
}

Punto Focalizada::L(Punto p) {return centro - p; }


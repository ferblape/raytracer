#ifndef _RENDER_
#define _RENDER_

#include "Escena.h"
#include "Camara.h"

class Render {
	public:
		int alto, ancho;
		Punto up;
		// Vector de colores de la escena
		// 
		typedef std::vector<RGB> VRGB;
		VRGB raster;
		// unsigned int *raster;
		virtual void renderiza(Escena escena, Camara c)=0;

};


class RenderOpenGL: public Render {
	public:
		void renderiza(Escena escena, Camara c);

};

class RenderRayTracer: public Render {
	public:
		int alto, ancho;
		RenderRayTracer(int alto, int ancho);
		void renderiza(Escena escena, Camara c);
		// Vuelca el contenido del buffer en el raster y lo pinta
		void volcar_raster();

};	

#endif

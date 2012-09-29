#include "Render.h"
#include "Primitiva.h"
// #include <GLUT/gl.h>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <iostream>
#include <unistd.h>
#include <math.h>

using namespace std;

void RenderOpenGL::renderiza(Escena escena, Camara c) {

	typedef std::vector<Primitiva*> VPrimitivas;
	VPrimitivas::iterator i;
	for(i=escena.primitivas.end()-1;i!=escena.primitivas.begin()-1;i--) {
		(*i)->dibujar();
	}
};

RenderRayTracer::RenderRayTracer(int alto, int ancho) {

	this->alto = alto;
	this->ancho = ancho;
	up = Punto(0,1,0);
}

void RenderRayTracer::renderiza(Escena escena, Camara c) {

	RGB color;

	// float i,j;
	int i,j;

	float alfa = (c.fov*PI)/360.0;
	float dist = 0.5/tan(alfa);

	float incx = 1.0/(float)ancho*1.0;
	float incy = 1.0/(float)alto*1.0;

	float aspectratio = (float)ancho/(float)alto;
	float alfaw = alfa*aspectratio;
	float ancho_a = tan(alfaw)*dist;


	Punto centro = c.posicion + (c.look - c.posicion).normalizar()*dist;

	// Vector horizontal y vertical por los que se mueve 
	Punto horizontal = up^(c.look - c.posicion);
	horizontal.normalizar();
	Punto vertical = (c.look - c.posicion).normalizar()^horizontal;
	vertical.normalizar();

	Punto direccion = centro - horizontal*ancho_a - vertical*0.5;
	for(i=0;i<ancho;i++) {
		for(j=0;j<alto;j++) {
			// trazamos un rayo desde centro hasta x,y -> devuelve un color
			//
			// (direccion+horizontal*i*incx+vertical*j*incy - c.posicion).escribir();
			// 
			color = escena.trazarRayo(c.posicion,(direccion+horizontal*i*incx+vertical*j*incy - c.posicion).normalizar(),1,-1,1);
			raster.push_back(color);
		}
	}
	cerr << "Tiempo renderizado:  ";
};


void RenderRayTracer::volcar_raster() {

	int i,j;

	VRGB::iterator k;
	k = raster.begin();
	for(i=ancho;i>0;i--) {
		for(j=0;j<alto;j++) {
			glBegin(GL_POINTS);
				glColor3f(k->r,k->g,k->b);
				glVertex3i(i,j,0);
			glEnd();
			k++;
		}
	}
};


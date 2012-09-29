#include <iostream>
#include <math.h>
#include "Escena.h"
#include "FuenteLuminosa.h"
#include "Camara.h"
#include "Primitiva.h"
#include "Algebra.h"
#include "RGB.h"

using namespace std;

Escena::Escena(){};

void Escena::insertarPrimitiva(Primitiva *p) {

	bool insertado = false;

	primitivas.push_back(p);
};

void Escena::insertarLuz(FuenteLuminosa* f) {

	luces.push_back(f);
}

void Escena::modificarCamara(Camara ncamara) {
	
	camara = ncamara;
};

void Escena::dibujar() {};

void Escena::purgar(Punto interseccion, VLuces luces, VLuces *luces_purgado,Primitiva *primitiva){
	
	VLuces::iterator l;
	VPrimitivas::iterator i;
	float t,tprimitiva;
	Punto lorigen, ldireccion;
	int lnintersecciones;
	bool meter = true;
	float distancia = 10000000;
	
	// Recorremos todas las luces
	for(l=luces.begin();l!=luces.end();l++) {
		// Si la luz es ambiental se añade 
		if ((*l)->tipo == AMBIENTAL) {
			luces_purgado->push_back(*l);
			continue;
		}
		
		// Origen de la luz
		lorigen = (*l)->centro;

		// Dirección de la luz
		if ((*l)->tipo == DIRECCIONAL) { 
			lorigen = interseccion;
			ldireccion = (*l)->direccion;
			luces_purgado->push_back(*l);
			continue;
		}
		else
			ldireccion = (interseccion - (*l)->centro).normalizar(); 
			

		// Recorremos las primitivas para ver si la luz atraviesa alguna de ellas
		for(i=primitivas.begin();i!=primitivas.end();i++) {
			// Calculamos la intersección de un rayo que parte de la luz con cualquier
			// primitiva
			lnintersecciones=(*i)->puntosInterseccion(lorigen,ldireccion,&t); 
			// Si hay intersección y ésta está entre el origen de la luz
			// y la intersección con la primitiva, entonces no se mete la luz
			if (lnintersecciones > 0) {
				// if ((*l)->tipo == DIRECCIONAL) {
				// 	meter = false;
				// 	continue;
				// }

				if (t < distancia && t > 0)
					distancia = t;
				if (*i==primitiva) {
					tprimitiva = t;
				}
			}
		}
		// Primera interseccion de la luz con una de las primitivas
		if (distancia >= tprimitiva)	
			luces_purgado->push_back(*l);
	}	
}
			
RGB Escena::trazarRayo(Punto origen, Punto direccion, int profundidad,int pos, float coeficiente) {

	float t;
	float distancia = +100000000;
	int nintersecciones;
	int contador;
	int primitiva_inter;
	VPrimitivas::iterator i;
	// Primitiva donde intersecciona
	Primitiva *primitiva;
	// color del punto de la última intersección
	RGB color;
	RGB color_primitiva;
	RGB color_transmitido;
	// boolean de si hay intersección
	bool interseccion = false;
	VLuces luces_purgado;
	VLuces::iterator l;
	Punto inter;

	// Si el coeficiente es menor de 0.1 se devuelve negro
	if (coeficiente <= 0.1)
		return RGB(0,0,0);

	for(i=primitivas.begin(),contador=0;i!=primitivas.end();i++,contador++) {
		// Calculamos la interseccion con la primitiva i
		luces_purgado.clear();
		nintersecciones=(*i)->puntosInterseccion(origen,direccion,&t); 
		if (nintersecciones > 0){
			if (t < distancia && t > 0)  {
				distancia = t;
				interseccion = true;
				primitiva = *i;
				primitiva_inter = contador;
			}
		}
		// Si no hay intersecciones con ese objeto, pasamos al siguiente
		else 
			continue;	
	}
	
	// Si no ha habido intersección devolvemos color negro
	if (!interseccion) {
		return RGB(0,0,0);
	}

	// primitiva: primitiva donde intersecciona
	// inter: punto donde se produce la intersección
	// primitiva_inter: posicion de la primitiva de la interseccion
	// luces_purgado: vector de luces purgado
	// Calculamos la reflexión

	inter = origen + direccion*distancia;
	Punto acumulado = Punto(0,0,0);
	Punto L, H, N, V,R;
	float escalar;
	
	// Recalculamos el vector de luces purgado
	purgar(inter+N*0.001,luces,&luces_purgado,primitiva);
	// Obtenemos el color de la primitiva que intersecta
	color_primitiva = primitiva->color(inter,origen,luces_purgado);

	for(l=luces_purgado.begin();l!=luces_purgado.end();l++) {

		// Si es la primera luz se inicializa color a negro
		if (l == luces_purgado.begin())
			color = RGB(0,0,0);

		// Ambiental
		if ((*l)->tipo == AMBIENTAL) {
			RGB istemp = (*l)->intensidad(inter);
			Punto is = Punto(istemp.r,istemp.g,istemp.b);
			Punto temp = is*primitiva->material.kd;
			color = color + RGB(temp.x, temp.y,temp.z)*color_primitiva;
			// Si la luz es ambiental se salta
			continue;
		}

		// Especular
		L = (*l)->L(inter);
		L.normalizar();
		V = (inter-origen).normalizar();
		H = (L+V)/((L+V).modulo());
		N = primitiva->normal(inter); 
		RGB istemp = (*l)->intensidad(inter);
		Punto is = Punto(istemp.r,istemp.g,istemp.b);
		escalar = H*N;
		escalar = powf(escalar,(*l)->n);
		Punto temp = is*primitiva->material.ks*escalar;
		acumulado = temp;

		// Difusa
		istemp = (*l)->intensidad(inter);
		is = Punto(istemp.r,istemp.g,istemp.b);
		float nl = N*L;
		temp = is*primitiva->material.kd*nl;
		acumulado = acumulado + temp;
			
		color = color + RGB(acumulado.x, acumulado.y,acumulado.z)*color_primitiva;
		
	}
	// Reflexión
	float nl = N*direccion.negado();
	R = (N*2*nl) + direccion;
	if (profundidad <= MAXPROFUNDIDAD) {
		color_transmitido = trazarRayo(inter+N*0.001,R,profundidad+1,primitiva_inter,coeficiente*primitiva->material.kd);
		color = color + color_transmitido*primitiva->material.ks;
	}	
	else 
		color = RGB(0,0,0);

	return color;
};

RGB Escena::trazarRayoGL(Punto origen, Punto direccion) {
//
// 
// 	VPuntos intersecciones;
// 	Punto *puntero;
// 
// 	// Dibujamos el rayo desde el centro de la cámara hasta p
// 
// 	VPrimitivas::iterator i;
// 	VPuntos::iterator j;
// 	for(i=primitivas.begin();i!=primitivas.end();i++) {
// 		cerr << "Punto destino: ";
// 		if ((*i)->puntosInterseccion(origen,direccion,&intersecciones)) {
// 			/*for(j=intersecciones.begin();j!=intersecciones.end();j++) {
// 				cerr << "Interseccion: ";
// 				j->escribir();
// 				j->color(0,0,1);
// 				// Dibujamos el punto de intersección
// 				j->dibujar();
// 			} */
// 			intersecciones[0].dibujar();
// 		}
// 	};
// 	cerr << "Fin intersecciones" << endl;
// 

}

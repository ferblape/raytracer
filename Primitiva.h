#ifndef _PRIMITIVA_
#define _PRIMITIVA_

#include "Algebra.h"
#include "RGB.h"
#include "Material.h"
#include "FuenteLuminosa.h"
#include <vector>

#define PI 3.141592653
#define PIDdos 1.570796327
#define dosPI 6.283185307

#define PLANO 1
#define OTRO 2

typedef std::vector<FuenteLuminosa*> VLuces;

class Primitiva {
    // Primitiva es una clase abstracta
    public:
        Punto posicion;         // Posicion en la que se encuentra el objeto
        typedef std::vector<Punto> VPuntos;
        VPuntos vertices; // Vector de vertices del objeto
        VPuntos normales; // Vector con las normales
		Material material;
		int tipo;
		float zmax;

		Primitiva();
        // Devuelve la normal del punto p
        virtual Punto normal(Punto p)=0;
        // Dado un rayo u que atraviese la Primitiva partiendo del punto p
        // devuelve un vector de puntos en los que intersecta
        virtual int puntosInterseccion(Punto p, Punto u, float *t)=0;
        // Devuelve true si el punto esta dentro y viceversa
        virtual bool dentro(Punto p)=0;
        // Dibuja la primitiva
        virtual void dibujar()=0;
		// Devuelve el color en un determinado punto
		virtual RGB color(Punto p, Punto origen, VLuces luces);
};

class Plano: public Primitiva {

    public:
        
		// Colores tablero
		RGB color1, color2;
		float ancho;
		bool checked;
		
		// El plano queda definido por su normal
        Plano(Punto pos);

        // Devuelve la normal del punto p
        Punto normal(Punto p);
		// Dado un rayo u que atraviese la Primitiva partiendo del punto p
        // devuelve un vector de puntos en los que intersecta
        int puntosInterseccion(Punto p, Punto u, float *t);
        // Devuelve true si el punto esta dentro y viceversa
        bool dentro(Punto p);
        // Dibuja la primitiva
        void dibujar();
		RGB color(Punto p, Punto origen, VLuces luces);
};


class Esfera: public Primitiva {

    public:
		float radio;    // Radio del círculo
        int precision;  // Precisión
        
        Esfera(Punto centro, float radio, int precision);

        // Devuelve la normal del punto p
        Punto normal(Punto p);
		// Dado un rayo u que atraviese la Primitiva partiendo del punto p
        // devuelve un vector de puntos en los que intersecta
        int puntosInterseccion(Punto p, Punto u, float *t);
        // Devuelve true si el punto esta dentro y viceversa
        bool dentro(Punto p);
        // Dibuja la primitiva
        void dibujar();
};

class Triangulo: public Primitiva {

	public:
		VPuntos proyeccion;
		int proyecc;
		int i0,i1,i2;

		// Constructor
		Triangulo(Punto p0, Punto p1, Punto p2);
	
        // Devuelve la normal del punto p
		Punto normal(Punto p);
		// Dado un rayo u que atraviese la Primitiva partiendo del punto p
        // devuelve un vector de puntos en los que intersecta
		int puntosInterseccion(Punto p, Punto u, float *t);
        // Devuelve true si el punto esta dentro y viceversa
        bool dentro(Punto p);
        // Dibuja la primitiva
        void dibujar();
		// Devuelve el color en un determinado punto
};

class Cuadrilatero: public Primitiva {

	public:
		bool dibuja_normal;
		bool dibuja_proyecciones;
		Triangulo *t1,*t2;

		// Constructor
		Cuadrilatero(Punto p0, Punto p1, Punto p2, Punto p3);
        // Devuelve la normal del punto p
		Punto normal(Punto p);
		// Dado un rayo u que atraviese la Primitiva partiendo del punto p
        // devuelve un vector de puntos en los que intersecta
		int puntosInterseccion(Punto p, Punto u, float *t);
        // Devuelve true si el punto esta dentro y viceversa
        bool dentro(Punto p);
        // Dibuja la primitiva
        void dibujar();
};


class Cubo: public Primitiva {

	public:
   
		// p0 es el punto superior derecha más lejano
		// p1 es el punto inferior izquierda más cercano
		Punto ph,pl;

		// Constructor
		Cubo(Punto p0, Punto p1);
		
        // Devuelve la normal del punto p
		Punto normal(Punto p);
		// Dado un rayo u que atraviese la Primitiva partiendo del punto p
        // devuelve un vector de puntos en los que intersecta
		int puntosInterseccion(Punto p, Punto u, float *t);
        // Devuelve true si el punto esta dentro y viceversa
        bool dentro(Punto p);
        // Dibuja la primitiva
        void dibujar();
};


#endif

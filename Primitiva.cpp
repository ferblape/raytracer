// #include <GLUT/gl.h>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include "Algebra.h"
#include "Primitiva.h"
#include "Material.h"
#include "FuenteLuminosa.h"
#include "Escena.h"
#include <iostream>
#include <math.h>

using namespace std;

RGB Primitiva::color(Punto p,Punto origen, VLuces luces) {
	return material.color;
};

Primitiva::Primitiva() {};


/* ***** PLANO ******* */

Plano::Plano(Punto pos) {

	posicion = pos;
	checked = true;
	material = Material(material.color,0.5,0.5);
	color1 = RGB(1,0,0);
	color2 = RGB(0,1,0);
	ancho = 0.3;
	zmax = 99999999;
	tipo = PLANO;
}

Punto Plano::normal(Punto p) {return Punto(0,1,0);};


int Plano::puntosInterseccion(Punto p, Punto u, float *t) {
	
	// Un plano viene determinado por A,B,C y D
	// En nuestro caso A y C = 0
	// B = 1; D = -posicion.y

	bool v = false;
	Punto normal = Punto(0,1,0);

	// Si el rayo es paralelo al plano no hay intersección
	float paralelo = normal*u;
	if (paralelo == 0)
		return 0;

	*t = -(normal*p - posicion.y)/paralelo;

	// Si la t es negativa la intersección ocurre por detrás del origen del rayo
	// y no sirve de nada la intersección
	if (*t < 0)
		return 0;
	return 1;
};


bool Plano::dentro(Punto p) {

	if (p.y == posicion.y)
		return true;
	return false;
};


void Plano::dibujar() {
};


RGB Plano::color(Punto p,Punto origen, VLuces luces) {

	Punto acumulado = Punto(0,0,0);
	Punto L, H, N, V;
	float escalar;

	// Determinamos el color del tablero
	RGB col;

	float x = p.x / ancho;
	float z = p.z / ancho;
	x = roundf(x);
	z = roundf(z);
	
	if (abs(int(x)%2) == 1)
		if (abs(int(z)%2) == 1)
			col = color2;
		else
			col = color1;
	else
		if (abs(int(z)%2) == 1)
			col = color1;
		else
			col = color2;
	
	// Si no es textura de ajedrez
	if (!checked)
		col = material.color;
	return col;

};



/* ***** ESFERA ******* */
Esfera::Esfera(Punto centro, float radio, int precision) {
	
	posicion = centro;
	zmax = centro.z;
	this->radio = radio;
	this->precision = precision;
	material = Material(RGB(1,0,0),0.5,0.5);
	tipo = OTRO;

    Punto p; // Punto auxiliar
    Punto n; // Vector normal auxiliar

    // Si el radio es 0 o menor, se dibuja un punto
    // en el centro de la esfera
    if (radio <= 0)
        vertices.push_back(centro);
        
    double theta1,theta2,theta3;

    for (int j=0;j<=(precision/2);j++) {
        theta1 = j * dosPI / precision - PIDdos;
        theta2 = (j + 1) * dosPI / precision - PIDdos;

        for (int i=0;i<=precision;i++) {
		    theta3 = i * dosPI / precision;
        
			n.x = cos(theta1) * cos(theta3);
            n.y = sin(theta1);
            n.z = cos(theta1) * sin(theta3);
            normales.push_back(n);
 
            p.x = posicion.x + radio * n.x;
            p.y = posicion.y + radio * n.y;
            p.z = posicion.z + radio * n.z;
            vertices.push_back(p);
        }
    }
};


Punto Esfera::normal(Punto p) {return (p - posicion).normalizar();};


int Esfera::puntosInterseccion(Punto p, Punto u, float *t) {

	// Vector u = Origen + t*(Destino)
	// t : incognita
	// Q = Origen = p
	// V = Destino  
	// rayo = p + t*u

	bool v = false;
	float t1,t2;

	u.normalizar();

	Punto Q = p - posicion;
	Punto V = u;
	
	float a = V*V;
	float b = 2*(Q*V);
	float c = (Q*Q) - radio*radio;

	//
	// if (v) cerr << "a: "<<a<<" - b: "<<b<<" - c: "<<c<<endl;
	// 
	
	// Cogemos, de las dos soluciones, la negativa, porque es la que antes 
	// intersectará de las dos
	float D = b*b - 4*a*c;
	//
	// if (v) cerr << "D: "<<D<<" " <<sqrt(D)<<endl;
	// 
	if (D < 0) {
		return 0;
	}
	else {
		t1 = (-b - sqrt(D)) / (2*a);
		if (D == 0) {
			*t = t1;
			return 1;
		}
		t2 = (-b + sqrt(D)) / (2*a);
		if (t1 > t2) {
			*t = t2;
			return 1;
		}
		*t = t1;
		return 1;
	}
		//
		// if ((t1 > 0 && t2 <0)) {
		// 	*t = t1;
		// 	return 1;
		// }
		// if ((t1 < 0 && t2>0)) {
		// 	*t = t2;
		// 	return 1;
		// }
		// 
			
	
};


bool Esfera::dentro(Punto p) {

	if (p.x*p.x + p.y*p.y + p.z*p.z < radio*radio)
		return true;
	else
		return false;

};


void Esfera::dibujar() {
    
	glColor3f(material.color.r,material.color.g,material.color.b);
    VPuntos::iterator i;
	// Lineas horizontales
	int contador = 0;
	glBegin(GL_LINE_STRIP);
    for(i=vertices.begin(); i!=vertices.end(); i++) {
		if (contador >= 0 && contador <= precision)
			glVertex3f(i->x,i->y,i->z);
		if (contador == precision) {
			contador = -1;
			glEnd();
			glBegin(GL_LINE_STRIP);
		}
		contador++;
	}
	glEnd();

	// Lineas verticales
    for (int j=0;j<=precision;j++) {
		glBegin(GL_LINE_STRIP);
		contador = 0;
    	for(i=vertices.begin(); i!=vertices.end(); i++) {
			if (contador == j)		
				glVertex3f(i->x,i->y,i->z);
			if (contador == precision)
				contador = -1;
			contador++;
		}
		glEnd();
	}
};

/* ***** TRIANGULO ******* */
#define max(a,b,c) (a>b?a>c?a:c:b>c?b:c)
// Constructor
Triangulo::Triangulo(Punto p0, Punto p1, Punto p2) {

	// Vertices en sentido antihorario
	vertices.push_back(p0);
	vertices.push_back(p1);
	vertices.push_back(p2);
	
	zmax = max(p0.z,p1.z,p2.z);	
	tipo = OTRO;

	posicion = (p0 + p1 + p2) / 3;

	Punto normal = (p2-p1)^(p0-p2);
	normal.normalizar();
	normales.push_back(normal);

	material = Material(RGB(0,1,0),0.5,0.5);

	// Proyectamos el polígono en el plano 
	if (fabs(normales[0].x) > fabs(normales[0].y) && fabs(normales[0].x) > fabs(normales[0].z)) { 
		// Proyectamos sobre las X
		proyecc = 1;
		i0 = proyecc - 1;
		i1 = 1;
		i2 = 2;
	}
	else if (fabs(normales[0].y) > fabs(normales[0].x) && fabs(normales[0].y) > fabs(normales[0].z)) {
		// Proyectamos sobre las Y
		proyecc = 2;
		i0 = proyecc - 1;
		i1 = 0;
		i2 = 2;
	}
	else {
		// Proyectamos sobre las Z
		proyecc = 3;
		i0 = proyecc - 1;
		i1 = 0;
		i2 = 1;
	}
	// i1 = (i0-1)%3;
	// i2 = (i0+1)%3;

};

// Devuelve la normal del punto p
Punto Triangulo::normal(Punto p) {
	return normales[0];
};


// Dado un rayo u que atraviese la Primitiva partiendo del punto p
// devuelve un vector de puntos en los que intersecta
int Triangulo::puntosInterseccion(Punto p, Punto u, float *t) {

	// Primiero calculamos la interseccion con el plano que lo contiene
	Punto int_plano;

	float den = normales[0]*u;
	// El rayo es paralelo
	if (den == 0)
		return 0;
	// Despejamos la t para el plano
	*t = (vertices[0]*normales[0] - normales[0]*p)/den;
	if (*t <= 0)
		return 0;
	
	// Obtenemos el punto interior al plano
	int_plano = p + (u*(*t));

	if (dentro(int_plano)) {
		// El punto es interior
		// Insertamos el punto sin proyectar
		// Sólo puede intersectar un punto por rayo
		return 1;
	}
	return 0;
};


// Devuelve true si el punto esta dentro y viceversa
bool Triangulo::dentro(Punto int_plano) {
	
	VPuntos::iterator i;
	Punto aux;
	
	float u0,v0,u1,v1,u2,v2;

	u0 = int_plano[i1] - vertices[0][i1];
	v0 = int_plano[i2] - vertices[0][i2];

	u1 = vertices[1][i1] - vertices[0][i1];
	v1 = vertices[1][i2] - vertices[0][i2];

	u2 = vertices[2][i1] - vertices[0][i1];
	v2 = vertices[2][i2] - vertices[0][i2];

	float alfa, beta;
	alfa = (u0*v2 - u2*v0)/(u1*v2 - u2*v1);
	beta = (u1*v0 - u0*v1)/(u1*v2 - u2*v1);

	return (alfa>=0 && beta >=0 && alfa+beta<=1);
}

// Dibuja la primitiva
void Triangulo::dibujar() {

	// Dibujo aristas
	glColor3f(material.color.r,material.color.g,material.color.b);
	glBegin(GL_LINE_LOOP);
		glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);
		glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);
		glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);
	glEnd();

};


/* ***** CUADRADO ******* */

// Constructor
Cuadrilatero::Cuadrilatero(Punto p0, Punto p1, Punto p2, Punto p3) {
	
	vertices.push_back(p0);
	vertices.push_back(p1);
	vertices.push_back(p2);
	vertices.push_back(p3);
	tipo = OTRO;

	t1 = new Triangulo(p0,p1,p2);
	t2 = new Triangulo(p0,p2,p3);

	posicion = (p0 + p1 + p2 + p3) / 4;

	//Punto normal = (p3-p0)^(p1-p0);
	//Punto normal = (p0-p1)^(p2-p1);
	//normal.normalizar();
	//normales.push_back(normal);
	normales.push_back(t2->normales[0]);
	//
	// normales.push_back(Punto(0,1,0));
	// 
	

	dibuja_normal = true;
	dibuja_proyecciones = false;

	material = Material(RGB(1,1,1),0.5,0.5);
	zmax = max(max(p0.z,p1.z,p2.z),p2.z,p3.z);

};

// Devuelve la normal del punto p
Punto Cuadrilatero::normal(Punto p) { return normales[0]; };


// Dado un rayo u que atraviese la Primitiva partiendo del punto p
// devuelve un vector de puntos en los que intersecta
int Cuadrilatero::puntosInterseccion(Punto p, Punto u, float *t){
	int n = t1->puntosInterseccion(p,u,t);
	if (n>0)
		return n;
	n = t2->puntosInterseccion(p,u,t);
	if (n>0)
		return n;
	return 0;
};


// Devuelve true si el punto esta dentro y viceversa
bool Cuadrilatero::dentro(Punto p){ 
	return (t1->dentro(p) || t2->dentro(p));
};

// Dibuja la primitiva
void Cuadrilatero::dibujar(){

	VPuntos::iterator i;

	glColor3f(material.color.r,material.color.g,material.color.b);
	glBegin(GL_LINE_LOOP);
	for(i=vertices.begin();i!=vertices.end();i++)
		glVertex3f(i->x,i->y,i->z);
	glEnd();

	if (dibuja_normal) {
		glColor3f(0,1,0);
		glBegin(GL_LINES);
			glVertex3f(posicion.x, posicion.y, posicion.z);
			glVertex3f(posicion.x + normales[0].x*2, posicion.y + normales[0].y*2, posicion.z + normales[0].z*2); 
		glEnd();
	}
};


/* ****** CUBO ******* */

// Constructor
Cubo::Cubo(Punto p0, Punto p1){

	// p0 es el punto superior derecha más lejano
	// p1 es el punto inferior izquierda más cercano
	ph = p0;
	pl = p1;
	posicion = Punto((ph.x + pl.x)/2, (ph.y + pl.y)/2, (ph.z + pl.z)/2);
	zmax = pl.z;
	tipo = OTRO;

	// Calculamos las 6 normales
	// Cara delantera
	normales.push_back(Punto(0,0,1));
	// Cara trasera
	normales.push_back(Punto(0,0,-1));
	// Cara superior
	normales.push_back(Punto(0,1,0));
	// Cara inferior
	normales.push_back(Punto(0,-1,0));
	// Cara derecha
	normales.push_back(Punto(1,0,0));
	// Cara izquierda
	normales.push_back(Punto(-1,0,0));

	material = Material(RGB(0,1,1),0.5,0.5);
};
  
// Devuelve la normal del punto p
Punto Cubo::normal(Punto p){
	Punto temp =  (p - posicion).normalizar();

	if (fabs(temp.x) >= fabs(temp.y) && fabs(temp.x) >= fabs(temp.z)) {
		if (temp.x > 0)
			return Punto(1,0,0);
		else
			return Punto(-1,0,0);
	}
	if (fabs(temp.y) >= fabs(temp.x) && fabs(temp.y) >= fabs(temp.z)) {
		if (temp.y > 0)
			return Punto(0,1,0);
		else
			return Punto(0,-1,0);
	}
	if (fabs(temp.z) >= fabs(temp.x) && fabs(temp.z) >= fabs(temp.y)) {
		if (temp.z > 0)
			return Punto(0,0,1);
		else
			return Punto(0,0,-1);
	}
	/*
	if (fabs(temp.x) >= fabs(temp.y) && fabs(temp.x) >= fabs(temp.z)) {
		temp.y = 0;
		temp.z = 0;
	}
	
	if (fabs(temp.y) >= fabs(temp.x) && fabs(temp.y) >= fabs(temp.z)) {
		temp.x = 0;
		temp.z = 0;
	}
	if (fabs(temp.z) >= fabs(temp.x) && fabs(temp.z) >= fabs(temp.y)) {
		temp.x = 0;
		temp.y = 0;
	}

	VPuntos::iterator i;
	for(i=normales.begin();i!=normales.end();i++) {
		if (temp*(*i) <=1 && temp*(*i)>=-1)	
			return (*i);
	}
	*/
};

// Dado un rayo u que atraviese la Primitiva partiendo del punto p
// devuelve un vector de puntos en los que intersecta
int Cubo::puntosInterseccion(Punto p, Punto u, float *t){

	float tcerca = -10000, tlejos = 100000;
	float temp;
	
	// X slab
	float Xh = ph.x;
	float Xl = pl.x;
	if (u.x == 0) {
		if (p.x < Xl || p.x > Xh)
			return 0;
	}
	else {
		float t1x = (Xl - p.x)/u.x;
		float t2x = (Xh - p.x)/u.x;

		if (t1x > t2x) {
			temp = t1x;
			t1x = t2x;
			t2x = temp;
		}
		if (t1x > tcerca)
			tcerca = t1x;
		if (t2x < tlejos)
			tlejos = t2x;

		if (tcerca > tlejos)
			return 0;
		if (tlejos < 0)
			return 0;
	}
	// Y slab
	float Yh = ph.y;
	float Yl = pl.y;
	if (u.y == 0) {
		if (p.y < Yl || p.y > Yh)
			return 0;
	}
	else {
		float t1y = (Yl - p.y)/u.y;
		float t2y = (Yh - p.y)/u.y;

		if (t1y > t2y) {
			temp = t1y;
			t1y = t2y;
			t2y = temp;
		}
		if (t1y > tcerca)
			tcerca = t1y;
		if (t2y < tlejos)
			tlejos = t2y;

		if (tcerca > tlejos)
			return 0;
		if (tlejos < 0)
			return 0;
	}
	// Z slab
	float Zh = ph.z;
	float Zl = pl.z;
	if (u.z == 0) {
		if (p.z > Zl || p.z < Zh)
			return 0;
	}
	else {
		float t1z = (Zl - p.z)/u.z;
		float t2z = (Zh - p.z)/u.z;

		if (t1z > t2z) {
			temp = t1z;
			t1z = t2z;
			t2z = temp;
		}
		if (t1z > tcerca)
			tcerca = t1z;
		if (t2z < tlejos)
			tlejos = t2z;

		if (tcerca > tlejos)
			return 0;
		if (tlejos < 0)
			return 0;
	}
	// intersecciones->push_back(u*tcerca + p);
	// intersecciones->push_back(u*tlejos + p);
	// return 2;
	*t = tcerca;
	return 1;
};


// Devuelve true si el punto esta dentro y viceversa
bool Cubo::dentro(Punto p) {

};


// Dibuja la primitiva
void Cubo::dibujar() {
	// Dibujar los vertices a partir de ph y pl
	// ph es el punto superior derecha más lejano
	// pl es el punto inferior izquierda más cercano

	// -- Orden antihorario -- 
	glColor3f(material.color.r,material.color.g,material.color.b);

	// Cara superior 
	glBegin(GL_LINE_LOOP);
		glVertex3f(ph.x,ph.y,ph.z);
		glVertex3f(pl.x,ph.y,ph.z);
		glVertex3f(pl.x,ph.y,pl.z);
		glVertex3f(ph.x,ph.y,pl.z);
	glEnd();
	// Cara frontal
	glBegin(GL_LINE_LOOP);
		glVertex3f(ph.x,ph.y,pl.z);
		glVertex3f(pl.x,ph.y,pl.z);
		glVertex3f(pl.x,pl.y,pl.z);
		glVertex3f(ph.x,pl.y,pl.z);
	glEnd();
	// Cara trasera
	glBegin(GL_LINE_LOOP);
		glVertex3f(ph.x,ph.y,ph.z);
		glVertex3f(ph.x,pl.y,ph.z);
		glVertex3f(pl.x,pl.y,ph.z);
		glVertex3f(pl.x,ph.y,ph.z);
	glEnd();
	// Cara Inferior
	glBegin(GL_LINE_LOOP);
		glVertex3f(pl.x,pl.y,pl.z);
		glVertex3f(pl.x,pl.y,ph.z);
		glVertex3f(ph.x,pl.y,ph.z);
		glVertex3f(ph.x,pl.y,pl.z);
	glEnd();
	// Cara izquierda
	glBegin(GL_LINE_LOOP);
		glVertex3f(pl.x,pl.y,pl.z);
		glVertex3f(pl.x,ph.y,pl.z);
		glVertex3f(pl.x,ph.y,ph.z);
		glVertex3f(pl.x,pl.y,ph.z);
	glEnd();
	// Cara derecha
	glBegin(GL_LINE_LOOP);
		glVertex3f(ph.x,ph.y,ph.z);
		glVertex3f(ph.x,ph.y,pl.z);
		glVertex3f(ph.x,pl.y,pl.z);
		glVertex3f(ph.x,pl.y,ph.z);
	glEnd();

};


%{

// #include <GL/gl.h>
#include <GLUT/glut.h>
#include <iostream>
#include <time.h>
#include "Primitiva.h"
#include "FuenteLuminosa.h"
#include "Camara.h"
#include "Escena.h"
#include "Render.h"

#include "def.h"
#include "gramatica.h"

extern Camara camara;
extern Escena escena;

extern int yylineno;

extern "C" {
	int yylex( void );
}

void yyerror( const char *msg) {
    fprintf(stderr, "Linea %3d: %s\n", yylineno, msg);
}

%}


%union {
	char *cadena;
	float real;
	tPunto punto;
	tColor color;
	tChecker checker;
}

%token <cadena> ID_
%token ABRELLAVE_
%token CIERRALLAVE_
%token MENOR_
%token FACTOR_
%token MAYOR_
%token COMA_
%token <real> FLOAT_
%token PUNTOCOMA_
%token COMILLAS_
%token <cadena> CADENA_
%token LOCATION_
%token LOOKAT_
%token CAMERA_
%token AMBIENTAL_
%token COLOR_
%token PUNTUAL_
%token DIRECCIONAL_
%token FOCAL_
%token SPHERE_
%token PLANE_
%token CHECKER_
%token SIZE_
%token CUBE_
%token QUADRILATERAL_
%token TRIANGLE_
%token ESPECULAR_
%token DIFFUSE_
%token FOV_

%type <punto> coordenadas
%type <color> color
%type <checker> checker

%%

escena: { escena = Escena(); } 
		camara_ luces objetos
;

camara_: CAMERA_ ABRELLAVE_ LOCATION_  coordenadas     LOOKAT_   coordenadas FOV_ FLOAT_ CIERRALLAVE_
		{ camara = Camara(Punto($4.x,$4.y,$4.z),Punto($6.x,$6.y,$6.z),$8); }
;

coordenadas:  MENOR_ FLOAT_ COMA_ FLOAT_ COMA_ FLOAT_ MAYOR_
			{ $$.x = $2; $$.y = $4; $$.z = $6; }
;


// Falta indicar la reflexion
color: COLOR_ MENOR_ FLOAT_ COMA_ FLOAT_ COMA_ FLOAT_ MAYOR_ ESPECULAR_ FLOAT_ DIFFUSE_ FLOAT_
		{ $$.r = $3; $$.g = $5; $$.b = $7; $$.ks = $10; $$.kd = $12;}
	  | COLOR_ MENOR_ FLOAT_ COMA_ FLOAT_ COMA_ FLOAT_ MAYOR_ 
		{ $$.r = $3; $$.g = $5; $$.b = $7; $$.ks = 0.5; $$.kd = 0.5;}
;

objetos: 	| objeto otro_objeto
;

objeto: 	esfera  | plano | cubo | triangulo | cuadrado
;

otro_objeto:	| esfera otro_objeto | plano otro_objeto | cubo otro_objeto | triangulo otro_objeto | cuadrado otro_objeto
;

esfera: SPHERE_ ABRELLAVE_ coordenadas COMA_ FLOAT_ color CIERRALLAVE_
	{
		Esfera *e = new Esfera(Punto($3.x,$3.y,$3.z),$5,50);
		e->material.color.set($6.r,$6.g,$6.b);
		e->material.kd = $6.kd;
		e->material.ks = $6.ks;
		escena.insertarPrimitiva(e);
	}
;

triangulo: TRIANGLE_ ABRELLAVE_ coordenadas coordenadas coordenadas color CIERRALLAVE_
	{
		Triangulo *t = new Triangulo(Punto($3.x,$3.y,$3.z),Punto($4.x,$4.y,$4.z),Punto($5.x,$5.y,$5.z));
		t->material.color.set($6.r,$6.g,$6.b);
		t->material.kd = $6.kd;
		t->material.ks = $6.ks;
		escena.insertarPrimitiva(t);
	}
;

cuadrado: QUADRILATERAL_ ABRELLAVE_ coordenadas coordenadas coordenadas coordenadas color CIERRALLAVE_
	{
		Cuadrilatero *c = new Cuadrilatero(Punto($3.x,$3.y,$3.z),Punto($4.x,$4.y,$4.z),Punto($5.x,$5.y,$5.z),Punto($6.x,$6.y,$6.z));
		c->material.color.set($7.r,$7.g,$7.b);
		c->material.kd = $7.kd;
		c->material.ks = $7.ks;
		escena.insertarPrimitiva(c);
	}
;

checker: CHECKER_ ABRELLAVE_ color color SIZE_ FLOAT_ CIERRALLAVE_
	{
		$$.color1.r = $3.r;
		$$.color1.g = $3.g;
		$$.color1.b = $3.b;
		
		$$.color2.r = $4.r;
		$$.color2.g = $4.g;
		$$.color2.b = $4.b;

		$$.ancho = $6;
	}
;

plano: PLANE_ ABRELLAVE_ FLOAT_ color CIERRALLAVE_
	{ 
		Plano *p = new Plano($3);
		p->checked = false;
		p->material.color.set($4.r,$4.g,$4.b);
		p->material.kd = $4.kd;
		p->material.ks = $4.ks;
		escena.insertarPrimitiva(p);
	}
		| PLANE_ ABRELLAVE_ FLOAT_ checker CIERRALLAVE_
		
	{ 
		Plano *p = new Plano($3);
		p->checked = true;
		p->color1 = RGB($4.color1.r,$4.color1.g,$4.color1.b);
		p->color2 = RGB($4.color2.r,$4.color2.g,$4.color2.b);
		p->ancho = $4.ancho;
		escena.insertarPrimitiva(p);
	}
;

cubo: CUBE_ ABRELLAVE_ coordenadas coordenadas color  CIERRALLAVE_
	{
		Cubo *c = new Cubo(Punto($3.x,$3.y,$3.z),Punto($4.x,$4.y,$4.z));
		c->material.color.set($5.r,$5.g,$5.b);
		c->material.kd = $5.kd;
		c->material.ks = $5.ks;
		escena.insertarPrimitiva(c);
	}

/* LUCES */

luces:	|	luz otra_luz
;

luz:		ambiental | puntual | direccional | focal
;

otra_luz:	| ambiental otra_luz | puntual otra_luz  | direccional otra_luz | focal otra_luz
;

ambiental: AMBIENTAL_ ABRELLAVE_ color CIERRALLAVE_
	{ 
		Ambiental *a = new Ambiental();
		a->i = RGB($3.r,$3.g,$3.b);
		escena.insertarLuz(a);
	};
;

puntual: PUNTUAL_ ABRELLAVE_ coordenadas color CIERRALLAVE_
  	{
		Puntual *p = new Puntual(Punto($3.x,$3.y,$3.z));
		p->i = RGB($4.r,$4.g,$4.b);
		escena.insertarLuz(p);
	}

direccional: DIRECCIONAL_ ABRELLAVE_ coordenadas color CIERRALLAVE_
	{
		Direccional *d = new Direccional(Punto($3.x,$3.y,$3.z));
		d->i = RGB($4.r,$4.g,$4.b);
		escena.insertarLuz(d);
	}

focal: FOCAL_ ABRELLAVE_ coordenadas coordenadas FACTOR_ FLOAT_ color CIERRALLAVE_
    {
		Focalizada *f = new Focalizada(Punto($3.x,$3.y,$3.z),Punto($4.x,$4.y,$4.z),$6);
		f->i = RGB($7.r,$7.g,$7.b);
		escena.insertarLuz(f);
	}

%%


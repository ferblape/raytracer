// #include <GL/gl.h>
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h> // Header File For The OpenGL32 Library
#include <OpenGL/glu.h> // Header File For The GLu32 Library
#include <GLUT/glut.h> // Header File For The GLut Library
#include <GLUT/glut.h>
#include <iostream>
#include <time.h>
#include "Primitiva.h"
#include "FuenteLuminosa.h"
#include "Camara.h"
#include "Escena.h"
#include "Render.h"

// Parser
#include "def.h"
#include "gramatica.h"

using namespace std;

// Variables globales
// Ancho y alto por defecto
int ancho = 320;
int alto = 320;
// Tipo de render: 1-opengl, 2-raytracer
int tipo_render = 1; 

Camara camara;
Escena escena;
RenderRayTracer *render; 
RenderOpenGL *ogl;

// Contadores de tiempo
clock_t ti, tf;


// PARSER
extern FILE *yyin;
extern int yylineno;


int yyparse (void);
int yylex( void );
int yyerror( const char * );
//////////////////////////////////////

// Inicialización de variables de la GL y globales
void myinit(int alto, int ancho) {

    glClearColor(0.0, 0.0, 0.0, 0.0);
	
	// Primitivas

	// Esfera *e = new Esfera(Punto(0.1,0.2,-1.2),0.2,50);
	// escena.insertarPrimitiva(e);

	// Esfera *e2 = new Esfera(Punto(0,0.3,0),0.3,50);
	// e2->rgb.set(0.2,0.5,1);
	// escena.insertarPrimitiva(e2);
	
	// Plano *plano = new Plano(0);
	// escena.insertarPrimitiva(plano);

	// Triangulo *t = new Triangulo(Punto(-0.4,0,-2),Punto(0.4,0,-2),Punto(0,0.4,-2));
	// Triangulo *t = new Triangulo(Punto(0,0.6,-2),Punto(0.8,0.2,0),Punto(-0.3,0,-0));
	// escena.insertarPrimitiva(t);
	// 
	// Cuadrilatero *c = new Cuadrilatero(Punto(-0.2,0.4,-1),Punto(0.2,0.4,-1),Punto(0.2,0,-1),Punto(-0.2,0,-1));
	// escena.insertarPrimitiva(c);
	// 
	// Cuadrilatero *c2 = new Cuadrilatero(Punto(-0.5,1,-2),Punto(-0.5,1,0),Punto(-0.5,0,0),Punto(-0.5,0,-2));
	// escena.insertarPrimitiva(c2);
	
	// Cubo *cu = new Cubo(Punto(-0.3,0.6,-2),Punto(0.3,0,-1.4));
	// escena.insertarPrimitiva(cu);
	
	// Circulo *ci = new Circulo(Punto(0,1,-1),2);
	// escena.insertarPrimitiva(ci);
	
	// Luces
	// Ambiental *a = new Ambiental();
	// escena.insertarLuz(a);
	//
	// Puntual *p = new Puntual(Punto(1,1,-3));
	// escena.insertarLuz(p);
	//
	// Puntual *p2 = new Puntual(Punto(-1,1,2));
	// escena.insertarLuz(p2);

	// Direccional *d = new Direccional(Punto(1,1,1),Punto(0.5,0.2,0));
	// escena.insertarLuz(d);

	// Creamos los Render
	render = new RenderRayTracer(alto,ancho);
	render->renderiza(escena,camara);
	ogl = new RenderOpenGL();
	tf = clock();
	cout << double(tf-ti)/CLOCKS_PER_SEC << " segundos" << endl;
}


void display(void) {

	glClear(GL_COLOR_BUFFER_BIT);	// Borra la ventana
	glPushMatrix();
	glViewport(0, 0, ancho, alto);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (tipo_render == 2) {
	 	//glOrtho(-1.0, 1.0, -1.0*(GLfloat)alto/(GLfloat)ancho,1.0*(GLfloat)alto/(GLfloat)ancho, -30.0, 30.0);

		gluPerspective(45.0f,(GLdouble)ancho/alto,10,0);
		//
		// if (ancho <= alto)
			// glOrtho(-1.0, 1.0, -1.0*(GLfloat)alto/(GLfloat)ancho, 
			// 	1.0*(GLfloat)alto/(GLfloat)ancho, -30.0, 30.0);
		// else
		// glOrtho(-1.0*(GLfloat)ancho/(GLfloat)alto, 
		// 		1.0*(GLfloat)ancho/(GLfloat)alto, -1.0, 1.0, -30.0, 30.0);
		// glFrustum(-1,1,-1.0*(GLdouble)alto/ancho,1.0*(GLdouble)alto/ancho,-30,30);
		glMatrixMode(GL_MODELVIEW); 
		glLoadIdentity();
		gluLookAt(camara.posicion.x,camara.posicion.y,camara.posicion.z, camara.look.x,camara.look.y, camara.look.z,0,1,0);
		ogl->renderiza(escena,camara);
	}

	if (tipo_render == 1) {	
	    gluOrtho2D(0.0, ancho, 0.0, alto);
    	glMatrixMode(GL_MODELVIEW);
	    glLoadIdentity();
		render->volcar_raster();
	}
	glPopMatrix();
	
	glFlush();
}


//Función de respuesta a la acción de cambio de tamaño de la ventana
void myReshape(GLsizei w, GLsizei h) {

	
	// Original
	/*glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, w, 0.0, h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0,0,w,h);*/
    
	// Render Raytracer
	/*
	if (tipo_render == 1) {	
	    h = (h == 0) ? 1 : h;
    	glViewport(0,0,w,h);
		glMatrixMode(GL_PROJECTION);
	    glLoadIdentity();
	    gluOrtho2D(0.0, w, 0.0, h);
    	glMatrixMode(GL_MODELVIEW);
	    glLoadIdentity();
	}
	// Render OpenGL
	if (tipo_render == 2) {
		h = (h == 0) ? 1 : h;
		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		if (w <= h)
			glOrtho(-1.0, 1.0, -1.0*(GLfloat)h/(GLfloat)w, 
				1.0*(GLfloat)h/(GLfloat)w, -30.0, 30.0);
		else
		glOrtho(-1.0*(GLfloat)w/(GLfloat)h, 
				1.0*(GLfloat)w/(GLfloat)h, -1.0, 1.0, -30.0, 30.0);
		glMatrixMode(GL_MODELVIEW); 
		glLoadIdentity();
	}
	*/
}



void keyboard (unsigned char key, int x, int y) {

	switch(key) {
		
		case 27:
		case 'q':
		case 'Q':
			exit(0);
			break;

		case 'o':
			tipo_render=2;
			glutPostRedisplay();
			break;
	
		case 'r':
			tipo_render=1;
			glutPostRedisplay();
			break;
		
		default:
			break;
	}
}



int main(int argc, char** argv) {
	
	// Inicializamos el reloj
	ti = clock();

	for (int i=1;i<argc;i++) {
		if (!strcmp(argv[i],"-h")) {
			alto = atoi(argv[++i]);
		}
		if (!strcmp(argv[i],"-w")) {
			ancho = atoi(argv[++i]);
		}
		if (!strcmp(argv[i],"-f")) {
		  	if ((yyin = fopen(argv[i+1], "r")) == NULL)
				cerr <<  "Fichero no válido " <<argv[i+1] << endl;
			else 
				yyparse();
		}
		if (!strcmp(argv[i],"-help") || !strcmp(argv[i],"--help") || !(strcmp(argv[i],"-h"))) {
			cout << "Raytracer para las prácticas de SIA" << endl;
			cout << "Fernando Blat Peris <ferblape@inf.upv.es>" << endl;
			cout << argv[0] << " -h alto -w ancho -f escena -v " << endl;
			cout << " > -h alto: indica el alto de la ventana (por defecto 320) " << endl;
			cout << " > -w ancho: indica el ancho de la ventana (por defecto 320) " << endl;
			cout << " > -f fichero: indica el fichero escenico del que se leerá la escena " << endl;
			exit(0);
		}
	}
	
   	glutInit(&argc, argv);
   	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   	glutInitWindowSize (ancho,alto); 
   	glutInitWindowPosition (400, 50);
	glutCreateWindow ("Raytracer - SIA");
	myinit(alto,ancho);
   	glutDisplayFunc(display); 
	glutKeyboardFunc(keyboard);
   	glutReshapeFunc(myReshape);
	glutMainLoop();
	return(0);
}

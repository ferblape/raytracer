//Clases basicas de geometria y algebra

//#include "stdafx.h" //incluir para V6.0 practica SIA con interfaz

#include <iostream.h>
#include <math.h>
#include "Algebra.h"
#include <GLUT/glut.h>

#define PI 3.14159f
#define cuadrado(x) x*x
#define cubo(x) x*x*x

// Clase Punto -------------------------------------------
//--------------------------------------------------------

//Constructor por defecto
Punto::Punto(float xx, float yy, float zz, float ww) {
	x=xx; y=yy; z=zz; w=ww; esUnitario=0;
	r=1.0; g=0.0; b=0.0; esVisible=true; forma=4;
}

//Suma de dos vectores 
Punto Punto::operator +(Punto p) {
	return Punto(x+p.x, y+p.y, z+p.z);
};

//Diferencia de dos vectores
Punto Punto::operator -(Punto p) {
	Punto suma;
	
	suma.x=x-p.x; suma.y=y-p.y; suma.z=z-p.z;
	return suma;
};

//Producto por un escalar POR LA DERECHA
Punto Punto::operator *(float k) {
	return Punto(x*k,y*k,z*k);
};

//Division de cada componente por un entero
Punto Punto::operator /(int divisor) {
	return Punto(x/divisor,y/divisor,z/divisor);
};

//Division de cada componente por un real
Punto Punto::operator /(float divisor) {
	return Punto(x/divisor,y/divisor,z/divisor);
};

//Tratamiento como vector por sobrecarga del operador []
float Punto::operator [](int i) {
	switch(i) {
		case 0:
			return(x);
			break;
		case 1:
			return(y);
			break;
		case 2:
			return(z);
			break;
		case 3:
			return(w);
			break;
		default:
			cerr<<"Indice de coordenada fuera de rango"<<endl;;
	};
	exit(1);
	return 0.0f;
};

//Producto por una matriz POR LA DERECHA (P*M)
Punto Punto::operator *(Matriz m) {

	return Punto( 
		x*m.e[0][0]+y*m.e[1][0]+z*m.e[2][0]+w*m.e[3][0],
		x*m.e[0][1]+y*m.e[1][1]+z*m.e[2][1]+w*m.e[3][1],
		x*m.e[0][2]+y*m.e[1][2]+z*m.e[2][2]+w*m.e[3][2],
		x*m.e[0][3]+y*m.e[1][3]+z*m.e[2][3]+w*m.e[3][3]);
};

//Transforma considerando el punto como vector columna
//es decir, aplica la transformacion por la izquierda
Punto Punto::transformar(Transformacion &t) {
	return (t*(*this));
};

//Devuelve un nuevo vector con el signo cambiado
Punto Punto::negado() {
	return Punto(-x,-y,-z,w);
};

//Devuelve el modulo del vector
float Punto::modulo() {
	return ((float)sqrt((double)cuadrado(x)+cuadrado(y)+cuadrado(z)));
};

//Normaliza el vector receptor y se devuelve a si mismo
Punto Punto::normalizar() {
	float m;
	if(!esUnitario) {
		m=modulo();
		x=x/m;y=y/m;z=z/m;
		esUnitario=1;
	};
	return *this;
};

//Devuelve el vector unitario en esa direccion
Punto Punto::unitario() {
	if(esUnitario) 
		return *this;
	else 
		return Punto(x,y,z).normalizar();
};

//Calcula la longitud (0..360º) esferica del vector en grados
float Punto::longitud() {
	float lon;
	lon= (float)acos(z/sqrt(x*x+z*z));		
	if(x<0) lon= 2*PI-lon;
	return lon*180/PI;
};

//Calcula la latitud (-90º..90º) esférica del vector en grados
float Punto::latitud() {
	float lat;
	lat= (float)acos(sqrt(x*x+z*z)/modulo());		
	if(y<0) lat= -lat;
	return lat*180/PI;
};

//Calcula el producto escalar
float Punto::operator *(Punto p) {
	return (x*p.x+y*p.y+z*p.z);
};

//Calcula el producto vectorial
Punto Punto::operator ^(Punto p) {
	return Punto( y*p.z-z*p.y, z*p.x-x*p.z, x*p.y-y*p.x );
};

//Devuelve un punto con la w=1
Punto Punto::homogeneo() {
	if( w == 1.0 ) 
		return *this;
	else 
		return Punto(x/w,y/w,z/w,1.0f);
};

//Escribe las coordenadas del punto en la consola
void Punto::escribir() {
	printf("x: %6.6f, y:%6.6f, z:%6.6f, w:%6.6f\n",x,y,z,w);
};



// Situa el punto en xx, yy, zz
void Punto::pos(float xx, float yy, float zz, float ww) {
	x = xx; y = yy; z = zz; w = ww;
}

// Cambia la forma del punto
void Punto::setforma(int forma) {
	this->forma = forma;
}

// Cambia el color del punto
void Punto::color(float r, float g, float b) {
	this->r = r; this->g = g; this->b = b;
}

// Cambia de visible a invisible
void Punto::setvisible(int estado) {
	esVisible = estado;
}

// Devuelve si es visible o no
int Punto::visible() {
	return esVisible;
}

// Dibujar un rayo por pantalla
void Punto::dibujar(Punto desde) {
	int i;
	float alfa = 0, inc;

	glColor3f(1,1,1);
	glBegin(GL_LINES);
	glVertex3f(x,y+0.04,z);
	glVertex3f(x,y-0.04,z);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(x+0.04,y,z);
	glVertex3f(x-0.04,y,z);
	glEnd();
	
	glColor3f(1,1,1);
	glBegin(GL_LINES);
	glVertex3f(desde.x,desde.y+0.04,desde.z);
	glVertex3f(desde.x,desde.y-0.04,desde.z);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(desde.x+0.04,desde.y,desde.z);
	glVertex3f(desde.x-0.04,desde.y,desde.z);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(this->x,this->y,this->z);
	glVertex3f(desde.x,desde.y,desde.z);
	glEnd();
}


// Dibujar el punto por pantalla
void Punto::dibujar() {
	int i;
	float alfa = 0, inc;
										
	if(this->esVisible) {
		switch(this->forma) {
			case 1: // "x"
				glColor3f(this->r,this->g,this->b);
				glBegin(GL_LINES);
					glVertex3f(x+0.04, y+0.04,z+0.04);
					glVertex3f(x-0.04, y-0.04,z-0.04);
				glEnd();
				glBegin(GL_LINES);
					glVertex3f(x+0.04, y-0.04,z-0.04);
					glVertex3f(x-0.04, y+0.04,z+0.04);
				glEnd();
				break;

			case 2: // "o"
				glColor3f(this->r, this->g, this->b);
				inc = (2*PI)/30;
				glBegin(GL_LINE_STRIP);
					for(i=0;i<30;i++) {
						glVertex3f(cos(alfa)*0.03 + x, sin(alfa)*0.03 + y,z);
						alfa += inc;
					}
				glEnd();
				break;

			case 3: // "+"
				glColor3f(this->r, this->g, this->b);
				glBegin(GL_LINES);
					glVertex3f(x,y+0.04,z);
					glVertex3f(x,y-0.04,z);
				glEnd();
				glBegin(GL_LINES);
					glVertex3f(x+0.04,y,z);
					glVertex3f(x-0.04,y,z);
				glEnd();
				break;

			case 4: // "·"
				glColor3f(this->r, this->g, this->b);
				glPointSize(4.0);
				glBegin(GL_POINTS);
					glVertex3f(x, y, z);
				glEnd();
				glPointSize(1.0);
				break;
				
			default:
				printf("\nole\n");
				glColor3f(this->r,this->g,this->b);
				glBegin(GL_LINES);
					glVertex3f(x+0.04, y+0.04,z+0.04);
					glVertex3f(x-0.04, y-0.04,z-0.04);
				glEnd();
				glBegin(GL_LINES);
					glVertex3f(x+0.04, y-0.04,z-0.04);
					glVertex3f(x-0.04, y+0.04,z+0.04);
				glEnd();
			break;
		}
	}
}


//Clase Matriz -------------------------------------------
//--------------------------------------------------------


//Construye la identidad por defecto
Matriz::Matriz() {

	int i,j;
	for(i=0;i<4;i++) {
		for(j=0;j<4;j++){
			if(j==i) 
				e[i][j]=1.0f;
			else 
				e[i][j]=0.0f;
		};
	};
};

//Construye la matriz por columnas
Matriz::Matriz(Punto e1,Punto e2,Punto e3,Punto e4) {
	int i;
	for(i=0;i<4;i++){
		e[i][0]=e1[i];
		e[i][1]=e2[i];
		e[i][2]=e3[i];
		e[i][3]=e4[i];
	};
};

//Devuelve un punto formado por la fila i (0..3)
Punto Matriz::fila(int i) {
	if(i<4 && i>=0) 
		return Punto(e[i][0],e[i][1],e[i][2],e[i][3]);
	else {		
		cerr << "Indice de fila fuera de rango\n";
		exit(1);
	};
	return Punto();
};

//Devuelve un punto con la columna i (0..3)
Punto Matriz::columna(int i) {
	if(i<4 && i>=0) 
		return Punto(e[0][i],e[1][i],e[2][i],e[3][i]);
	else {		
		cerr << "Indice de columna fuera de rango\n";
		exit(1);
	};
	return Punto();
};


//Asignacion de matrices
Matriz Matriz::operator =(const Matriz &m) {
	int i,j;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++) 
			e[i][j]=m.e[i][j];
	return *this;
};

//Producto de matrices. Devuelve una nueva matriz
Matriz Matriz::operator *(Matriz m) {
	int i,j,k;
	Matriz pr; //Identidad por defecto

	pr.e[0][0]=pr.e[1][1]=pr.e[2][2]=pr.e[3][3]=0.0f;

	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			for(k=0;k<4;k++)
				pr.e[i][j]=pr.e[i][j]+e[i][k]*m.e[k][j];
	return pr;
};

//Producto por un vector POR LA DERECHA (M*P)
Punto Matriz::operator *(Punto p) {
	int j;
	Punto pr=Punto(0,0,0,0);
	
	for(j=0;j<4;j++){
		  pr.x= pr.x+e[0][j]*p[j];
		  pr.y= pr.y+e[1][j]*p[j];
		  pr.z= pr.z+e[2][j]*p[j];
		  pr.w= pr.w+e[3][j]*p[j];
	};
	return pr;
};

//Multiplica por capas (k cte.) y devuelve una matriz3d
Matriz3d Matriz::operator *(const Matriz3d &m3d) {
	int i,j,k,n;
	Matriz3d mr;	//Por defecto toda a ceros

	for(k=0;k<4;k++) //fija la capa
		for(i=0;i<4;i++)
			for(j=0;j<4;j++)
				for(n=0;n<4;n++)
					mr.e[i][j][k]= mr.e[i][j][k] + e[i][n]*m3d.e[n][j][k];
	return mr;
};


//Producto por un escalar (M*k). Devuelve una nueva matriz
Matriz Matriz::operator *(float k) {
	int i,j;
	Matriz pr;

	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			pr.e[i][j]=e[i][j]*k;

	return pr;
};

//Devuelve la traspuesta en una nueva matriz. 
//Usar parentesis para asegurar precedencia (!M)
Matriz Matriz::operator !() {
	int i,j;
	Matriz t;

	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			t.e[j][i]=e[i][j];

	return t;
};



//Escribe la matriz por filas en la salida estandar
void Matriz::escribir() {
	int i,j;

	for(i=0;i<4;i++){
		printf("\n");
		for(j=0;j<4;j++)
			printf("%6.2f ",e[i][j]);
	};
	printf("\n");
};

//Modifica la matriz con los siguientes puntos, escritos por FILAS
Matriz Matriz::modifica(Punto e1,Punto e2,Punto e3,Punto e4) {
	int i;
	Matriz t;
	for(i=0;i<4;i++){
		t.e[0][i]=e1[i];
		t.e[1][i]=e2[i];
		t.e[2][i]=e3[i];
		t.e[3][i]=e4[i];
	};
	return t;
};
//Clase Transformacion (subclase de Matriz) -------------------------
//-------------------------------------------------------------------

//Acumula la traslacion propuesta
void Transformacion::traslacion(Punto d) {
	Matriz t;
	int i;

	for (i=0;i<3;i++) 
		t.e[i][3]=d[i];
	Matriz::operator=((*this)*t);

};

//Acumula el escalado sobre un punto generico
void Transformacion::escalado(float sx,float sy,float sz, Punto centro) {
	Matriz s;

	traslacion(centro);
	s.e[0][0]=sx; s.e[1][1]=sy; s.e[2][2]=sz;
	Matriz::operator=((*this)*s);
	traslacion(centro.negado());
};


//Acumula el giro alrededor de un eje generico
void Transformacion::giro(float ang, Punto vectorEje, Punto enRecta ) {
	float lat,lon;

	lat = vectorEje.latitud();		//latitud
	lon = vectorEje.longitud();		//longitud

	//Recordar acumulacion LIFO
	traslacion(enRecta);	//Rehacer la traslacion
	giroY(lon);		//Rehacer la longitud
	giroX(-lat);		//Rehacer la latitud
	giroZ(ang);		//Girar el angulo
	giroX(lat);		//Deshacer la latitud
	giroY(-lon);		//Deshacer la longitud
	traslacion(enRecta.negado());	//Traslacion al origen

};

//Acumula el giro por cambio de base
void Transformacion::giro(Punto u, Punto v, Punto w) {
	Matriz g = !Matriz(u,v,w);  //Por filas (traspuesta)

	//Ultima columna debe ser (0,0,0,1)
	g.e[0][3]=g.e[1][3]=g.e[2][3]=0.0f;

	Matriz::operator=((*this)*g);
};


//Acumulacion de giros específicos
//en X
void Transformacion::giroX(float ang) {
	
	Matriz g;
	g.e[1][1]=(float)cos((double)ang/180*PI);
	g.e[1][2]=(float)sin((double)(-ang/180*PI));
	g.e[2][1]= -g.e[1][2];        
	g.e[2][2]=g.e[1][1];

	Matriz::operator=((*this)*g);
};

//en Y
void Transformacion::giroY(float ang) {
	Matriz g;
	g.e[0][0]=(float)cos((double)ang/180*PI);
    	g.e[0][2]=(float)sin((double)ang/180*PI);
	g.e[2][0]= -g.e[0][2];        
	g.e[2][2]=g.e[0][0];

	Matriz::operator=((*this)*g);
};

//en Z
void Transformacion::giroZ(float ang) {
	Matriz g;
	g.e[0][0]=(float)cos((double)ang/180*PI);
	g.e[0][1]=(float)sin((double)(-ang/180*PI));
	g.e[1][0]= -g.e[0][1];
	g.e[0][0]=g.e[1][1];

	Matriz::operator=((*this)*g);
};

// Clase Matriz3d -------------------------------------------
//-----------------------------------------------------------

//Constructor por defecto. Matriz toda a 0.0
Matriz3d::Matriz3d() {
	int i,j,k;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			for(k=0;k<4;k++) 
				e[i][j][k]=0.0f;
};

//Contruye la matriz3d con las matrices como columnas
Matriz3d::Matriz3d(Matriz c1, Matriz c2, Matriz c3, Matriz c4) {
	int i,k;

	for(i=0;i<4;i++) {
		for(k=0;k<4;k++){
			e[i][0][k]=c1.e[k][i];
			e[i][1][k]=c2.e[k][i];
			e[i][2][k]=c3.e[k][i];
			e[i][3][k]=c4.e[k][i];
		};
	};
};

//Asignacion de matrices 3d
Matriz3d Matriz3d::operator =(const Matriz3d &m) {
	int i,j,k;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			for(k=0;k<4;k++) e[i][j][k]=m.e[i][j][k];
	return *this;
};

//Multiplica por capas y devuelve la nueva matriz 3d
Matriz3d Matriz3d::operator *(const Matriz &m) {
	int i,j,k,n;
	Matriz3d mr;	//Por defecto toda a ceros

	for(k=0;k<4;k++) //fija la capa
		for(i=0;i<4;i++)
			for(j=0;j<4;j++)
				for(n=0;n<4;n++)
					mr.e[i][j][k]= mr.e[i][j][k] + e[i][n][k]*m.e[n][j];
	return mr;

};

//Devuelve el punto para esa fila,columna 
Punto Matriz3d::fiCo(int i, int j) {
	return Punto(e[i][j][0], e[i][j][1],e[i][j][2],e[i][j][3]);
};

//escribe la matriz por la salida estandar por columnas
void Matriz3d::escribir() {
	int i,j,k;

	for(j=0;j<4;j++){
		printf("\n");
		for(i=0;i<4;i++){
			printf("\n");
			for(k=0;k<4;k++) 
				printf("%6.2f ",e[i][j][k]);
		};
	};
};

//Mete un punto en la posicion i,j
Matriz3d Matriz3d::ponerEn(int i, int j, Punto p) {
	int k;
	for(k=0;k<4;k++)
		e[i][j][k]=p[k];
	return *this;
};


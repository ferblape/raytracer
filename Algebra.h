#ifndef _CALGEBRA
#define _CALGEBRA

//Clases basicas de geometria y algebra

class Punto;
class Matriz;
class Transformacion;
class Matriz3d;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Actua indistintamente como punto o vector almacenado 4 coordenadas o componentes
class Punto {
public:
	float x,y,z,w;			//Coordenadas homogeneas

	Punto(float xx=0.0, float yy=0.0, float zz=0.0, float ww=1.0); 
	Punto operator +(Punto p);	//Suma de puntos
	Punto operator -(Punto p);	//Resta de puntos
	Punto operator *(float k);	//Producto por un escalar
	Punto operator /(int divisor);	//Division por un escalar
	Punto operator /(float divisor);	//Division por un escalar
	float operator [](int i);	//Considerado como vector
	Punto operator *(Matriz m);	//Producto por una matriz
	float operator *(Punto p);	//Calcula el producto escalar
	Punto operator ^(Punto p);	//Calcula el producto vectorial
	Punto transformar(Transformacion &t);	//Transformacion de un punto
	Punto negado();		//Punto con el signo cambiado
	Punto normalizar();	//Normaliza el punto y se devuelve asi mismo
	Punto unitario();	//Vector unitario en esa direccion
	float modulo();		//Calcula el modulo del vector
	float longitud();	//Calcula la longitud esferica del vector
	float latitud();	//Calcula la latitud esferica del vector
	void escribir();	//Escribe el punto
	Punto homogeneo();	//Devuelve un punto con la w=1

	void pos(float xx, float yy, float zz, float ww);	// Situa el punto en xx, yy, zz
	void setforma(int forma);	// Cambia la forma del punto
	void color(float r, float g, float b);	// Cambia el color del punto
	void setvisible(int estado);		// Cambia de visible a invisible
	int visible();	// Devuelve si es visible o no
	void dibujar();	// Dibujar el punto por pantalla
	void dibujar(Punto desde);	// Dibujar el rayo que va desde el punto hasta desde

private:
	int esUnitario;	  	//esta normalizado
	float r,g,b;		// Colores
	int esVisible;		// Visible o no
	int forma;			// Forma del punto 
};
 
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Matriz de 4x4 coordenadas o Matriz vector de 4 puntos
class Matriz {
public:
	float e[4][4];

	Matriz();	//Construye la identidad por defecto
	//Construye la matriz por columnas
	Matriz(Punto e1,Punto e2, Punto e3,Punto e4=Punto());
	Punto fila(int i);	//Devuelve un punto con la fila i(0..3)
	Punto columna(int i);	//Devuelve un punto con la columna i(0..3)
	Matriz operator =(const Matriz &);	//Asignacion de matrices
	Matriz operator *(Matriz m);	//Producto de matrices
	Punto operator *(Punto p);	//Producto por un vector
	Matriz3d operator *(const Matriz3d &);//Producto por capas con una matriz 3d
	Matriz operator *(float k);	//Producto por un escalar
	Matriz operator !();		//Traspone filas y columnas
	void escribir();	//Escribe la matriz
	//Modifica la matriz con los siguientes puntos, escritos por FILAS
	Matriz modifica(Punto e1, Punto e2, Punto e3, Punto e4 = Punto()); 
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Matriz de transformación derivada de matriz que acumula transformaciones 3D
class Transformacion: public Matriz {
public:

	//La acumulacion es LIFO sobre el punto pensando en coordenadas fijas
	//y se debe aplicar por la izquierda del punto en columna (idem GL)
	//Ej: P' = M1*M2*M3*P  (M3 fue la ultima en acumularse y la primera en aplicarse)

	//Acumula el giro por cambio de base
	void giro(Punto u, Punto v, Punto w);

	//Acumula la traslacion propuesta
	void traslacion(Punto d);

	//Acumula el escalado
	void escalado(float sx=1.0,float sy=1.0,float sz=1.0, Punto centro=Punto());

	//Acumula el giro (ang en grados)
	void giro(float ang, Punto vectorEje, Punto enRecta=Punto() );

	//Acumulacion de giros específicos (ang en grados)
	void giroX(float ang);
	void giroY(float ang);
	void giroZ(float ang);
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Matriz cubica de 4x4x4 (filas X columnas X capas)
class Matriz3d: public Matriz {
public:
	float e[4][4][4];

	Matriz3d();
	//Constructor por columnas
	Matriz3d(Matriz , Matriz , Matriz , Matriz );

	Punto fiCo(int i,int j);		//Devuelve el punto en fila i, columna j
	Matriz3d ponerEn(int i, int j, Punto p);//Mete el punto en la posicion i,j
	Matriz3d operator =(const Matriz3d &);  //Asignación de matrices 3d
	Matriz3d operator *(const Matriz &);	//Producto por capas con una matriz
	void escribir();
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


#endif

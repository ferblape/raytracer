#ifndef DEF_H
#define DEF_H

typedef struct tPunto {
	float x;
	float y;
	float z;
} tPunto;

typedef struct tColor {
	float r;
	float g;
	float b;
	float ks;
	float kd;
} tColor;

typedef struct tChecker {
	tColor color1;
	tColor color2;
	float ancho;
} tChecker;

#endif

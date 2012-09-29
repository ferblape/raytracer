#include "RGB.h"
#include <iostream>
#include <stdio.h>

using namespace std;

RGB::RGB() { r = 0; g = 0; b = 0;}

RGB::RGB(float r, float g, float b) {
	this->r = r;
	this->g = g;
	this->b = b;
}


RGB RGB::operator *(RGB rgb) {
	return RGB(r*rgb.r, g*rgb.g, b*rgb.b);
}

RGB RGB::operator *(float f) {
	return RGB(r*f, g*f, b*f);
}
RGB RGB::operator +(RGB rgb) {
	RGB nuevo = RGB(r+rgb.r, g+rgb.g, b+rgb.b);
	if (nuevo.r > 1)
		nuevo.r = 1;
	if (nuevo.g > 1)
		nuevo.g = 1;
	if (nuevo.b > 1)
		nuevo.b = 1;
	return nuevo;
}

void RGB::set(float nr, float ng, float nb) {
	r = nr; g = ng; b = nb;
}

void RGB::escribir() {
	cerr << "r: " << r << " - g: " << g << " - b: " << b<<endl;
}

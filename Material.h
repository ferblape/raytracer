#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "RGB.h"

class Material {
	public:
		RGB color;
		float kd;
		float ks;

		Material(RGB col, float kd_, float ks_);
		Material();
};
#endif

#include "Material.h"

Material::Material(RGB col, float kd_, float ks_) {
	color = col;
	kd = kd_;
	ks = ks_;
}

Material::Material() {};

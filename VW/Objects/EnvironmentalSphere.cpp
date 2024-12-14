#include "EnvironmentalSphere.hh"

EnvironmentalSphere::EnvironmentalSphere():Sphere() {
    switchOrientation();
}

EnvironmentalSphere::EnvironmentalSphere(vec3 cen, float r):Sphere(cen,r) {
    switchOrientation();
}

vec2 EnvironmentalSphere::project(vec3 p) const {
    vec2 uv = Sphere::project(p);
    return vec2(1 - uv[0], uv[1]);
}

void EnvironmentalSphere::read(const QJsonObject &json)
{
    Sphere::read(json);
    switchOrientation();
}
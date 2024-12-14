#include "Plane.hh"

#include <iostream>

Plane::Plane(vec3 normal, vec3 pass_point) : Object(){
    this->normal = normalize(normal);
    this->v1 = pass_point;
    computeD();
}

Plane::Plane(vec3 normal, float d) : Object() {
    normal  = normalize(normal);
    this->normal = normal;
    this->D = d;
    if (abs(normal.z)>DBL_EPSILON)
        this->v1 = vec3(0.0, 0.0, -d/normal.z);
    else if (abs(normal.y)>DBL_EPSILON)
        this->v1 = vec3(0.0, -d/normal.y, 0.0);
    else
        this->v1 = vec3(-d/normal.x, 0.0, 0.0);
};

Plane::Plane(vec3 normal, vec3 pass_point, float d, shared_ptr<Material> m) : Object(){
    // En aquest constructor normal esta normalitzat
    this->normal = normal;
    this->v1 = pass_point;
    this->D = d;
    setMaterial(m);
}

void Plane::computeD() {
    // Assumim que els altres atributs estan omplerts
    this->D = -dot(this->normal, this->v1);
}

bool Plane::isNormal(vec3 normal) const {
    return abs(1 - dot(this->normal, normal)) < DBL_EPSILON;
}
bool Plane::isD(float d) const {
    return abs(D - d) < DBL_EPSILON;
}

vec3 Plane::getNormal() const {
    return normal;
}

bool Plane::isIntersection(float *t, vec3 origin, vec3 direction, float tmin, float tmax) const {
    // Raig paral·lel al pla
    float dot_prod = dot(direction, normal);
    if (abs(dot_prod) < DBL_EPSILON) {
        return false;
    }

    // t de la interseccio i comprovacio (tmin,tmax)
    float temp = -((dot(normal,origin) + D) / dot_prod);
    if (temp > tmax || temp < tmin) {
        return false;
    }

    *t = temp;
    return true;
}

bool Plane::hit(Ray &raig, float tmin, float tmax) const{
    // Interseccio amb el pla del triangle?
    float t;
    if (!isIntersection(&t, raig.getOrigin(), raig.getDirection(), tmin, tmax)) {
        return false;
    }

    // Omplim el camp de info:
    shared_ptr<HitRecord> info = make_shared<HitRecord>();
    info->t = t;
    info->p = raig.pointAt(t);

    // La normal a un pla es la mateixa per tots els punts
    info->normal = normal;
    info->mat = material;
    raig.addHit(info);
    return true;
}

bool Plane::allHits(Ray& r, float tmin, float tmax) const {
    // Interseccio amb el pla del triangle?
    float t;
    if (!isIntersection(&t, r.getOrigin(), r.getDirection(), tmin, tmax)) {
        return false;
    }

    // Omplim el camp de info:
    shared_ptr<HitRecord> info = make_shared<HitRecord>();
    info->t = t;
    info->p = r.pointAt(t);

    // La normal a un pla es la mateixa per tots els punts
    info->normal = normal;
    info->mat = material;
    r.insertHit(info);
    return true;
}

void Plane::update(int frame) {
    // TO DO: Cal ampliar-lo per a fer el update del pla
}

void Plane::aplicaTG(shared_ptr<TG> t) {
    if (dynamic_pointer_cast<shared_ptr<TranslateTG>>(t)) {

        // Nomes movem el punt de pas
        vec4 newp(this->v1, 1.0);
        newp = t->getTG() * newp;
        this->v1.x = newp.x;
        this->v1.y = newp.y;
        this->v1.z = newp.z;
    }
}

void Plane::read (const QJsonObject &json)
{
    Object::read(json);

    if (json.contains("point") && json["point"].isArray()) {
        QJsonArray auxVec = json["point"].toArray();
        v1[0] = auxVec[0].toDouble();
        v1[1] = auxVec[1].toDouble();
        v1[2] = auxVec[2].toDouble();
    }
    if (json.contains("normal") && json["normal"].isArray()) {
        QJsonArray auxVec = json["normal"].toArray();
        normal[0] = auxVec[0].toDouble();
        normal[1] = auxVec[1].toDouble();
        normal[2] = auxVec[2].toDouble();
    }

    computeD();
}


//! [1]
void Plane::write(QJsonObject &json) const
{
    Object::write(json);

    QJsonArray auxArray;
    auxArray.append(normal[0]);auxArray.append(normal[1]);auxArray.append(normal[2]);
    json["normal"] = auxArray;

    QJsonArray auxArray2;
    auxArray2.append(v1[0]);auxArray2.append(v1[1]);auxArray2.append(v1[2]);
    json["point"] = auxArray2;
}
//! [1]

void Plane::print(int indentation) const
{
    Object::print(indentation);
    const QString indent(indentation * 2, ' ');

    QTextStream(stdout) << indent << "point:\t" << v1[0] << ", "<< v1[1] << ", "<< v1[2] << "\n";
    QTextStream(stdout) << indent << "normal:\t" << normal[0] << ", "<< normal[1] << ", "<< normal[2] << "\n";
    QTextStream(stdout) << indent << "D:\t" << D << "\n";

}

#include "Triangle.hh"

Triangle::Triangle():Plane() {
    // Triangle per defecte (normal: (0,-1,0))
    Triangle(vec3(0.0,0.0,0.0),vec3(1.0,0.0,0.0),vec3(0.0,0.0,1.0));
}

Triangle::Triangle(const vec3 &v1, const vec3 &v2, const vec3 &v3):Plane()  {
    // Sentit antihorari
    this->v1 = v1;
    this->v2 = v2;
    this->v3 = v3;

    normal = (normalize(cross(v2-v1, v3-v1)));
    computeD();
}

bool Triangle::hit(Ray &raig, float tmin, float tmax) const {
    // Interseccio amb el pla del triangle?
    float t;
    if (!isIntersection(&t, raig.getOrigin(), raig.getDirection(), tmin, tmax)) {
        return false;
    }

    // Comprovacio interseccio dins el triangle (recorregut antihorari)
    vec3 P = raig.pointAt(t);

    // P a la dreta de l'aresta v1v2
    if (dot(normal, cross(v2 - v1, P - v1)) < 0) {
        return false;
    }

    // P a la dreta de l'aresta v2v3
    if (dot(normal, cross(v3 - v2, P - v2)) < 0) {
        return false;
    }

    // P a la dreta de l'aresta v3v1
    if (dot(normal, cross(v1 - v3, P - v3)) < 0) {
        return false;
    }

    // Interior del triangle, registrem el hit
    shared_ptr<HitRecord> info = make_shared<HitRecord>();
    info->t = t;
    info->p = P;

    // La normal a un triangle es la mateixa per tots els punts
    info->normal = normal;
    info->mat = material;
    raig.addHit(info);
    return true;
}

// Mateixa estrategia que hit(), usant raig.insertHit()
bool Triangle::allHits(Ray& raig, float tmin, float tmax) const {
    // Interseccio amb el pla del triangle?
    float t;
    if (!isIntersection(&t, raig.getOrigin(), raig.getDirection(), tmin, tmax)) {
        return false;
    }

    // Comprovacio interseccio dins el triangle (recorregut antihorari)
    vec3 P = raig.pointAt(t);

    // P a la dreta de l'aresta v1v2
    if (dot(normal, cross(v2 - v1, P - v1)) < 0) {
        return false;
    }

    // P a la dreta de l'aresta v2v3
    if (dot(normal, cross(v3 - v2, P - v2)) < 0) {
        return false;
    }

    // P a la dreta de l'aresta v3v1
    if (dot(normal, cross(v1 - v3, P - v3)) < 0) {
        return false;
    }

    // Interior del triangle, registrem el hit
    shared_ptr<HitRecord> info = make_shared<HitRecord>();
    info->t = t;
    info->p = P;

    // La normal a un triangle es la mateixa per tots els punts
    info->normal = normal;
    info->mat = material;
    raig.insertHit(info);
    return true;
}

void Triangle::update(int frame) {
}

void Triangle::aplicaTG(shared_ptr<TG> t) {

}

void Triangle::read (const QJsonObject &json)
{
    Object::read(json);

    if (json.contains("v1") && json["v1"].isArray()) {
        QJsonArray auxVec = json["v1"].toArray();
        v1[0] = auxVec[0].toDouble();
        v1[1] = auxVec[1].toDouble();
        v1[2] = auxVec[2].toDouble();
    }
    if (json.contains("v2") && json["v2"].isArray()) {
        QJsonArray auxVec = json["v2"].toArray();
        v2[0] = auxVec[0].toDouble();
        v2[1] = auxVec[1].toDouble();
        v2[2] = auxVec[2].toDouble();
    }
    if (json.contains("v3") && json["v3"].isArray()) {
        QJsonArray auxVec = json["v3"].toArray();
        v3[0] = auxVec[0].toDouble();
        v3[1] = auxVec[1].toDouble();
        v3[2] = auxVec[2].toDouble();
    }

    normal = (normalize(cross(v2-v1, v3-v1)));
    computeD();

}


//! [1]
void Triangle::write(QJsonObject &json) const
{
    Object::write(json);

    QJsonArray auxArray;
    auxArray.append(v1[0]);
    auxArray.append(v1[1]);
    auxArray.append(v1[2]);
    json["v1"] = auxArray;

    auxArray = QJsonArray();
    auxArray.append(v2[0]);
    auxArray.append(v2[1]);
    auxArray.append(v2[2]);
    json["v2"] = auxArray;

    auxArray = QJsonArray();
    auxArray.append(v3[0]);
    auxArray.append(v3[1]);
    auxArray.append(v3[2]);
    json["v3"] = auxArray;

}
//! [1]

void Triangle::print(int indentation) const
{
    Object::print(indentation);

    const QString indent(indentation * 2, ' ');

    QTextStream(stdout) << indent << "vertice 1:\t" << v1[0] << ", "<< v1[1] << ", "<< v1[2] << "\n";
    QTextStream(stdout) << indent << "vertice 2:\t" << v2[0] << ", "<< v2[1] << ", "<< v2[2] << "\n";
    QTextStream(stdout) << indent << "vertice 3:\t" << v3[0] << ", "<< v3[1] << ", "<< v3[2] << "\n";
}


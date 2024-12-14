#include "AreaLight.hh"
#include <glm/gtc/random.hpp>

AreaLight::AreaLight(vec3 posicio, vec3 Ia, vec3 Id, vec3 Is, float a, float b, float c, float radius) : Light(Ia, Id, Is)
{
    this->pos = posicio;
    this->a = a;
    this->b = b;
    this->c = c;
    this->radius = radius;
}

vec3 AreaLight::getPos()
{
    return this->pos;
}

vec3 AreaLight::vectorL(vec3 point)
{
    return normalize(pos - point);
}

float AreaLight::attenuation(vec3 point)
{
    if (abs(a) < DBL_EPSILON && abs(b) < DBL_EPSILON && abs(c) < DBL_EPSILON)
    {
        // Si tots els coeficients son 0 considerem que no hi ha atenuacio
        return 1.0f;
    }
    // Calculem la distancia entre el punt i la posicio de la llum
    float d = distance(point, pos);
    return 1.0f / (c * d * d + b * d + a);
}

float AreaLight::distanceToLight(vec3 point)
{
    return distance(point, pos);
}

vec3 AreaLight::getRandomPointOnLight()
{
    // Generem un punt aleatori en una esfera centrada en el 0 i el traslladem a la posicio del llum.
    vec3 randomPoint = glm::ballRand(radius);
    return this->pos + randomPoint;
}

void AreaLight::read(const QJsonObject &json)
{
    Light::read(json);

    if (json.contains("position") && json["position"].isArray())
    {
        QJsonArray auxVec = json["position"].toArray();
        pos[0] = auxVec[0].toDouble();
        pos[1] = auxVec[1].toDouble();
        pos[2] = auxVec[2].toDouble();
    }
    if (json.contains("a") && json["a"].isDouble())
        a = json["a"].toDouble();
    if (json.contains("b") && json["b"].isDouble())
        b = json["b"].toDouble();
    if (json.contains("c") && json["c"].isDouble())
        c = json["c"].toDouble();

    if (json.contains("radius") && json["radius"].isDouble())
        radius = json["radius"].toDouble();
}

//! [1]
void AreaLight::write(QJsonObject &json) const
{
    Light::write(json);
    QJsonArray auxArray;
    auxArray.append(pos[0]);
    auxArray.append(pos[1]);
    auxArray.append(pos[2]);
    json["position"] = auxArray;

    json["a"] = a;
    json["b"] = b;
    json["c"] = c;

    json["radius"] = radius;
}
//! [1]

void AreaLight::print(int indentation) const
{
    const QString indent(indentation * 2, ' ');

    QTextStream(stdout) << "Area Light"
                        << "\n";
    QTextStream(stdout) << indent + 2 << "position:\t" << pos[0] << ", " << pos[1] << ", " << pos[2] << "\n";
    QTextStream(stdout) << indent + 2 << "a:\t" << a << "\n";
    QTextStream(stdout) << indent + 2 << "b:\t" << b << "\n";
    QTextStream(stdout) << indent + 2 << "c:\t" << c << "\n";
    QTextStream(stdout) << indent + 2 << "Radius:\t" << radius << "\n";
}

#include "Sphere.hh"

Sphere::Sphere()
{
    center = vec3(0.0, 0.0, 0.0);
    radius = 1.0;
}

Sphere::Sphere(vec3 cen, float r)
{
    center = cen;
    radius = r;
}

vec2 Sphere::project(vec3 p) const {
    // Vector del punt al centre de l'esfera (normalitzat)
    vec3 norm = (p - center) / abs(radius);

    // Coordenades (u,v) en el cas de la S²
    auto theta = asin(norm[1]);
    auto phi = atan2(-norm[2], norm[0]);
    return vec2(phi/(2*PI) + 0.5, (theta / PI) + 0.5);
}

bool Sphere::hit(Ray &raig, float tmin, float tmax) const {
    shared_ptr<HitRecord> hit = make_shared<HitRecord>();

    vec3 oc = raig.getOrigin() - center;
    float a = dot(raig.getDirection(), raig.getDirection());
    float b = dot(oc, raig.getDirection());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - a * c;
    if (discriminant > 0)
    {
        float temp = (-b - sqrt(discriminant)) / a;
        if (temp < tmax && temp > tmin)
        {
            hit->t = temp;
            vec3 p = raig.pointAt(hit->t);
            hit->p = p;
            hit->uv = project(p);
            hit->normal = (hit->p - center) / radius;
            hit->mat = material;
            raig.addHit(hit);
            return true;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < tmax && temp > tmin)
        {
            hit->t = temp;
            vec3 p = raig.pointAt(hit->t);
            hit->p = p;
            hit->uv = project(p);
            hit->normal = (hit->p - center) / radius;
            hit->mat = material;
            raig.addHit(hit);
            return true;
        }
    }
    return false;
}

bool Sphere::allHits(Ray &raig, float tmin, float tmax) const
{
    bool trobat = false;
    vec3 oc = raig.getOrigin() - center;
    float a = dot(raig.getDirection(), raig.getDirection());
    float b = dot(oc, raig.getDirection());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - a * c;
    if (discriminant > 0)
    {
        float temp = (-b - sqrt(discriminant)) / a;
        if (temp < tmax && temp > tmin)
        {
            shared_ptr<HitRecord> info = make_shared<HitRecord>();
            info->t = temp;
            vec3 p = raig.pointAt(info->t);
            info->p = p;
            info->uv = project(p);
            info->normal = (info->p - center) / radius;
            info->mat = material;
            raig.insertHit(info);
            trobat = true;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < tmax && temp > tmin)
        {
            shared_ptr<HitRecord> info = make_shared<HitRecord>();
            info->t = temp;
            vec3 p = raig.pointAt(info->t);
            info->p = p;
            info->uv = project(p);
            info->normal = (info->p - center) / radius;
            info->mat = material;
            raig.insertHit(info);
            trobat = true;
        }
    }
    return trobat;
}

void Sphere::update(int frame)
{
    // TO DO: Cal ampliar-lo per a fer el update de l'esfera
    Animable::update(frame);
}

void Sphere::aplicaTG(shared_ptr<TG> t)
{
    if (dynamic_pointer_cast<TranslateTG>(t))
    {
        vec4 c(center, 1.0);
        c = t->getTG() * c;
        center.x = c.x;
        center.y = c.y;
        center.z = c.z;
    }
    else if (dynamic_pointer_cast<ScaleTG>(t))
    {
        // Com que les nostre esferes es representen amb un centre i un radi,
        // no te sentit considerar escalats diferents en cada eix.
        // Per aixo suposarem que la matriu d'escalat és diagonal, amb els tres
        // primers elements de la diagonal iguals, el quart un 1, i tots els altres
        // 0.
        float scaling_factor = (t->getTG())[0][0];
        radius *= scaling_factor;
    }
}

void Sphere::read(const QJsonObject &json)
{
    Object::read(json);

    if (json.contains("radius") && json["radius"].isDouble())
    {
        radius = json["radius"].toDouble();
    }
    if (json.contains("center") && json["center"].isArray())
    {
        QJsonArray auxVec = json["center"].toArray();
        center[0] = auxVec[0].toDouble();
        center[1] = auxVec[1].toDouble();
        center[2] = auxVec[2].toDouble();
    }
}

//! [1]
void Sphere::write(QJsonObject &json) const
{
    Object::write(json);

    QJsonArray auxArray;
    auxArray.append(center[0]);
    auxArray.append(center[1]);
    auxArray.append(center[2]);
    json["center"] = auxArray;

    json["radius"] = abs(radius);
}
//! [1]

void Sphere::print(int indentation) const
{
    Object::print(indentation);

    const QString indent(indentation * 2, ' ');

    QTextStream(stdout) << indent << "center:\t" << center[0] << ", " << center[1] << ", " << center[2] << "\n";
    QTextStream(stdout) << indent << "radius:\t" << radius << "\n";
}

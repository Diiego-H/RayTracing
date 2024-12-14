#include "Box.hh"

Box::Box()
{
    min = vec3(0.0, 0.0, 0.0);
    max = vec3(0.0, 0.0, 0.0);
}

Box::Box(const vec3 &min, const vec3 &max)
{
    // Each component in min must be lower or equal than that in max
    this->min = min;
    this->max = max;
}

// Smits' method
bool Box::hit(Ray &raig, float tmin, float tmax) const
{
    float min_inter = tmin, max_inter = tmax;
    int normal_comp_min, normal_comp_max;
    vec3 direction = raig.getDirection();
    vec3 origin = raig.getOrigin();

    // Obtencio interseccio minima i maxima tractant components
    bool any = false;
    for (int i = 0; i < 3; i++)
    {
        float t0, t1, div = 1 / direction[i];

        // Valor minim i maxim de t en aquesta component
        if (div > 0)
        {
            t0 = (min[i] - origin[i]) * div;
            t1 = (max[i] - origin[i]) * div;
        }
        else
        {
            t0 = (max[i] - origin[i]) * div;
            t1 = (min[i] - origin[i]) * div;
        }

        // Interseccio fora de (tmin, tmax)
        if (t0 > tmax || t1 < tmin)
            return false;

        // Actualitzacio minim/maxim
        if (t0 > min_inter)
        {
            min_inter = t0;
            normal_comp_min = i;
        }
        if (t1 < max_inter)
        {
            max_inter = t1;
            normal_comp_max = i;
        }
    }

    // Validacio final de t (hem comprovat min_inter < tmax i tmin < max_inter)
    if (min_inter < max_inter)
    {
        if (tmin < min_inter)
        {
            // Interseccio amb menor t
            shared_ptr<HitRecord> hit = make_shared<HitRecord>();
            hit->t = min_inter;
            hit->p = raig.pointAt(min_inter);
            hit->mat = material;

            // Normal i-essim vector base canonica, i component interseccio que dona la t (sentit oposat al raig)
            vec3 temp(0.0);
            temp[normal_comp_min] = (direction[normal_comp_min] > 0) ? -1.0f : 1.0f;
            hit->normal = temp;

            // Afegim el hit
            raig.addHit(hit);

            any = true;
        }
        else if (max_inter < tmax)
        {
            // Interseccio amb major t
            shared_ptr<HitRecord> hit = make_shared<HitRecord>();
            hit->t = max_inter;
            hit->p = raig.pointAt(max_inter);
            hit->mat = material;

            // Normal i-essim vector base canonica, i component interseccio que dona la t (sentit oposat al raig)
            vec3 temp(0.0);
            temp[normal_comp_max] = (direction[normal_comp_max] > 0) ? -1.0f : 1.0f;
            hit->normal = temp;

            // Afegim el hit
            raig.addHit(hit);

            any = true;
        }
    }

    return any;
}

// Igual que hit() contemplant les dues possibilitats d'interseccio i amb insertHit()
bool Box::allHits(Ray &raig, float tmin, float tmax) const
{
    float min_inter = tmin, max_inter = tmax;
    int normal_comp_min, normal_comp_max;
    vec3 direction = raig.getDirection();
    vec3 origin = raig.getOrigin();

    // Obtencio interseccio minima i maxima tractant components
    bool any = false;
    for (int i = 0; i < 3; i++)
    {
        float t0, t1, div = 1 / direction[i];

        // Valor minim i maxim de t en aquesta component
        if (div > 0)
        {
            t0 = (min[i] - origin[i]) * div;
            t1 = (max[i] - origin[i]) * div;
        }
        else
        {
            t0 = (max[i] - origin[i]) * div;
            t1 = (min[i] - origin[i]) * div;
        }

        // Interseccio fora de (tmin, tmax)
        if (t0 > tmax || t1 < tmin)
            return false;

        // Actualitzacio minim/maxim
        if (t0 > min_inter)
        {
            min_inter = t0;
            normal_comp_min = i;
        }
        if (t1 < max_inter)
        {
            max_inter = t1;
            normal_comp_max = i;
        }
    }

    // Validacio final de t (hem comprovat min_inter < tmax i tmin < max_inter)
    if (min_inter < max_inter)
    {
        // Interseccio amb menor t
        if (tmin < min_inter)
        {
            shared_ptr<HitRecord> hit = make_shared<HitRecord>();
            hit->t = min_inter;
            hit->p = raig.pointAt(min_inter);
            hit->mat = material;

            // Normal i-essim vector base canonica, i component interseccio que dona la t (sentit oposat al raig)
            vec3 temp(0.0);
            temp[normal_comp_min] = (direction[normal_comp_min] > 0) ? -1.0f : 1.0f;
            hit->normal = temp;

            // Afegim el hit
            raig.insertHit(hit);

            any = true;
        }

        // Interseccio amb major t
        if (max_inter < tmax)
        {
            shared_ptr<HitRecord> hit = make_shared<HitRecord>();
            hit->t = max_inter;
            hit->p = raig.pointAt(max_inter);
            hit->mat = material;

            // Normal i-essim vector base canonica, i component interseccio que dona la t (sentit oposat al raig)
            vec3 temp(0.0);
            temp[normal_comp_max] = (direction[normal_comp_max] > 0) ? -1.0f : 1.0f;
            hit->normal = temp;

            // Afegim el hit
            raig.insertHit(hit);

            any = true;
        }
    }

    return any;
}

void Box::update(int frame)
{
    // TO DO: Cal ampliar-lo per a fer el update de la box
    Animable::update(frame);
}

void Box::aplicaTG(shared_ptr<TG> t)
{
    if (dynamic_pointer_cast<TranslateTG>(t))
    {
        // Transladem el punt minim del box
        vec4 minpoint(min, 1.0);
        minpoint = t->getTG() * minpoint;
        min.x = minpoint.x;
        min.y = minpoint.y;
        min.z = minpoint.z;

        // Transladem el punt maxim del box
        vec4 maxpoint(max, 1.0);
        maxpoint = t->getTG() * maxpoint;
        max.x = maxpoint.x;
        max.y = maxpoint.y;
        max.z = maxpoint.z;
    }
    else if (dynamic_pointer_cast<ScaleTG>(t))
    {
        // Trobem el vector del box dividit entre dos i el centre del box, els usarem
        // per fer l'escalat i preservar el centre del box
        vec3 halfBoxVec = (max - min) / 2.0f;
        vec3 midPoint = min + (halfBoxVec);

        // Escalem el vector de box
        vec4 halfBoxVec4(halfBoxVec, 1);
        halfBoxVec4 = t->getTG() * halfBoxVec4;
        halfBoxVec = vec3(halfBoxVec4.x, halfBoxVec4.y, halfBoxVec4.z);

        // Reconstruim el box amb el nou vector de box i el centre trobat previament
        min = midPoint - halfBoxVec;
        max = midPoint + halfBoxVec;
    }
}

void Box::read(const QJsonObject &json)
{
    Object::read(json);

    if (json.contains("punt_min") && json["punt_min"].isArray())
    {
        QJsonArray auxVec = json["punt_min"].toArray();
        min[0] = auxVec[0].toDouble();
        min[1] = auxVec[1].toDouble();
        min[2] = auxVec[2].toDouble();
    }
    if (json.contains("punt_max") && json["punt_max"].isArray())
    {
        QJsonArray auxVec = json["punt_max"].toArray();
        max[0] = auxVec[0].toDouble();
        max[1] = auxVec[1].toDouble();
        max[2] = auxVec[2].toDouble();
    }
}

//! [1]
void Box::write(QJsonObject &json) const
{
    Object::write(json);

    QJsonArray auxArray;
    auxArray.append(min[0]);
    auxArray.append(min[1]);
    auxArray.append(min[2]);
    json["punt_min"] = auxArray;

    QJsonArray auxArray2;
    auxArray2.append(max[0]);
    auxArray2.append(max[1]);
    auxArray2.append(max[2]);
    json["punt_max"] = auxArray2;
}
//! [1]

void Box::print(int indentation) const
{
    Object::print(indentation);

    const QString indent(indentation * 2, ' ');

    QTextStream(stdout) << indent << "Min_point:\t" << min[0] << ", " << min[1] << ", " << min[2] << "\n";
    QTextStream(stdout) << indent << "Max_point:\t" << max[0] << ", " << max[1] << ", " << max[2] << "\n";
}

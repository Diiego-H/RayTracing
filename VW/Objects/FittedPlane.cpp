#include "FittedPlane.hh"

void FittedPlane::computeAttributes() {
    w = pmax[0] - pmin[0];
    h = pmax[1] - pmin[1];

    /* NO ES MODIFICA LA PROJECCIO SEGONS SI EL VECTOR NORMAL TE +1 O -1 A LA COMPONENT NO NUL·LA */

    // Quan el pla és perpendicular a l'eix x, z serà la component de l'amplada, si no serà x
    w_component = (abs(abs(normal[0]) - 1) < DBL_EPSILON)? 2 : 0;

    // Quan el pla és perpendicular a l'eix y, z serà la component de l'alçada, si no serà y
    h_component = (abs(abs(normal[1]) - 1) < DBL_EPSILON)? 2 : 1;

    // Punt d'origen del pla
    origin = v1;
    origin[w_component] += pmin[0];
    origin[h_component] += pmin[1];
}

bool FittedPlane::hit(Ray &raig, float tmin, float tmax) const {
    bool hitFound = false;

    // Intersecció amb el pla?
    Ray aux(raig.getOrigin(), raig.getDirection(), tmin, tmax);
    if (Plane::hit(aux, tmin, tmax)) {
        shared_ptr<HitRecord> hit = aux.getHit(0);

        // Traslladem el punt al pla paral·lel amb inici el (0,0,0)
        vec3 p = hit->p - origin;

        // Intersecció entre pmin i pmax?
        if (p[w_component] < 0.0 || p[w_component] > w || p[h_component] < 0.0 || p[h_component] > h) {
            return false;
        }

        // Intersecció valida, guardem el hit un cop projectem el punt
        hit->uv = vec2(p[w_component] / w, p[h_component] / h);
        raig.addHit(hit);
        hitFound = true;
    }

    return hitFound;
}

bool FittedPlane::allHits(Ray& r, float tmin, float tmax) const {
    Ray aux(r.getOrigin(), r.getDirection(), tmin, tmax);
    if (hit(aux,tmin,tmax)) {
        r.insertHit(aux.getHit(0));
        return true;
    } else { 
        return false; 
    }
}

void FittedPlane::read (const QJsonObject &json) {
    Plane::read(json);

    if (json.contains("pmin") && json["pmin"].isArray()) {
        QJsonArray auxVec = json["pmin"].toArray();
        pmin[0] = auxVec[0].toDouble();
        pmin[1] = auxVec[1].toDouble();
    }
    if (json.contains("pmax") && json["pmax"].isArray()) {
        QJsonArray auxVec = json["pmax"].toArray();
        pmax[0] = auxVec[0].toDouble();
        pmax[1] = auxVec[1].toDouble();
    }

    // Computem atributs addicionals a partir dels llegits
    computeAttributes();
}

void FittedPlane::write(QJsonObject &json) const {
    Plane::write(json);

    QJsonArray auxArray;
    auxArray.append(pmin[0]);auxArray.append(pmin[1]);
    json["pmin"] = auxArray;

    QJsonArray auxArray2;
    auxArray2.append(pmax[0]);auxArray2.append(pmax[1]);
    json["pmax"] = auxArray2;
}

void FittedPlane::print(int indentation) const {
    Plane::print(indentation);

    const QString indent(indentation * 2, ' ');

    QTextStream(stdout) << indent << "w:\t" << w << "\n";
    QTextStream(stdout) << indent << "h:\t" << h << "\n";
}
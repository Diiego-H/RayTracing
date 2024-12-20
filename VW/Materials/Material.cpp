#include "Material.hh"

// Valors arbitraris. Podem decidir canviar-los
Material::Material() : Ka(1.0f), Kd(1.0f), Ks(1.0f), Kt(0.0f)
{
    shininess = 1.0f;
}

Material::~Material()
{
}

Material::Material(vec3 d)
{
    Kd = d;
    // Valors arbitraris. Podem decidir canviar-los.
    Ka = vec3(1.0f, 1.0f, 1.0f);
    Ks = vec3(1.0f, 1.0f, 1.0f);
    shininess = 1.0f;
    Kt = vec3(0.0f, 0.0f, 0.0f);
    nut = 0.0f;
    dmax = 0.0f; // per defecte opac
}

Material::Material(vec3 a, vec3 d, vec3 s, float shin)
{
    // Fase 2
    Ka = a;
    Kd = d;
    Ks = s;
    shininess = shin;
    nut = 0.0f;
    dmax = 0.0f; // per defecte opac
}

Material::Material(vec3 a, vec3 d, vec3 s, float shin, float opac)
{
    // Fase 2
    Ka = a;
    Kd = d;
    Ks = s;
    shininess = shin;
    opacity = opac;
    nut = 0.0f;
    dmax = 0.0f; // per defecte opac
}

vec3 Material::getDiffuse(vec2 point) const
{
    return Kd;
}

void Material::read(const QJsonObject &json)
{
    if (json.contains("ka") && json["ka"].isArray())
    {
        QJsonArray auxVec = json["ka"].toArray();
        Ka[0] = auxVec[0].toDouble();
        Ka[1] = auxVec[1].toDouble();
        Ka[2] = auxVec[2].toDouble();
    }
    if (json.contains("kd") && json["kd"].isArray())
    {
        QJsonArray auxVec = json["kd"].toArray();
        Kd[0] = auxVec[0].toDouble();
        Kd[1] = auxVec[1].toDouble();
        Kd[2] = auxVec[2].toDouble();
    }
    if (json.contains("kdtoon") && json["kdtoon"].isArray())
    {
        QJsonArray auxVec = json["kdtoon"].toArray();
        for (int i = 0; i < 4; i++)
        {
            QJsonArray auxKd = auxVec[i].toArray();
            for (int j = 0; j < 3; j++)
            {
                KdToon[i][j] = auxKd[j].toDouble();
            }
        }
    }
    if (json.contains("ks") && json["ks"].isArray())
    {
        QJsonArray auxVec = json["ks"].toArray();
        Ks[0] = auxVec[0].toDouble();
        Ks[1] = auxVec[1].toDouble();
        Ks[2] = auxVec[2].toDouble();
    }
    if (json.contains("shininess") && json["shininess"].isDouble())
        shininess = json["shininess"].toDouble();

    if (json.contains("kt") && json["kt"].isArray())
    {
        QJsonArray auxVec = json["kt"].toArray();
        Kt[0] = auxVec[0].toDouble();
        Kt[1] = auxVec[1].toDouble();
        Kt[2] = auxVec[2].toDouble();
    }

    if (json.contains("opacity") && json["opacity"].isDouble())
        opacity = json["opacity"].toDouble();

    if (json.contains("nut") && json["nut"].isDouble())
        nut = json["nut"].toDouble();

    if (json.contains("dmax") && json["dmax"].isDouble())
        dmax = json["dmax"].toDouble();
}

//! [1]
void Material::write(QJsonObject &json) const
{
    QJsonArray auxArray;
    auxArray.append(Ka[0]);
    auxArray.append(Ka[1]);
    auxArray.append(Ka[2]);
    json["ka"] = auxArray;

    QJsonArray auxArray2;
    auxArray2.append(Kd[0]);
    auxArray2.append(Kd[1]);
    auxArray2.append(Kd[2]);
    json["kd"] = auxArray2;

    QJsonArray auxArray3;
    auxArray3.append(Ks[0]);
    auxArray3.append(Ks[1]);
    auxArray3.append(Ks[2]);
    json["ks"] = auxArray3;

    QJsonArray auxArray4;
    auxArray4.append(Kt[0]);
    auxArray4.append(Kt[1]);
    auxArray4.append(Kt[2]);
    json["kt"] = auxArray4;

    json["opacity"] = opacity;
    json["shininess"] = shininess;
    json["nut"] = nut;
    json["dmax"] = dmax;
}

//! [1]

void Material::print(int indentation) const
{
    const QString indent(indentation * 2, ' ');

    QTextStream(stdout) << indent << "Ka:\t" << Ka[0] << ", " << Ka[1] << ", " << Ka[2] << "\n";
    QTextStream(stdout) << indent << "Kd:\t" << Kd[0] << ", " << Kd[1] << ", " << Kd[2] << "\n";
    QTextStream(stdout) << indent << "Ks:\t" << Ks[0] << ", " << Ks[1] << ", " << Ks[2] << "\n";
    QTextStream(stdout) << indent << "Kt:\t" << Kt[0] << ", " << Kt[1] << ", " << Kt[2] << "\n";
    QTextStream(stdout) << indent << "shininess:\t" << shininess << "\n";
    QTextStream(stdout) << indent << "opacity:\t" << opacity << "\n";
    QTextStream(stdout) << indent << "nut:\t" << nut << "\n";
    QTextStream(stdout) << indent << "dmax:\t" << dmax<< "\n";
}

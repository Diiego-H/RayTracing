#include "MaterialTextura.hh"

MaterialTextura::MaterialTextura(const vec3& color): Material()
{
    Kd = color;
}

MaterialTextura::MaterialTextura(const vec3& a, const vec3& d, const vec3& s, const float k):
    Material(a, d, s, k) {
}

MaterialTextura::MaterialTextura(const vec3& a, const vec3& d, const vec3& s, const float k, const float o):
    Material(a, d, s, k, o) {
}

MaterialTextura::~MaterialTextura()
{
}

bool MaterialTextura::scatter(const Ray& r_in, int t, vec3& color, Ray & r_out) const {
    // Les textures no calculen rajos secundaris
    return false;
}

vec3 MaterialTextura::getDiffuse(vec2 point) const {
    return textura->getColorPixel(point);

}

void MaterialTextura::read (const QJsonObject &json) {
    Material::read(json);
    if (json.contains("textureFile") && json["textureFile"].isString()) {
        textureFile = json["textureFile"].toString();
        textura = make_shared<Texture>(textureFile);
    }
}

void MaterialTextura::write(QJsonObject &json) const {
    Material::write(json);
    json["textureFile"] = textureFile;
}

void MaterialTextura::print(int indentation) const {
    Material::print(indentation);
    const QString indent(indentation * 2, ' ');
    QTextStream(stdout) << indent << "textureFile:\t" << textureFile << "\n";
}
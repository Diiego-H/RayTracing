#include "Transparent.hh"

Transparent::Transparent(const vec3 &color) : Material()
{
    Kd = color;
    nut = 1.0f;
}

Transparent::Transparent(const vec3 &a, const vec3 &d, const vec3 &s, const float k) : Material(a, d, s, k)
{
    nut = 1.0f;
}

Transparent::Transparent(const vec3 &a, const vec3 &d, const vec3 &s, const float k, const float o) : Material(a, d, s, k, o)
{
    nut = 1.0f;
}

Transparent::~Transparent()
{
}

bool Transparent::scatter(const Ray &r_in, int t, vec3 &color, Ray &r_out) const
{
    auto rec = r_in.getHit(t);
    // Sabem que les interseccions sempre seran entre aire i objecte
    // Suposem aire com el buit
    // Per tant un dels dos índex de refracció serà 1.0
    // Per a saber quin és l'altre, comprovem si el raig està entrant o sortint
    // Ho farem revisant el signe del producte escalar
    // Si és positiu, el raig està sortint, si és negatiu, el raig està entrant

    vec3 direction = normalize(r_in.getDirection());
    float val = dot(direction, rec->normal);
    float ni_over_nt = 0.0f;
    vec3 normal;

    if (val < 0.0f)
    {
        ni_over_nt = 1.0f / nut;
        normal = rec->normal;
    }
    else
    {
        normal = -rec->normal;
        ni_over_nt = nut;
    }
    vec3 target = refract(direction, normal, ni_over_nt);

    // Mirem si l'angle d'incidència provoca un angle crític de sortida
    // Reflexió interna
    if (glm::length(target) < DBL_EPSILON)
    {
        target = reflect(direction, normal);
        color = Ks;
    }
    else
        color = Kt;

    r_out = Ray(rec->p, target);
    return true;
}

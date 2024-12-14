#include "RayTracing.hh"

RayTracing::RayTracing(QImage *i) : image(i)
{

    setup = Controller::getInstance()->getSetUp();
    scene = Controller::getInstance()->getScene();

    // Guardem l'estratègia com atribut per no crear-la cada cop que la necessitem
    NColorShading = ShadingFactory::getInstance().createShading(ShadingFactory::NCOLORSHADING);
}

void RayTracing::play()
{

    init();
    auto camera = setup->getCamera();
    int width = camera->viewportX;
    float width_inv = 1.0f / width;
    int height = camera->viewportY;
    float height_inv = 1.0f / height;
    float sampleRadius = ((width < height) ? height_inv : width_inv);

    for (int y = height - 1; y >= 0; y--)
    {
        std::cerr << "\rScanlines remaining: " << y << ' ' << std::flush; // Progrés del càlcul
        for (int x = 0; x < width; x++)
        {

            float u = x * width_inv;
            float v = (height - y) * height_inv;
            vec3 color(0, 0, 0);

            // Mostreig de rajos per pixel segons valor de "samples"
            int nSamples = setup->getSamples();
            for (int i = 0; i < nSamples; i++)
            {
                // Soroll en el raig: radi la distància mínima entre punts de píxels adjacents
                vec2 noise = diskRand(sampleRadius);

                // CÀLCUL DEL RAIG EN COORDENADES DE MON
                Ray r = camera->computeRay(u + noise[0], v + noise[1]);

                // CÀLCUL DEL COLOR FINAL DEL PIXEL
                color += this->getColorPixel(r);
            }
            // Clamp a [0,1] del promig del color per cada component
            for (int i = 0; i < 3; i++)
            {
                color[i] = clamp(color[i] / nSamples, 0.0f, 1.0f);
            }

            // Gamma correction
            color = sqrt(color);

            color *= 255;
            setPixel(x, y, color);
        }
    }
}

void RayTracing::setPixel(int x, int y, vec3 color)
{

    if (color.r < 0)
        color.r = 0;
    if (color.g < 0)
        color.g = 0;
    if (color.b < 0)
        color.b = 0;

    if (color.r > 255)
        color.r = 255;
    if (color.g > 255)
        color.g = 255;
    if (color.b > 255)
        color.b = 255;

    image->setPixelColor(x, y, QColor(color.r, color.g, color.b));
}

/* Mètode RayPixel
** TODO: Cal modificar la funcio RayPixel es la funcio recursiva del RayTracing. Cal retocar-lo per:
** TUTORIAL 0 per a fer el degradat del fons
** FASES 0 i 1 per a cridar a la intersecció amb l'escena i posar el color de l'objecte (via color, depth o normal)
** TUTORIAL 2 per incloure els shading més realistes (Blinn-Phong  i ombres)
** TUTORIAL 2 per a tractar reflexions i transparències
**
*/

// Funcio recursiva que calcula el color.
vec3 RayTracing::getColorPixel(Ray &ray, int depth)
{
    vec3 color = vec3(0);

    // Background color
    float t = 0.5f * (normalize(ray.getDirection()).y + 1);
    vec3 backgroundColor = (1 - t) * setup->getDownBackground() + t * setup->getTopBackground();
  
    if (setup->getNHits())
    {
        if (scene->allHits(ray, ray.getTmin(), ray.getTmax()))
        {
            vector<shared_ptr<HitRecord>> hits = ray.getHitRecords();

            // Color amb els N hits
            color = NColorShading->shading(scene, hits, setup->getCamera()->getLookFrom(), setup->getGlobalLight(),
                                            setup->getLights(), setup->getShadows());

            // Contribucio per si no hi ha intersecció
            color += (hits[hits.size() - 1]->mat->Kt) * backgroundColor;
        }
        else
        {
            color = backgroundColor;
        }
    }
    else
    {
        if (scene->hit(ray, ray.getTmin(), ray.getTmax()))
        {
            // Hit mes proper
            vector<shared_ptr<HitRecord>> hits = ray.getHitRecords();
            shared_ptr<HitRecord> h = hits[0];

            if (depth < setup->getMAXDEPTH()) {
                // Contribucio de la reflexio
                vec3 K;
                Ray sec;
                if (h->mat->scatter(ray, 0, K, sec)) {
                    color = K * getColorPixel(sec, depth + 1);
                }
            }
            
            // Color amb el raig primari
            color += (vec3(1) - h->mat->Kt) * setup->getShadingStrategy()->shading(scene, ray.getHitRecords(), setup->getCamera()->getLookFrom(),
                                              setup->getGlobalLight(), setup->getLights(), setup->getShadows());
        }
        else if (depth > 0) 
        {
            // Color que aporten els rajos secundaris sense intersecció
            color = setup->getBackground() ? backgroundColor : setup->getGlobalLight();
        } else 
        {
            // El raig primari dona color background quan no interseca
            color = backgroundColor;
        }
    }

    return color;
}

void RayTracing::init()
{
    auto s = setup->getShadingStrategy();
}

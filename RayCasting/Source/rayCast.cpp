#include "../headers/GraphicObjects.h"
#include "../headers/Config.h"
#include <cmath>

// int scanForSphere(sf::Image *image, Sphere *sphere, Light *light, Vision *vis) {
//     catchNullptr(image, EXIT_FAILURE);
//     catchNullptr(sohere);
//     catchNullptr(light);
//     catchNullptr(vis);

//      Vect3  center = sphere -> getPos();
//     double   rad  = sphere ->  getR(); 

//     for (double x = 0; x < WIDTH; x++)
//         for (double y = 0; y < HEIGHT; y++) {
//             if (sqr(x - center.x) + sqr(y - center.y) > sqr(rad)){
//                 image -> setPixel(x, y, sf::Color::Black);
//                 continue;
//             };

//             double z = sqrt( sqr(rad) - sqr(x - center.x) - sqr(y - center.y) );

//             Vect3 point(x - center.x, y - center.y, z);

//             image -> setPixel(x, y, getPixelColor(sphere, light, vis, point));
//         }
    
//     return;
// }

void Light::rotate(double deltaTime, Vect3 center) {
    Vect3 newVect = (this->pos - center) ^ (deltaTime * ROTATION_VELOCITY);
    this -> pos = newVect + center;

    return;
}

double min(double a, double b);

double pow(double x, int y);

sf::Color getPixelColor(Sphere *sphere, Light *light, Vision *vis, Vect3 point) {
    Vect3 n = !point;

    Vect3 v =  vis ->pos - sphere->getPos();

    Vect3 l = light->pos - sphere->getPos();

    l = !(l - point);
    v = !(v - point);

    double  phi  = (n, l);
    if (phi < 0) phi = 0;

    double alpha = ((!(n * 2 - l)), v);
    if (alpha < 0) alpha = 0;

    // Vect3 pixelColor = (sphere -> getMaterial());

    Vect3 pixelColor = (sphere -> getMaterial() * light -> intensity * phi);
    
    pixelColor += (light -> intensity * pow(alpha, 15));

    pixelColor += (light -> intensity * sphere -> getMaterial());
    
    return sf::Color(min(1, pixelColor.x) * 255, min(pixelColor.y, 1) * 255, min(1, pixelColor.z) * 255);
}

sf::Color getPixelColor2(Sphere *sphere, Light *light, Vision *vis, Vect3 point) {
    Vect3 n = (Vect3(0, 0, 1));

    Vect3 v =  vis ->pos - point;

    Vect3 l = light->pos - point;

    l = !(l - point);
    v = !(v - point);

    double  phi  = (n, l);
    if (phi < 0) phi = 0;

    double alpha = (n * (n, l) * 2, v);
    if (alpha < 0) alpha = 0;

    // Vect3 pixelColor = (sphere -> getMaterial());

    Vect3 pixelColor = (sphere -> getMaterial() * light -> intensity * phi);
    
    pixelColor += (light -> intensity * pow(alpha, 15));

    pixelColor += (light -> intensity * sphere -> getMaterial());
    
    return sf::Color(min(1, pixelColor.x) * 255, min(pixelColor.y, 1) * 255, min(1, pixelColor.z) * 255);
}

double pow(double x, int y) {
    if (y <= 0) return 1;

    if (y % 2)
        return pow(x * x, y / 2) * x;

    return pow(x * x, y / 2);
}

double min(double a, double b) {
    if (a < b) return a;
    return b;
}
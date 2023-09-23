#pragma once

#include <SFML/Graphics.hpp>
#include "Vect.h"

const Vect3  WHITE_LIGHT  = Vect3(1 , 1, 1);
const Vect3 TEST_MATERIAL = Vect3(0.4, 0, 0);

struct Light {
    Vect3 pos;

    Vect3 intensity;

    Light(const Vect3 &position, const Vect3 &inty) :
                 pos (position),
                                 intensity (inty)
    {}

    void rotate(double deltaTime, Vect3 center);

    ~Light() {}
};

struct Vision {
    Vect3 pos;

    Vision(const Vect3 &position) :
                 pos (position)
    {}

    ~Vision() {}
};

class Sphere {

    Vect3 pos;

    double r;

    Vect3 material;


    public:
        Sphere(const Vect3 &position, double r, const Vect3 &material):
                      pos (position),
                                        r (r),
                                                material (material)
        {}

        ~Sphere() {}

        getR(){ return r; }

        Vect3    getPos  () { return    pos;   }
        Vect3 getMaterial() { return material; }
        void setMaterial(Vect3 material) { this->material = material;}

};

int scanForSphere(sf::Image *image, Sphere *sphere, Light *light, Vision *vis);

sf::Color getPixelColor2(Sphere *sphere, Light *light, Vision *vis, Vect3 point);

sf::Color getPixelColor(Sphere *sphere, Light *light, Vision *vis, Vect3 point);
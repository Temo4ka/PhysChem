#include <SFML/Graphics.hpp>
#include "Config.h"
#include "vec.h"

class Molecule {
    double velocity;
    double  weight ;
    Vect     dir   ;
    Vect   position;

    public:
        Molecule (const Vect& startPos, const int rangeX, const int rangeY, const double weight);

        ~Molecule() {}

};

class TypeA : Molecule {

};

class TypeB : Molecule {

};

class Button {
    Vect   position;
    
    double    width;
    double   height;

    public:
        Button(const Vect pos, const double w, const double h) :
                position (pos),
                                     width (w),
                                                    height (h)
        {}

        ~Button() {}

};

class Piston {
    double velocity;

    sf::RectangleShape pistonShape;

    public:
        Piston (const Vect &startPos, const double w, const double h, const double velocity, const sf::Color color);

        ~Piston() {};

        int Move(const double deltaTime);
}
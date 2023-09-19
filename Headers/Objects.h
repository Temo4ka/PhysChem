#include <SFML/Graphics.hpp>
#include "Config.h"
#include "Vect.h"

enum Collision {
    NO_COLLISION = 0,
       COLLISION = 1
};

class Molecule {
    double velocity;
    double  weight ;
    Vect     dir   ;
    Vect   position;

    public:
        Molecule (const Vect startPos, const double weight);

        ~Molecule() {}

        double  getWeight()   { return this ->  weight;  }
        double getVelocity()  { return this -> velocity; }
        Vect   getPosition()  { return this -> position; }
        // Vect   getDirection() { return this ->    dir;   }

        int    setPosition(const Vect newPos);

        int  move(const double deltaTime, const double PistonY);

        int absorb(Molecule *molecule);

        int reverseDir()     { this -> dir = this -> dir * -1; }

        virtual int collide() {}

};

class TypeA : public Molecule {
    double radius;

    public:
        int collide(TypeA *a, MoleculeManager *manager);
        int collide(TypeB *a, MoleculeManager *manager);

        int draw(sf::Image *image);

        double getRadius() { return this -> radius; }

        TypeA(const Vect startPos, const double weight, const double radius):
            Molecule(startPos, weight),
            radius (radius)
        {}
};

class TypeB : public Molecule {
    double len;
    
    public:

        int collide(TypeA *a, MoleculeManager *manager);
        int collide(TypeB *b, MoleculeManager *manager);

        int draw(sf::Image *image);

        double getLen() { return len / 2; }

        TypeB(const Vect startPos, const double weight, const double len):
            Molecule(startPos, weight),
            len (len)
        {}
};

class MoleculeManager {
    int size;

    Molecule **array;

    public:
        MoleculeManager();
        ~MoleculeManager();

        int addMolecule(const Molecule *newMolecule);

        int swap(Molecule *a, Molecule *b);

        int eraseMolecule(const int ind);

        int update();

        int createTypeA(const Piston *piston);
        int createTypeB(const Piston *piston);

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
        Piston (const Vect &startPos, const double w, const double h, const double velocity, const sf::Color color = sf::Color(0, 180, 0));

        ~Piston() {};

        int move(const double deltaTime);

        int draw(sf::RenderWindow *window);

        double getPosition();
};
#pragma once

#include <SFML/Graphics.hpp>
#include "Config.h"
#include "Vect.h"
#include "../RayCasting/Headers/GraphicObjects.h"

enum Collision {
    NO_COLLISION = 0,
       COLLISION = 1
};

enum ButtonPressure {
    BUTTON_NOT_PRESSED = 0,
    BUTTON_PRESSED = 1
};

class Molecule;
class TypeA;
class TypeB;
class MoleculeManager;

class Piston;

class Molecule {
    Vect   velocity;
    double  weight ;
    Vect   position;

    public:
        Molecule (const Vect startPos, const double weight);

        ~Molecule() {}

        double  getWeight (      )  { return this ->  weight;  }
        Vect   getVelocity(      )  { return this -> velocity; }
        Vect   getPosition(      )  { return this -> position; }
        void   setVelocity(Vect v)  {    this -> velocity = v; }
        // Vect   getDirection() { return this ->    dir;   }

        int    setPosition(const Vect newPos);

        int  move(const double deltaTime, const double PistonY);

        int absorb(Molecule *molecule);

        void reverseDir()     { this -> velocity = this -> velocity * -1; }

        virtual int collide (Molecule *m, MoleculeManager *manager) { return NO_COLLISION; }
        virtual int collide2(  TypeA  *a, MoleculeManager *manager) { return NO_COLLISION; }
        virtual int collide2(  TypeB  *b, MoleculeManager *manager) { return NO_COLLISION; }
        // virtual int collide(TypeB *b, MoleculeManager *manager) { return EXIT_FAILURE; }

        virtual int draw(sf::Image *image, Light *light, Vision *vision) { return EXIT_FAILURE; }

};

class TypeA : public Molecule {
    double radius;

    public:
        int collide( Molecule *m, MoleculeManager *manager);
        int collide2(  TypeA  *a, MoleculeManager *manager);
        int collide2(  TypeB  *a, MoleculeManager *manager);

        int draw(sf::Image *image, Light *light, Vision *vision);

        double getRadius() { return this -> radius; }

        TypeA(const Vect startPos, const double weight, const double radius):
            Molecule(startPos, weight),
            radius (radius)
        {}
};

class TypeB : public Molecule {
    double len;
    
    public:
        int collide(Molecule *m, MoleculeManager *manager);
        int collide2(  TypeA  *a, MoleculeManager *manager);
        int collide2(  TypeB  *a, MoleculeManager *manager);

        int draw(sf::Image *image, Light *light, Vision *vision);

        double getLen() { return len / 2; }

        TypeB(const Vect startPos, const double weight, const double len):
            Molecule(startPos, weight),
            len (len)
        {}
};

class MoleculeManager {
    signed size;

    Molecule **array;

    Piston *piston;

    Light *light;

    Vision *vision;

    public:
        MoleculeManager(Piston *piston, Light *light, Vision *vision);
        ~MoleculeManager();

        int createTypeA(Piston *piston);
        int createTypeB(Piston *piston);

        int addMolecule(Molecule *newMolecule);

        int eraseMolecule(const int ind);

        int swap(Molecule **a, Molecule **b);

        int update(const double deltaTime);

        int  draw (sf::Image *image);

        int      getSize()  { return this-> size;  }

        Piston* getPiston() { return this->piston; }
};

class Piston {
    double velocity;

    sf::RectangleShape pistonShape;

    public:
        Piston (const Vect &startPos, const double w, const double h, const double velocity, const sf::Color color = sf::Color(0, 180, 0));

        ~Piston() {};

        int move(const double deltaTime);

        int moveButton(const double k);

        int draw(sf::RenderWindow *window);

        double getPosition();
};

class Graphics {
    Vect position;

    int w;
    int h;

    int curX;

    public:
        Graphics(Vect pos, int h, int w):
            position (pos),
                               h (h),
                                         w (w),
        curX (-1)
        {}

        ~Graphics() {}

        int   getH () { return this->h;    }
        int   getW () { return this->w;    }
        int getCurX() { return this->curX; }

        void incCurX() { (this->curX)++;   }

        void setCurX(int x) { this->curX = x; }

        Vect getPosition() { return this->position; }

        int draw(sf::Image *image, sf::Color color = sf::Color(0, 80, 0));
};

class Time_Molecules : public Graphics {
    int molecules;

    double updTime;

    public:
        Time_Molecules(Vect pos, int h, int w):
        Graphics (pos, h, w),
        updTime (GRAPHIC_TIMER)
        {}

        int update(double deltaTime, int molecules, sf::Image *image, sf::Color color = sf::Color(160, 0, 160));

        int showText(sf::RenderWindow *window, sf::Font *font);
};
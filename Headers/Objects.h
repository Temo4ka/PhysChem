#include <SFML/Graphics.hpp>
#include "Config.h"
#include "Vect.h"

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

        void reverseDir()     { this -> dir = this -> dir * -1; }

        virtual int collide (Molecule *m, MoleculeManager *manager) { return NO_COLLISION; }
        virtual int collide2(  TypeA  *a, MoleculeManager *manager) { return NO_COLLISION; }
        virtual int collide2(  TypeB  *b, MoleculeManager *manager) { return NO_COLLISION; }
        // virtual int collide(TypeB *b, MoleculeManager *manager) { return EXIT_FAILURE; }

        virtual int draw(sf::Image *image) { return EXIT_FAILURE; }

};

class TypeA : public Molecule {
    double radius;

    public:
        int collide( Molecule *m, MoleculeManager *manager);
        int collide2(  TypeA  *a, MoleculeManager *manager);
        int collide2(  TypeB  *a, MoleculeManager *manager);

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
        int collide(Molecule *m, MoleculeManager *manager);
        int collide2(  TypeA  *a, MoleculeManager *manager);
        int collide2(  TypeB  *a, MoleculeManager *manager);

        int draw(sf::Image *image);

        double getLen() { return len / 2; }

        TypeB(const Vect startPos, const double weight, const double len):
            Molecule(startPos, weight),
            len (len)
        {}
};

class MoleculeManager {
    signed size;

    Molecule **array;

    public:
        MoleculeManager();
        ~MoleculeManager();

        int createTypeA(Piston *piston);
        int createTypeB(Piston *piston);

        int addMolecule(Molecule *newMolecule);

        int eraseMolecule(const int ind);

        int swap(Molecule **a, Molecule **b);

        int update(const double deltaTime, const double pistonY);

        int  draw (sf::Image *image);
};

class Button {
    Vect   position;
    
    double    width;
    double   height;

    double r;
    double g;
    double b;

    bool isPressed;

    sf::Text text;

    public:
        Button(const Vect pos, const double w, const double h, const double r, const double g, const double b) :
                position (pos),
                                     width (w),
                                                    height (h),
                                                                         r (r),
                                                                                         g (g),
                                                                                                         b (b),
        isPressed (0)
        {}

        int draw(sf::Image *image);

        int setText(const char *text, const signed textSize, sf::Font *font);

        int showText(sf::RenderWindow *window);

        int checkIsPressed(const Vect mousePosition, const int buttonStatus);

        virtual void run();

        ~Button() {}

};

class AddTypeA : public Button {
    MoleculeManager *manager;

    public:
        AddTypeA(const Vect pos, const double w, const double h, const double r, const double g, const double b, MoleculeManager *manager)
        Button(pos, w, h, r, g, b),
        manager(manager)
        {}
        
        ~AddTypeA();

        void run();
};

class ButtonManager {
    signed size;

    Button **array;

    public:
        ButtonManager();
        ~ButtonManager();

        int addButton(Button *button);

        int showText(sf::RenderWindow *window);

        int draw(sf::Image *image);

        int checkPression(sf::RenderWindow *window, const int buttonStatus);
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
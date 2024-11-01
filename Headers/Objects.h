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

class Molecule {
public:
    Molecule(const Vect &DownLeftCorner, const Vect &UpRightCorner, const double weight);
   ~Molecule() {}

    Vect getPosition() const {
        return position;
    }

    void move(const double deltaTime) {
        position += velocity * deltaTime;
    }

    int draw(sf::Image *image, Light *light, Vision *vision);

public:
    const double   weight;
    const double   radius;
    Vect         velocity;
    Vect         position;
    
    const sf::Color color;
};

class Gas {
public:
    Gas(const Vect &DownLeftCorner, const Vect &UpRightCorner):
    DownLeftCorner(DownLeftCorner),
    UpRightCorner(UpRightCorner),
    molecules()
    {}

    void addMolecule(const Vect &startPos, const double weight) {
        molecules.emplace_back((DownLeftCorner + UpRightCorner) * 0.5, weight);
    }

    int update(const double deltaTime);

    int draw(sf::Image *image, Light *light, Vision *vision);

private:
    void collideMolecules(Molecule &a, Molecule &b);
    bool collideWalls    (Molecule &mlc);

public:
    const Vect DownLeftCorner;
    const Vect  UpRightCorner;
private:
    std::vector<Molecule> molecules;

friend class rogramManager;
};

class ProgramManager {
public:
    ProgramManager(
        const Vect &DownLeftCorner, const Vect &UpRightCorner,
        Light  *light,
        Vision *vision):
    gas   (DownLeftCorner, UpRightCorner),
    light (light),
    vision(vision)
    {}

    ~ProgramManager() {}

    int update      (const double deltaTime);
    int addMolecules(size_t n);
    int draw        (sf::Image *image) { gas.draw(image, light, vision); }

public:
    Gas        gas;
private:
    Light   *light;     //TODO: change
    Vision *vision;
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
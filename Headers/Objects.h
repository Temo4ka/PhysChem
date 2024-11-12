#pragma once

#include <SFML/Graphics.hpp>

#include "Vect.h"
#include "Config.h"
#include "Physics.h"
#include "../RayCasting/Headers/GraphicObjects.h"

using namespace Units;

class Molecule {
// static
public:
    enum MOLECULE_TYPE
    {
        H = 0   ,
        He      ,
        N       ,
        O       ,
        F       ,
        Ne      ,
        Cl      ,
        Ar      ,
        Kr      ,
        Xe      ,
        Rn      ,

        NUM_MOLECULE_TYPE
    };

    struct Molecule_properties
    {
        sf::Color  color;
        Virt_m     radius;
        g_per_mole molar_mass;
    }
    static const Molecules_table[NUM_MOLECULE_TYPE];

// member functions
public:
    Molecule(
        const MOLECULE_TYPE type,
        const VectVirt_m &DownLeftCorner, const VectVirt_m &UpRightCorner,
        const Virt_m_per_sec &MaxVelocity);
   ~Molecule() {}

    void move(const Virt_sec deltaTime) {
        position_.vect_ += velocity_.vect_ * deltaTime.val_;
    }

    int draw(sf::Image *image, Light *light, Vision *vision);

// member data
public:
    MOLECULE_TYPE const type_;
    VectVirt_m_per_sec  velocity_;
    VectVirt_m          position_;
};

class Gas {
public:
    Gas(const VectVirt_m &DownLeftCorner, const VectVirt_m &UpRightCorner):
    DownLeftCorner(DownLeftCorner),
    UpRightCorner(UpRightCorner),
    molecules()
    {}

    void addMolecule(const Molecule::MOLECULE_TYPE type, const Virt_mole amount = 0.01, const Virt_m_per_sec &MaxVelocity = 400);
    int update(const double deltaTime);
    int draw(sf::Image *image, Light *light, Vision *vision);

private:
    void collideMolecules(Molecule &a, Molecule &b);
    int  collideWalls    (Molecule &mlc);

public:
    const VectVirt_m DownLeftCorner;
    const VectVirt_m  UpRightCorner;
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

    int update(const double deltaTime) { return gas.update(deltaTime); }
    int draw(sf::Image *image) { return gas.draw(image, light, vision); }

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
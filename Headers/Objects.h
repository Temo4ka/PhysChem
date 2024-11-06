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

    void addMolecule(const double weight) {
        molecules.emplace_back(DownLeftCorner, UpRightCorner, weight);
    }

    int update(const double deltaTime);

    int draw(sf::Image *image, Light *light, Vision *vision);

private:
    void collideMolecules(Molecule &a, Molecule &b);
    int collideWalls    (Molecule &mlc);

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

    int update(const double deltaTime) { return gas.update(deltaTime); }
    int draw(sf::Image *image) { return gas.draw(image, light, vision); }
    
    void addMolecule() { gas.addMolecule(rand()); }

public:
    Gas        gas;
private:
    Light   *light;     //TODO: change
    Vision *vision;
};

class Graph {
  public:
    Graphics(const std::string &name_, std::string &legendX_, std::string &legendY_):
    name (name_),
    legendX (leegendX_),
    legendY (leegendY_),
    timer (GRAPHIC_TIMER)
    {}

    ~Graphics() {}

    Vect getPosition() { return this->position; }

    void update(double deltaTime, int value);

    void drawBase(Vect &position, Vect &size, sf::Image *image, sf::Color color = sf::Color(0, 80, 0));

    void draw(Vect &position, Vect &size, sf::Image *image, sf::Color color = sf::Color(0, 80, 0));

  private:
    std::string name;
    std::string legendX;
    std::string legendY;

    int valY;

    double timer;
};

class GraphManager {

}

class Time_Molecules : public Graphics {
    public:
        Time_Molecules(Vect pos, int h, int w):
        Graphics (pos, h, w),
        updTime (GRAPHIC_TIMER)
        {}

        int update(double deltaTime, int molecules, sf::Image *image, sf::Color color = sf::Color(160, 0, 160));

        int showText(sf::RenderWindow *window, sf::Font *font);
};
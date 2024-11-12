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

    int getMoleculesNum() { return molecules.size(); }

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

    int getMoleculesNum() { return gas.getMoleculesNum(); }

public:
    Gas        gas;
private:
    Light   *light;     //TODO: change
    Vision *vision;
};

class Graph {
  public:
    Graph(const std::string &name_, const std::string &legendX_, const std::string &legendY_, const int max_x, const int max_y):
    name (name_),
    legendX (legendX_),
    legendY (legendY_),
    MAX_X (max_x),
    MAX_Y (max_y),
    timer (GRAPHIC_TIMER)
    {}

    ~Graph() {}

    void update(const double deltaTime, const int value);

    void drawBase(const Vect &position, const Vect &size, sf::Image *image, const sf::Font &font, std::vector<sf::Text> &textToDraw);

    void draw(const Vect &position, const Vect &size, sf::Image *image);

  private:
    void showAllText(const Vect &position, const Vect &size, std::vector<sf::Text> &textToDraw, const sf::Font &font);

    sf::Text getText(const Vect &position, const sf::Font &font, const std::string text_, const size_t charSize);

    std::string name;
    std::string legendX;
    std::string legendY;

    int curY;
    int curX;

    const int MAX_X;
    const int MAX_Y;

    double timer;
};

class GraphManager {
  public:
    enum GraphTypes {
        MOLECULES,
    };

    GraphManager(const Vect &LeftUpperCorner_, const Vect &RightLowerCorner_):
        LeftUpperCorner(LeftUpperCorner_),
        RightLowerCorner(RightLowerCorner_)
    {}


    void update(const GraphTypes type, const double deltaTime, const int value) { graphs[type].update(deltaTime, value); }

    void draw(sf::Image *image) {
        Vect size = (RightLowerCorner - LeftUpperCorner) / 2;

        for (int curGraph = 0; curGraph < graphs.size(); curGraph++)
            graphs[curGraph].draw(LeftUpperCorner + size * curGraph, size, image);
    }

    void init(sf::Image *image, sf::Font &font, std::vector<sf::Text> &textToDraw) {
        Vect size = (RightLowerCorner - LeftUpperCorner) / 2;

        for (int curGraph = 0; curGraph < graphs.size(); curGraph++)
            graphs[curGraph].drawBase(LeftUpperCorner + size * curGraph, size, image, font, textToDraw);
    }



  private:
    std::vector<Graph> graphs = {
        Graph("Molecules", "time", "mols", 100, 100)
    };

    Vect LeftUpperCorner;
    Vect RightLowerCorner;
};

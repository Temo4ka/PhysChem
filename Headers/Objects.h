#pragma once

#include <cassert>
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
        VectVirt_m deltaPos = velocity_ * deltaTime;

        position_ += deltaPos;
        free_run_ += deltaPos.len();
    }

    Virt_Joule get_kinetic_energy() const;

    int draw(sf::Image *image, Light *light, Vision *vision);

// member data
public:
    MOLECULE_TYPE const type_;
    VectVirt_m_per_sec  velocity_;
    VectVirt_m          position_;
    Virt_m              free_run_;
};

class Gas {
public:
    struct gas_group
    {
        Virt_mole  amount;
        Virt_Joule kinetic_energy;
        Kelvin     temperature;
    };

public:
    Gas(const VectVirt_m &DownLeftCorner, const VectVirt_m &UpRightCorner):
    DownLeftCorner(DownLeftCorner),
    UpRightCorner (UpRightCorner ),
    perimeter     (2*((UpRightCorner - DownLeftCorner).get_x() + (UpRightCorner - DownLeftCorner).get_y())),
    square        ((UpRightCorner - DownLeftCorner).get_x() * (UpRightCorner - DownLeftCorner).get_y())
    {}

    void addMolecule(const Molecule::MOLECULE_TYPE type, const Virt_mole amount = 0.25, const Virt_m_per_sec &MaxVelocity = 400);
    int update(const Virt_sec deltaTime);
    int draw(sf::Image *image, Light *light, Vision *vision);

    int getMoleculesNum() const
    {
        return molecules.size();
    }

    const gas_group &get_gas_group(Molecule::MOLECULE_TYPE type) const
    {
        assert(type >= 0 && type < Molecule::NUM_MOLECULE_TYPE);
        return gas_groups[type];
    }

    Kelvin            get_temperature() const { return temperature_; }
    Virt_Newton_per_m get_pressure   () const { return pressure_; }
    Virt_m            get_free_run   () const { return free_run_; }

private:
    void collideMolecules(Molecule &a, Molecule &b);
    void collideWalls    (Molecule &mlc);
    void calc_temperature();
    void calc_free_run   ();

public:
    const VectVirt_m DownLeftCorner;
    const VectVirt_m  UpRightCorner;
    const Virt_m          perimeter;
    const Virt_m2            square;

private:
    std::vector<Molecule> molecules;
    gas_group             gas_groups[Molecule::NUM_MOLECULE_TYPE];

    Kelvin                temperature_;
    Virt_Newton_per_m     pressure_; // так как у нас 2D-задача, то и давление будет в Ньютонах на метр.
    Virt_m                free_run_;
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
        Graph("Molecules", "time", "mols", 100, 1000)

    };

    Vect LeftUpperCorner;
    Vect RightLowerCorner;
};

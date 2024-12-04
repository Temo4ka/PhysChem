#pragma once

#include <cassert>
#include <SFML/Graphics.hpp>
#include "GraphConfig.h"
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

    Virt_Joule get_kinetic_energy()                                               const;
    int        draw              (sf::Image *image, Light *light, Vision *vision) const;

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
    Gas(const VectVirt_m &DownLeftCorner, const VectVirt_m &UpRightCorner);

    void addMolecule(const Molecule::MOLECULE_TYPE type, const Virt_mole amount = 0.25, const Virt_m_per_sec &MaxVelocity = 400);
    int  update     (const Virt_sec deltaTime);
    int  draw       (sf::Image *image, Light *light, Vision *vision) const;

    void piston_up  () { piston_velocity_ = -30; };
    void piston_down() { piston_velocity_ =  30; };
    void piston_stop() { piston_velocity_ =   0; };

    int getMoleculesNum() const
    {
        return molecules_.size();
    }

    const gas_group &get_gas_group(Molecule::MOLECULE_TYPE type) const
    {
        assert(type >= 0 && type < Molecule::NUM_MOLECULE_TYPE);
        return gas_groups_[type];
    }

    Kelvin            get_temperature() const { return temperature_; }
    Virt_Newton_per_m get_pressure   () const { return pressure_;    }
    Virt_mole         get_amount     () const { return amount_;      }
    Virt_m            get_free_run   () const { return free_run_;    }

    Virt_Joule        get_energy     () const { return energy_;      }
    Virt_Joule        get_piston_work() const { return piston_work_; }

    Virt_m2           get_square     () const { return square_;      }

private:
    void collideMolecules(Molecule &a, Molecule &b);
    void collideWalls    (Molecule &mlc);
    void calc_temperature();
    void calc_free_run   ();

public:
    VectVirt_m const UpRightCorner_;
private:
    VectVirt_m      DownLeftCorner_;
    Virt_m               perimeter_;
    Virt_m2                 square_;

    Virt_m_per_sec piston_velocity_;
    Virt_Joule     piston_work_;

    std::vector<Molecule> molecules_;
    gas_group             gas_groups_[Molecule::NUM_MOLECULE_TYPE];

    Kelvin                temperature_ = 0;
    Virt_Newton_per_m     pressure_    = 0; // так как у нас 2D-задача, то и давление будет в Ньютонах на метр.
    Virt_mole             amount_      = 0;
    Virt_Joule            energy_      = 0;
    Virt_m                free_run_    = 0;
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
     struct GraphColors {
        sf::Color GRAPH_BACKGROUND_COLOR = sf::Color(0, 80, 0);
        sf::Color   GRAPH_LEGEND_COLOR   = sf::Color::White;
        sf::Color   GRAPH_DIAGRAM_COLOR  = sf::Color(80, 0, 0);

        GraphColors() {}
        GraphColors(const sf::Color &back, const sf::Color &legend, const sf::Color &diag):
        GRAPH_BACKGROUND_COLOR(back),
        GRAPH_LEGEND_COLOR(legend),
        GRAPH_DIAGRAM_COLOR(diag)
        {}
    } colorScheme;

    Graph(const std::string &name_, const std::string &legendX_, const std::string &legendY_, const int max_x, const int max_y, const GraphColors &colorScheme):
    name (name_),
    legendX (legendX_),
    legendY (legendY_),
    MAX_X (max_x),
    MAX_Y (max_y),
    timer (GRAPHIC_TIMER),
    colorScheme(colorScheme)
    {}

    ~Graph() {}

    void update(const double deltaTime, const double value);

    void drawBase(const Vect &position, const Vect &size, sf::Image *image, const sf::Font &font, std::vector<sf::Text> &textToDraw);

    void draw(const Vect &position, const Vect &size, sf::Image *image);

  private:
    void showAllText(const Vect &position, const Vect &size, std::vector<sf::Text> &textToDraw, const sf::Font &font);

    sf::Text getText(const Vect &position, const sf::Font &font, const std::string text_, const size_t charSize);

    std::string name;
    std::string legendX;
    std::string legendY;

    double curY;
    int curX;

    const int MAX_X;
    const int MAX_Y;

    double timer;
};

class GraphManager {
  public:
    enum GraphTypes {
        PRESSURE,
        PS_nuRT,
        E_Ap
    };

    GraphManager(const Vect &LeftUpperCorner_, const Vect &RightLowerCorner_):
        LeftUpperCorner(LeftUpperCorner_),
        RightLowerCorner(RightLowerCorner_)
    {}


    void update(const GraphTypes type, const double deltaTime, const double value) { graphs[type].update(deltaTime, value); }

    void draw(sf::Image *image) {
        Vect size = RightLowerCorner - LeftUpperCorner;
        size.y /= graphs.size();

        for (int curGraph = 0; curGraph < graphs.size(); curGraph++)
            graphs[curGraph].draw(Vect(LeftUpperCorner.x, LeftUpperCorner.y + size.y * curGraph), size, image);
    }

    void init(sf::Image *image, sf::Font &font, std::vector<sf::Text> &textToDraw) {
        Vect size = RightLowerCorner - LeftUpperCorner;
        size.y /= graphs.size();

        for (int curGraph = 0; curGraph < graphs.size(); curGraph++)
            graphs[curGraph].drawBase(Vect(LeftUpperCorner.x, LeftUpperCorner.y + size.y * curGraph), size, image, font, textToDraw);
    }

  private:

    std::vector<Graph> graphs = {
        Graph("Pressure", "time", "press, N/m", 100, 100, Graph::GraphColors()),
        Graph("PS/nuRT", "time", "PS/nuRT", 100, 10, Graph::GraphColors()),
        Graph("E-Ap", "time", "E, J", 100, 20000, Graph::GraphColors()),
    };

    Vect LeftUpperCorner;
    Vect RightLowerCorner;
};

#include "../Headers/Scene.h"
#include "../RayCasting/Headers/GraphicObjects.h"

#include <cmath>
#include <cassert>

//==================================================================================================

const Molecule::Molecule_properties Molecule::Molecules_table[] =
{
    {sf::Color::White      , 1, Units::MolarMass_H },
    {sf::Color::Magenta    , 1, Units::MolarMass_He},
    {sf::Color::Red        , 2, Units::MolarMass_N },
    {sf::Color::Blue       , 2, Units::MolarMass_O },
    {sf::Color::Yellow     , 2, Units::MolarMass_F },
    {sf::Color(252, 148, 3), 2, Units::MolarMass_Ne},
    {sf::Color::Green      , 3, Units::MolarMass_Cl},
    {sf::Color::Black      , 3, Units::MolarMass_Ar},
    {sf::Color::Cyan       , 4, Units::MolarMass_Kr},
    {sf::Color(252, 3, 227), 5, Units::MolarMass_Xe},
    {sf::Color(163, 28, 28), 6, Units::MolarMass_Rn},
};

Molecule::Molecule(
    const MOLECULE_TYPE type,
    const VectVirt_m &DownLeftCorner, const VectVirt_m &UpRightCorner,
    const Virt_m_per_sec &MaxVelocity):
type_    (type),
velocity_(Vect::rand_unit_vect()),
position_(0, 0)
{
    assert(type_ >= 0 && type_ < NUM_MOLECULE_TYPE);

    const Virt_m     radius   = Molecules_table[type_].radius;
    const VectVirt_m RectSize = UpRightCorner - DownLeftCorner - 2*VectVirt_m(radius, radius);
    const VectVirt_m Offset(
        rand() % (unsigned long long) (RectSize.vect_.x + 1),
        rand() % (unsigned long long) (RectSize.vect_.y + 1)
    );

    position_  = DownLeftCorner + VectVirt_m(radius, radius) + Offset;
    velocity_ *= rand() % (unsigned long long) MaxVelocity.val_;
}

//------------------------------------------------------------------------------------------------

int Molecule::draw(sf::Image *image, Light *light, Vision *vis) {
    catchNullptr(image, EXIT_FAILURE);
    catchNullptr(light, EXIT_FAILURE);
    catchNullptr( vis , EXIT_FAILURE);

    const double radius = Molecules_table[type_].radius.val_;
    const Vect   pos0   = position_.vect_;

    Sphere curSphere(Vect3(pos0.x, pos0.y, 0), radius, Vect3(0.3, 0.3, 0.3));
    for (double x = pos0.x - radius; x <= pos0.x + radius; x++)
        for (double y = pos0.y - radius; y <= pos0.y + radius; y++)
        {
            if (SQR(x - pos0.x) + SQR(y - pos0.y) <= SQR(radius))
            {
                double k = 1 - (SQR(x - pos0.x) + SQR(y - pos0.y)) / SQR(radius);
                k = (k > 1) ? 1 : k;

                Vect3 curColor(0, 0, k);
                curSphere.setMaterial(curColor);

                double z = sqrt(SQR(radius) - SQR(x - pos0.x) - SQR(y - pos0.y));
                image -> setPixel(x, y, getPixelColor(&curSphere, light, vis, Vect3(x - pos0.x, y - pos0.y, z)));
            }
        }

    return EXIT_SUCCESS;
}

//------------------------------------CRINGE_MOMENT--------------------------------------------------------------------------------------

void Gas::collideMolecules(Molecule &a, Molecule &b) {
/*
    Vect distV = b.getPosition() - a.getPosition();

    double dist = sqrt(SQR(distV.x) + SQR(distV.y));

    if (dist < b.radius + a.radius) {

        double velocPrA = (distV, a.velocity) /  dist;
        double velocPrB = (distV, b.velocity) / -dist;

        if (velocPrA + velocPrB > 0) {
            
        }
    }
*/
}

int Gas::collideWalls(Molecule &molecule) {
/*
     if (molecule.position.x < LEFT_WALL + 5) {
        molecule.velocity.x *= -1;
        molecule.position.x = LEFT_WALL + 5;

        return 1;
    }

    if (molecule.position.x > RIGHT_WALL) {
        molecule.velocity.x *= -1;
        molecule.position.x = RIGHT_WALL - 3;

        return 1;
    }

    if (molecule.position.y > WINDOW_HEIGHT) {
        molecule.velocity.y *= -1;
        molecule.position.y = WINDOW_HEIGHT - 5;

        return 1;
    }

    if (molecule.position.y <= CEILING) {
        molecule.velocity.y *= -1;
        molecule.position.y = CEILING + 5;

        return 1;
    }
*/
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------

int Gas::update(const double deltaTime) {
    for (auto curMolecule : molecules)
        curMolecule.move(deltaTime);
    
    // fprintf(logFile, "---------------------------------------\nSIZE:%d\n", this -> size);
    for (int firstPointer = 0; firstPointer < molecules.size(); firstPointer++) {
        for (int secondPointer = firstPointer + 1; secondPointer < molecules.size(); secondPointer++) {
            collideMolecules(molecules[firstPointer], molecules[secondPointer]);
        }
        collideWalls(molecules[firstPointer]);
    }
    // fprintf(logFile, "\nSIZE:%d\n===================================\n", this -> size);

    return EXIT_SUCCESS;
}

int Gas::draw(sf::Image *image, Light *light, Vision *vision) {
    for (auto curMolecule : molecules)
        curMolecule.draw(image, light, vision);

    return EXIT_SUCCESS;
}
#include "../Headers/Scene.h"
#include "../RayCasting/Headers/GraphicObjects.h"

#include <cmath>
#include <cassert>

//==================================================================================================

const Molecule::Molecule_properties Molecule::Molecules_table[] =
{
    {sf::Color::White      , 4, Units::MolarMass_H },
    {sf::Color::Magenta    , 4, Units::MolarMass_He},
    {sf::Color::Red        , 5, Units::MolarMass_N },
    {sf::Color::Blue       , 5, Units::MolarMass_O },
    {sf::Color::Yellow     , 5, Units::MolarMass_F },
    {sf::Color(252, 148, 3), 5, Units::MolarMass_Ne},
    {sf::Color::Green      , 6, Units::MolarMass_Cl},
    {sf::Color::Black      , 6, Units::MolarMass_Ar},
    {sf::Color::Cyan       , 7, Units::MolarMass_Kr},
    {sf::Color(252, 3, 227), 8, Units::MolarMass_Xe},
    {sf::Color(163, 28, 28), 9, Units::MolarMass_Rn},
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

                const sf::Color color = Molecules_table[type_].color;
                Vect3 curColor(k * color.r / 255.0, k * color.g / 255.0, k * color.b / 255.0);
                curSphere.setMaterial(curColor);

                double z = sqrt(SQR(radius) - SQR(x - pos0.x) - SQR(y - pos0.y));
                image -> setPixel(x, y, getPixelColor(&curSphere, light, vis, Vect3(x - pos0.x, y - pos0.y, z)));
            }
        }

    return EXIT_SUCCESS;
}

//------------------------------------CRINGE_MOMENT--------------------------------------------------------------------------------------

void Gas::collideMolecules(Molecule &a, Molecule &b)
{
    const double radius_a     = Molecule::Molecules_table[a.type_].radius.val_;
    const double radius_b     = Molecule::Molecules_table[b.type_].radius.val_;

    const double molar_mass_a = Molecule::Molecules_table[a.type_].molar_mass.val_;
    const double molar_mass_b = Molecule::Molecules_table[b.type_].molar_mass.val_;

    double dist = (b.getPosition() - a.getPosition()).len().val_;
    if (dist >= sqrt(SQR(radius_a) + SQR(radius_b)))
        return;

    Vect old_x_axis(1, 0);
    Vect old_y_axis(0, 1);

    Vect new_x_axis = !(a.position_.vect_ - b.position_.vect_);
    Vect new_y_axis(-new_x_axis.y, new_x_axis.x);

    Vect old_a_velocity((a.velocity_.vect_, new_x_axis), (a.velocity_.vect_, new_y_axis));
    Vect old_b_velocity((b.velocity_.vect_, new_x_axis), (b.velocity_.vect_, new_y_axis));

    printf("old_a_vel: (x = %lf, y = %lf, len = %lf)\n", old_a_velocity.x, old_a_velocity.y, old_a_velocity.len());
    printf("old_b_vel: (x = %lf, y = %lf, len = %lf)\n", old_b_velocity.x, old_b_velocity.y, old_b_velocity.len());

    Vect new_a_velocity = old_a_velocity + Vect(2*(b.velocity_.vect_.len() - a.velocity_.vect_.len())/(1.0 + molar_mass_a / molar_mass_b), 0);
    Vect new_b_velocity = old_b_velocity + Vect(2*(a.velocity_.vect_.len() - b.velocity_.vect_.len())/(1.0 + molar_mass_b / molar_mass_a), 0);

    printf("new_a_vel: (x = %lf, y = %lf)\n", new_a_velocity.x, new_a_velocity.y);
    printf("new_b_vel: (x = %lf, y = %lf)\n", new_b_velocity.x, new_b_velocity.y);

    a.velocity_.vect_ = Vect((new_a_velocity, old_x_axis), (new_a_velocity, old_y_axis));
    b.velocity_.vect_ = Vect((new_b_velocity, old_x_axis), (new_b_velocity, old_y_axis));

    printf("final a: (x = %lf, y = %lf)\n", a.velocity_.vect_.x, a.velocity_.vect_.y);
    printf("final b: (x = %lf, y = %lf)\n", b.velocity_.vect_.x, b.velocity_.vect_.y);
}

int Gas::collideWalls(Molecule &molecule) {

    const double radius = Molecule::Molecules_table[molecule.type_].radius.val_;

    if (molecule.getPosition().vect_.x < DownLeftCorner.x + radius) {
        molecule.velocity_.vect_.x *= -1;
        molecule.position_.vect_.x = DownLeftCorner.x + radius;

        return 1;
    }

    if (molecule.getPosition().vect_.x > UpRightCorner.x - radius) {
        molecule.velocity_.vect_.x *= -1;
        molecule.position_.vect_.x = UpRightCorner.x - radius;

        return 1;
    }

    if (molecule.position_.vect_.y > UpRightCorner.y - radius) {
        molecule.velocity_.vect_.y *= -1;
        molecule.position_.vect_.y = UpRightCorner.y - radius;

        return 1;
    }

    if (molecule.position_.vect_.y < DownLeftCorner.y + radius) {
        molecule.velocity_.vect_.y *= -1;
        molecule.position_.vect_.y = DownLeftCorner.y + radius;

        return 1;
    }

    return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------

int Gas::update(const double deltaTime) {
    for (auto& curMolecule : molecules)
        curMolecule.move(deltaTime);

    for (int firstPointer = 0; firstPointer < molecules.size(); firstPointer++) {
        for (int secondPointer = firstPointer + 1; secondPointer < molecules.size(); secondPointer++) {
            collideMolecules(molecules[firstPointer], molecules[secondPointer]);
        }
        collideWalls(molecules[firstPointer]);
    }

    return EXIT_SUCCESS;
}

int Gas::draw(sf::Image *image, Light *light, Vision *vision) {
    for (auto curMolecule : molecules)
        curMolecule.draw(image, light, vision);

    return EXIT_SUCCESS;
}
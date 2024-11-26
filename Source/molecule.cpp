#include "../Headers/Scene.h"
#include "../RayCasting/Headers/GraphicObjects.h"

#include <cmath>
#include <cassert>

//==================================================================================================

static Kelvin kinetic_energy_2_temperature(Virt_Joule kinetic_energy)
{
    return (2 * kinetic_energy) / (3 * Virt_kB);
}

//------------------------------------------------------------------------------------------------

const Molecule::Molecule_properties Molecule::Molecules_table[] =
{
    {sf::Color::White        , 4, MolarMass_H },
    {sf::Color::Magenta      , 4, MolarMass_He},
    {sf::Color::Red          , 5, MolarMass_N },
    {sf::Color::Blue         , 5, MolarMass_O },
    {sf::Color::Yellow       , 5, MolarMass_F },
    {sf::Color(252, 148,   3), 5, MolarMass_Ne},
    {sf::Color::Green        , 6, MolarMass_Cl},
    {sf::Color( 52, 235, 183), 6, MolarMass_Ar},
    {sf::Color::Cyan         , 7, MolarMass_Kr},
    {sf::Color(252,   3, 227), 8, MolarMass_Xe},
    {sf::Color(163,  28,  28), 9, MolarMass_Rn},
};

//------------------------------------------------------------------------------------------------

Molecule::Molecule(
    const MOLECULE_TYPE type,
    const VectVirt_m &DownLeftCorner, const VectVirt_m &UpRightCorner,
    const Virt_m_per_sec &MaxVelocity):
type_    (type),
velocity_(Vect::rand_unit_vect()),
position_(0, 0),
free_run_(0)
{
    assert(type_ >= 0 && type_ < NUM_MOLECULE_TYPE);

    const Virt_m     radius   = Molecules_table[type_].radius;
    const VectVirt_m RectSize = UpRightCorner - DownLeftCorner - VectVirt_m(2*radius, 2*radius);
    const VectVirt_m Offset(
        rand() % (unsigned long long) (RectSize.vect_.x + 1),
        rand() % (unsigned long long) (RectSize.vect_.y + 1)
    );

    position_  = DownLeftCorner + VectVirt_m(radius, radius) + Offset;
    velocity_ *= rand() % (unsigned long long) MaxVelocity;
}

//------------------------------------------------------------------------------------------------

Virt_Joule Molecule::get_kinetic_energy() const
{
    const Virt_g mass = Molecule::Molecules_table[type_].molar_mass / Virt_Na;
    return mass * velocity_.len() * velocity_.len() / 2000 /* Virt_g to Virt_kg */;
}

//------------------------------------------------------------------------------------------------

int Molecule::draw(sf::Image *image, Light *light, Vision *vis)
{
    catchNullptr(image, EXIT_FAILURE);
    catchNullptr(light, EXIT_FAILURE);
    catchNullptr( vis , EXIT_FAILURE);

    const Virt_m   radius = Molecules_table[type_].radius;
    const sf::Color color = Molecules_table[type_].color;

    Sphere curSphere(Vect3(position_.get_x(), position_.get_y(), 0), radius, Vect3(0.3, 0.3, 0.3));
    for (Virt_m x = position_.get_x() - radius; x <= position_.get_x() + radius; x.val_++)
        for (Virt_m y = position_.get_y() - radius; y <= position_.get_y() + radius; y.val_++)
        {
            if (SQR(x - position_.get_x()) + SQR(y - position_.get_y()) <= SQR(radius))
            {
                double k = 1 - (SQR(x - position_.get_x()) + SQR(y - position_.get_y())) / SQR(radius);
                k = (k > 1) ? 1 : k;

                Vect3 curColor(k * color.r / 255.0, k * color.g / 255.0, k * color.b / 255.0);
                curSphere.setMaterial(curColor);

                double z = sqrt(SQR(radius) - SQR(x - position_.get_x()) - SQR(y - position_.get_y()));
                image -> setPixel(x, y, getPixelColor(&curSphere, light, vis, Vect3(x - position_.get_x(), y - position_.get_y(), z)));
            }
        }

    return EXIT_SUCCESS;
}

void Gas::collideMolecules(Molecule &a, Molecule &b)
{
    const Virt_m   radius_a = Molecule::Molecules_table[a.type_].radius;
    const Virt_m   radius_b = Molecule::Molecules_table[b.type_].radius;

    VectVirt_m dist = a.position_ - b.position_;
    if (dist.len() > radius_a + radius_b)
        return;

    a.free_run_ = 0;
    b.free_run_ = 0;

    const g_per_mole mass_a = Molecule::Molecules_table[a.type_].molar_mass;
    const g_per_mole mass_b = Molecule::Molecules_table[b.type_].molar_mass;

    VectVirt_m main_x_axis(1, 0);
    VectVirt_m main_y_axis(0, 1);

    VectVirt_m tmp_x_axis = dist; !tmp_x_axis;
    VectVirt_m tmp_y_axis(tmp_x_axis.get_y(), -tmp_x_axis.get_x());

    VectVirt_m_per_sec a_velocity_tmp((tmp_x_axis, a.velocity_), (tmp_y_axis, a.velocity_));
    VectVirt_m_per_sec b_velocity_tmp((tmp_x_axis, b.velocity_), (tmp_y_axis, b.velocity_));

    VectVirt_m_per_sec a_velocity_tmp_delta(2*(b_velocity_tmp.get_x() - a_velocity_tmp.get_x()) / (1 + mass_a / mass_b), 0);
    VectVirt_m_per_sec b_velocity_tmp_delta(2*(a_velocity_tmp.get_x() - b_velocity_tmp.get_x()) / (1 + mass_b / mass_a), 0);

    a_velocity_tmp += a_velocity_tmp_delta;
    b_velocity_tmp += b_velocity_tmp_delta;

    a.velocity_.vect_.x = a_velocity_tmp.get_x() * (tmp_x_axis, main_x_axis) + a_velocity_tmp.get_y() * (tmp_y_axis, main_x_axis);
    a.velocity_.vect_.y = a_velocity_tmp.get_x() * (tmp_x_axis, main_y_axis) + a_velocity_tmp.get_y() * (tmp_y_axis, main_y_axis);

    b.velocity_.vect_.x = b_velocity_tmp.get_x() * (tmp_x_axis, main_x_axis) + b_velocity_tmp.get_y() * (tmp_y_axis, main_x_axis);
    b.velocity_.vect_.y = b_velocity_tmp.get_x() * (tmp_x_axis, main_y_axis) + b_velocity_tmp.get_y() * (tmp_y_axis, main_y_axis);
}

/* Накапливает в поле pressure изменение импульса.
 * После обработки всех столкновений нужно будет поделить на периметр и дельта-время, чтобы получить давление.
 */
void Gas::collideWalls(Molecule &molecule)
{
    const Virt_m radius = Molecule::Molecules_table[molecule.type_].radius;
    const Virt_g mass   = Molecule::Molecules_table[molecule.type_].molar_mass / Virt_Na;

    if (molecule.position_.get_x() < DownLeftCorner.get_x() + radius) {
        molecule.velocity_.vect_.x *= -1;
        molecule.position_.vect_.x = DownLeftCorner.get_x() + radius;

        pressure_ += 2 * mass * fabs(molecule.velocity_.get_x());
    }

    if (molecule.position_.get_x() > UpRightCorner.get_x() - radius) {
        molecule.velocity_.vect_.x *= -1;
        molecule.position_.vect_.x = UpRightCorner.get_x() - radius;

        pressure_ += 2 * mass * fabs(molecule.velocity_.get_x());
    }

    if (molecule.position_.get_y() > UpRightCorner.get_y() - radius) {
        molecule.velocity_.vect_.y *= -1;
        molecule.position_.vect_.y = UpRightCorner.get_y() - radius;

        pressure_ += 2 * mass * fabs(molecule.velocity_.get_y());
    }

    if (molecule.position_.get_y() < DownLeftCorner.get_y() + radius) {
        molecule.velocity_.vect_.y *= -1;
        molecule.position_.vect_.y = DownLeftCorner.get_y() + radius;

        pressure_ += 2 * mass * fabs(molecule.velocity_.get_y());
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------

void Gas::calc_temperature()
{
    Virt_Joule kinetic_energy = 0.0;

    for (unsigned type = 0; type < Molecule::NUM_MOLECULE_TYPE; ++type)
    {
        gas_groups[type].kinetic_energy = 0.0;
        gas_groups[type].temperature    = 0.0;
    }

    for (auto &curMolecule : molecules)
    {
        Virt_Joule cur_kinetic_energy = curMolecule.get_kinetic_energy();

        kinetic_energy += cur_kinetic_energy;
        gas_groups[curMolecule.type_].kinetic_energy += cur_kinetic_energy;
    }

    kinetic_energy /= molecules.size();
    temperature_ = kinetic_energy_2_temperature(kinetic_energy);

    for (unsigned type = 0; type < Molecule::NUM_MOLECULE_TYPE; ++type)
    {
        gas_groups[type].kinetic_energy /= (gas_groups[type].amount * Virt_Na);
        gas_groups[type].temperature     = kinetic_energy_2_temperature(gas_groups[type].kinetic_energy);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------

void Gas::calc_free_run()
{
    free_run_ = 0.0;

    for (auto &curMolecule : molecules)
        free_run_ += curMolecule.free_run_;

    free_run_ /= molecules.size();
}

//----------------------------------------------------------------------------------------------------------------------------------------

void Gas::addMolecule(const Molecule::MOLECULE_TYPE type, const Virt_mole amount, const Virt_m_per_sec &MaxVelocity)
{
    amount_ += amount;
    gas_groups[type].amount += amount;
    for (double cnt = 0; cnt < amount * Virt_Na; ++cnt)
        molecules.emplace_back(type, DownLeftCorner, UpRightCorner, MaxVelocity);
}

int Gas::update(const Virt_sec deltaTime) {
    for (auto& curMolecule : molecules)
        curMolecule.move(deltaTime);

    for (int first_idx = 0; first_idx < molecules.size(); first_idx++) {
        for (int second_idx = first_idx + 1; second_idx < molecules.size(); second_idx++) {
            collideMolecules(molecules[first_idx], molecules[second_idx]);
        }
        collideWalls(molecules[first_idx]);
    }

    pressure_ /= (perimeter * deltaTime);
    calc_temperature();
    calc_free_run();

    return EXIT_SUCCESS;
}

int Gas::draw(sf::Image *image, Light *light, Vision *vision) {
    for (auto curMolecule : molecules)
        curMolecule.draw(image, light, vision);

    return EXIT_SUCCESS;
}

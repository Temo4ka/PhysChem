#ifndef PHYSICS_H
#define PHYSICS_H

#include "Vect.h"

//==================================================================================================

#define TYPEDEF_SCALAR(type_name)   \
    struct type_name                \
    {                               \
        type_name(double val):      \
        val_(val)                   \
        {}                          \
                                    \
        double val_;                \
    };

#define TYPEDEF_VECTOR(type_name)   \
    TYPEDEF_SCALAR(type_name)       \
                                    \
    struct Vect##type_name          \
    {                               \
        Vect##type_name(const Vect &vect): \
        vect_(vect)                 \
        {}                          \
                                    \
        Vect##type_name(double x, double y): \
        vect_(x, y)                 \
        {}                          \
                                    \
        Vect vect_;                 \
    };

#define SCALAR_PHYS_2_VIRT(unit_name, unit_value)   \
    static Virt_##unit_name Phys2Virt_##unit_name(const Phys_##unit_name val) { return (1.0 / (unit_value)) * val.val_; }   \
    static Phys_##unit_name Virt2Phys_##unit_name(const Virt_##unit_name val) { return (unit_value)         * val.val_; }

#define VECTOR_PHYS_2_VIRT(unit_name, unit_value)   \
    SCALAR_PHYS_2_VIRT(unit_name, unit_value)       \
                                                    \
    static VectVirt_##unit_name VectPhys2Virt_##unit_name(const VectPhys_##unit_name vect) { return (1.0 / (unit_value)) * vect.vect_; }    \
    static VectPhys_##unit_name VectVirt2Phys_##unit_name(const VectVirt_##unit_name vect) { return (unit_value)         * vect.vect_; }

class Units
{
public:
    TYPEDEF_SCALAR(Phys_mole)
    TYPEDEF_SCALAR(Virt_mole)

    SCALAR_PHYS_2_VIRT(mole, MOLE_UNIT)

    //--------------------------------------------------------------------------------------------------

    TYPEDEF_SCALAR(Phys_per_mole)
    TYPEDEF_SCALAR(Virt_per_mole)

    SCALAR_PHYS_2_VIRT(per_mole, 1.0 / MOLE_UNIT)

    static const Phys_per_mole Phys_Na;
    static const Virt_per_mole Virt_Na;

    //--------------------------------------------------------------------------------------------------

    TYPEDEF_SCALAR(Phys_g)
    TYPEDEF_SCALAR(Virt_g)

    SCALAR_PHYS_2_VIRT(g, MASS_UNIT)

    //--------------------------------------------------------------------------------------------------

    /*!!!
     * Виртуальная и физическая температуры одинаковы, потому что так хотим.
     */
    TYPEDEF_SCALAR(Kelvin)
    TYPEDEF_SCALAR(Celsius)

    static Kelvin  Celsius2Kelvin(const Celsius val) { return val.val_ - CELSIUS_OFFSET; }
    static Celsius Kelvin2Celsius(const Kelvin  val) { return val.val_ + CELSIUS_OFFSET; }

    //--------------------------------------------------------------------------------------------------

    /*!!!
     * Мы хотим, чтобы виртуальная и физическая молярные массы были одинаковы.
     * Для этого мы делаем (MASS_UNIT) и (MOLE_UNIT) одинаковыми.
     */
    TYPEDEF_SCALAR(g_per_mole)

    #define MOLAR_MASS(gas_name)    \
        static const g_per_mole MolarMass_##gas_name;

    MOLAR_MASS(H)
    MOLAR_MASS(He)
    MOLAR_MASS(N)
    MOLAR_MASS(O)
    MOLAR_MASS(F)
    MOLAR_MASS(Ne)
    MOLAR_MASS(Cl)
    MOLAR_MASS(Ar)
    MOLAR_MASS(Kr)
    MOLAR_MASS(Xe)
    MOLAR_MASS(Rn)

    #undef MOLAR_MASS

    //--------------------------------------------------------------------------------------------------

    TYPEDEF_VECTOR(Phys_m)
    TYPEDEF_VECTOR(Virt_m) // пиксели

    VECTOR_PHYS_2_VIRT(m, DISTANCE_UNIT)

    //--------------------------------------------------------------------------------------------------

    TYPEDEF_SCALAR(Phys_m2)
    TYPEDEF_SCALAR(Virt_m2)

    SCALAR_PHYS_2_VIRT(m2, DISTANCE_UNIT * DISTANCE_UNIT)

    //--------------------------------------------------------------------------------------------------

    TYPEDEF_SCALAR(Phys_m3)
    TYPEDEF_SCALAR(Virt_m3)

    SCALAR_PHYS_2_VIRT(m3, DISTANCE_UNIT * DISTANCE_UNIT * DISTANCE_UNIT)

    //--------------------------------------------------------------------------------------------------

    TYPEDEF_SCALAR(Phys_sec)
    TYPEDEF_SCALAR(Virt_sec)

    SCALAR_PHYS_2_VIRT(sec, TIME_UNIT)

    //--------------------------------------------------------------------------------------------------

    TYPEDEF_VECTOR(Phys_m_per_sec)
    TYPEDEF_VECTOR(Virt_m_per_sec) // пиксели в секунду

    VECTOR_PHYS_2_VIRT(m_per_sec, VELOCITY_UNIT)

    //--------------------------------------------------------------------------------------------------

    TYPEDEF_SCALAR(Phys_Joule)
    TYPEDEF_SCALAR(Virt_Joule)

    SCALAR_PHYS_2_VIRT(Joule, JOULE_UNIT)

    //--------------------------------------------------------------------------------------------------

    TYPEDEF_SCALAR(Phys_Joule_per_Kelvin)
    TYPEDEF_SCALAR(Virt_Joule_per_Kelvin)

    SCALAR_PHYS_2_VIRT(Joule_per_Kelvin, JOULE_UNIT)

    static const Phys_Joule_per_Kelvin Phys_kB;
    static const Virt_Joule_per_Kelvin Virt_kB;

    //--------------------------------------------------------------------------------------------------

    TYPEDEF_SCALAR(Phys_Joule_per_mole_Kelvin)
    TYPEDEF_SCALAR(Virt_Joule_per_mole_Kelvin)

    SCALAR_PHYS_2_VIRT(Joule_per_mole_Kelvin, JOULE_UNIT / MOLE_UNIT)

    //--------------------------------------------------------------------------------------------------

    TYPEDEF_VECTOR(Phys_Newton)
    TYPEDEF_VECTOR(Virt_Newton)

    VECTOR_PHYS_2_VIRT(Newton, NEWTON_UNIT)

    //--------------------------------------------------------------------------------------------------

    TYPEDEF_SCALAR(Phys_Pascal)
    TYPEDEF_SCALAR(Virt_Pascal)

    SCALAR_PHYS_2_VIRT(Pascal, NEWTON_UNIT / (DISTANCE_UNIT * DISTANCE_UNIT))

    //--------------------------------------------------------------------------------------------------

private:
    // 1 Virt_mole = (MOLE_UNIT) Phys_mole
    static constexpr double MOLE_UNIT = (1e22 /* кол-во моделей в жизни */) / (1.0 /* кол-во молекул в модели */);

    // 1 Virt_g = (MASS_UNIT) Phys_g
    static constexpr double MASS_UNIT = (MOLE_UNIT) /*!!! необходимо, чтобы физическая и виртуальная молярные массы были одинаковы */;

    // Celsius = Kelvin + (CELSIUS_OFFSET)
    static constexpr double CELSIUS_OFFSET = -273.15;

    // 1 Virt_m = (DISTANCE_UNIT) Phys_m
    static constexpr double DISTANCE_UNIT = (1.0 /* метр */) / (1000.0 /* пиксели */);

    // 1 Virt_m_per_sec = (VELOCITY_UNIT) Phys_m_per_sec
    static constexpr double VELOCITY_UNIT = (752.85 /* пиксели в секунду */) / (5.0 /* скорость молекулы углерода при 0 по цельсию, метры в cекунду */);

    // 1 Virt_sec = (TIME_UNIT) Phys_sec
    static constexpr double TIME_UNIT = DISTANCE_UNIT / VELOCITY_UNIT;

    // 1 Virt_Joule = (JOULE_UNIT) Phys_Joule
    static constexpr double JOULE_UNIT = (MASS_UNIT * VELOCITY_UNIT * VELOCITY_UNIT);

    // 1 Virt_Newton = (NEWTON_UNIT) Phys_Newton
    static constexpr double NEWTON_UNIT = (JOULE_UNIT / DISTANCE_UNIT);
};

#undef TYPEDEF_SCALAR
#undef TYPEDEF_VECTOR

#undef SCALAR_PHYS_2_VIRT
#undef VECTOR_PHYS_2_VIRT

//==================================================================================================

#define SCALAR_UNIT_ALIAS(unit_name)    \
    using unit_name = Units::unit_name;

#define VECTOR_UNIT_ALIAS(unit_name)    \
    SCALAR_UNIT_ALIAS(unit_name)        \
    using Vect##unit_name = Units::Vect##unit_name;

SCALAR_UNIT_ALIAS(Phys_mole)
SCALAR_UNIT_ALIAS(Virt_mole)

SCALAR_UNIT_ALIAS(Phys_per_mole)
SCALAR_UNIT_ALIAS(Virt_per_mole)

SCALAR_UNIT_ALIAS(Phys_g)
SCALAR_UNIT_ALIAS(Virt_g)

SCALAR_UNIT_ALIAS(Kelvin)
SCALAR_UNIT_ALIAS(Celsius)

SCALAR_UNIT_ALIAS(g_per_mole)

VECTOR_UNIT_ALIAS(Phys_m)
VECTOR_UNIT_ALIAS(Virt_m)

SCALAR_UNIT_ALIAS(Phys_m2)
SCALAR_UNIT_ALIAS(Virt_m2)

SCALAR_UNIT_ALIAS(Phys_m3)
SCALAR_UNIT_ALIAS(Virt_m3)

SCALAR_UNIT_ALIAS(Phys_sec)
SCALAR_UNIT_ALIAS(Virt_sec)

VECTOR_UNIT_ALIAS(Phys_m_per_sec)
VECTOR_UNIT_ALIAS(Virt_m_per_sec)

SCALAR_UNIT_ALIAS(Phys_Joule)
SCALAR_UNIT_ALIAS(Virt_Joule)

SCALAR_UNIT_ALIAS(Phys_Joule_per_Kelvin)
SCALAR_UNIT_ALIAS(Virt_Joule_per_Kelvin)

SCALAR_UNIT_ALIAS(Phys_Joule_per_mole_Kelvin)
SCALAR_UNIT_ALIAS(Virt_Joule_per_mole_Kelvin)

VECTOR_UNIT_ALIAS(Phys_Newton)
VECTOR_UNIT_ALIAS(Virt_Newton)

SCALAR_UNIT_ALIAS(Phys_Pascal)
SCALAR_UNIT_ALIAS(Virt_Pascal)

#undef SCALAR_UNIT_ALIAS
#undef VECTOR_UNIT_ALIAS

//==================================================================================================

#endif // PHYSICS_H

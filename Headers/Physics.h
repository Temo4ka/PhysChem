#ifndef PHYSICS_H
#define PHYSICS_H

#include "Vect.h"

#define TYPEDEF_SCALAR(type_name)   \
    struct type_name                \
    {                               \
        type_name():                \
        val_(0.0)                   \
        {}                          \
                                    \
        type_name(double val):      \
        val_(val)                   \
        {}                          \
                                    \
        operator double() const     \
        {                           \
            return val_;            \
        }                           \
                                    \
        type_name& operator +=(const type_name &other) \
        {                           \
            val_ += other.val_;     \
            return *this;           \
        }                           \
                                    \
	    type_name& operator -=(const type_name &other) \
        {                           \
            val_ -= other.val_;     \
            return *this;           \
        }                           \
                                    \
        type_name& operator *=(const double scalar) \
        {                           \
            val_ *= scalar;         \
            return *this;           \
        }                           \
                                    \
        type_name& operator /=(const double scalar) \
        {                           \
            val_ /= scalar;         \
            return *this;           \
        }                           \
                                    \
        double val_;                \
    };                              \
    inline type_name operator +(const type_name &a, const type_name &b) \
    {                               \
        return a.val_ + b.val_;     \
    }                               \
                                    \
    inline type_name operator -(const type_name &a, const type_name &b) \
    {                               \
        return a.val_ - b.val_;     \
    }

#define TYPEDEF_VECTOR(type_name)   \
    TYPEDEF_SCALAR(type_name)       \
                                    \
    struct Vect##type_name          \
    {                               \
        Vect##type_name():          \
        vect_()                     \
        {}                          \
                                    \
        Vect##type_name(const Vect &vect): \
        vect_(vect)                 \
        {}                          \
                                    \
        Vect##type_name(type_name x, type_name y): \
        vect_(x.val_, y.val_)       \
        {}                          \
                                    \
        type_name len() const       \
        {                           \
            return vect_.len();     \
        }                           \
                                    \
        type_name get_x() const     \
        {                           \
            return vect_.x;         \
        }                           \
                                    \
        type_name get_y() const     \
        {                           \
            return vect_.y;         \
        }                           \
                                    \
        operator Vect() const       \
        {                           \
            return vect_;           \
        }                           \
                                    \
                                    \
        Vect##type_name& operator +=(const Vect##type_name &other) \
        {                           \
            vect_ += other.vect_;   \
            return *this;           \
        }                           \
                                    \
	    Vect##type_name& operator -=(const Vect##type_name &other) \
        {                           \
            vect_ -= other.vect_;   \
            return *this;           \
        }                           \
                                    \
        Vect##type_name& operator *=(const double scalar) \
        {                           \
            vect_ *= scalar;        \
            return *this;           \
        }                           \
                                    \
        Vect##type_name& operator /=(const double scalar) \
        {                           \
            vect_ /= scalar;        \
            return *this;           \
        }                           \
                                    \
        Vect##type_name& operator -() \
        {                           \
            vect_ = -vect_;         \
            return *this;           \
        }                           \
                                    \
        Vect##type_name& operator !() \
        {                           \
            vect_ = !vect_;         \
            return *this;           \
        }                           \
                                    \
        Vect vect_;                 \
    };                              \
                                    \
    inline Vect##type_name operator +(const Vect##type_name &a, const Vect##type_name &b) \
    {                               \
        return a.vect_ + b.vect_;   \
    }                               \
                                    \
    inline Vect##type_name operator -(const Vect##type_name &a, const Vect##type_name &b) \
    {                               \
        return a.vect_ - b.vect_;   \
    }

#define SCALAR_PHYS_2_VIRT(unit_name, unit_value)   \
    inline Virt_##unit_name Phys2Virt_##unit_name(const Phys_##unit_name val) { return (1.0 / (unit_value)) * val.val_; }   \
    inline Phys_##unit_name Virt2Phys_##unit_name(const Virt_##unit_name val) { return (unit_value)         * val.val_; }

#define VECTOR_PHYS_2_VIRT(unit_name, unit_value)   \
    SCALAR_PHYS_2_VIRT(unit_name, unit_value)       \
                                                    \
    inline VectVirt_##unit_name VectPhys2Virt_##unit_name(const VectPhys_##unit_name vect) { return (1.0 / (unit_value)) * vect.vect_; }    \
    inline VectPhys_##unit_name VectVirt2Phys_##unit_name(const VectVirt_##unit_name vect) { return (unit_value)         * vect.vect_; }

//==================================================================================================

namespace Units
{
    namespace detail
    {
        // 1 Virt_mole = (MOLE_UNIT) Phys_mole
        static constexpr double MOLE_UNIT = (1.0 /* кол-во молекул в модели */) / (1e22 /* кол-во моделей в жизни */);

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
    }

    TYPEDEF_SCALAR(Phys_mole)
    TYPEDEF_SCALAR(Virt_mole)

    SCALAR_PHYS_2_VIRT(mole, detail::MOLE_UNIT)

    //--------------------------------------------------------------------------------------------------

    TYPEDEF_SCALAR(Phys_per_mole)
    TYPEDEF_SCALAR(Virt_per_mole)

    SCALAR_PHYS_2_VIRT(per_mole, 1.0 / detail::MOLE_UNIT)

    extern const Phys_per_mole Phys_Na;
    extern const Virt_per_mole Virt_Na;

    //--------------------------------------------------------------------------------------------------

    TYPEDEF_SCALAR(Phys_g)
    TYPEDEF_SCALAR(Virt_g)

    SCALAR_PHYS_2_VIRT(g, detail::MASS_UNIT)

    //--------------------------------------------------------------------------------------------------

    /*!!!
     * Виртуальная и физическая температуры одинаковы, потому что так хотим.
     */
    TYPEDEF_SCALAR(Kelvin)
    TYPEDEF_SCALAR(Celsius)

    static Kelvin  Celsius2Kelvin(const Celsius val) { return val.val_ - detail::CELSIUS_OFFSET; }
    static Celsius Kelvin2Celsius(const Kelvin  val) { return val.val_ + detail::CELSIUS_OFFSET; }

    //--------------------------------------------------------------------------------------------------

    /*!!!
     * Мы хотим, чтобы виртуальная и физическая молярные массы были одинаковы.
     * Для этого мы делаем (MASS_UNIT) и (MOLE_UNIT) одинаковыми.
     */
    TYPEDEF_SCALAR(g_per_mole)

#define MOLAR_MASS(gas_name, mass_value)    \
    static const g_per_mole MolarMass_##gas_name = mass_value;

    MOLAR_MASS(H , 1.008)
    MOLAR_MASS(He, 4.0026)
    MOLAR_MASS(N , 14.007)
    MOLAR_MASS(O , 15.999)
    MOLAR_MASS(F , 18.998)
    MOLAR_MASS(Ne, 20.180)
    MOLAR_MASS(Cl, 35.45)
    MOLAR_MASS(Ar, 39.948)
    MOLAR_MASS(Kr, 83.798)
    MOLAR_MASS(Xe, 131.29)
    MOLAR_MASS(Rn, 222)

#undef MOLAR_MASS

    //--------------------------------------------------------------------------------------------------

    TYPEDEF_VECTOR(Phys_m)
    TYPEDEF_VECTOR(Virt_m) // пиксели

    VECTOR_PHYS_2_VIRT(m, detail::DISTANCE_UNIT)

    //--------------------------------------------------------------------------------------------------

    TYPEDEF_SCALAR(Phys_m2)
    TYPEDEF_SCALAR(Virt_m2)

    SCALAR_PHYS_2_VIRT(m2, detail::DISTANCE_UNIT * detail::DISTANCE_UNIT)

    //--------------------------------------------------------------------------------------------------

    TYPEDEF_SCALAR(Phys_per_m2)
    TYPEDEF_SCALAR(Virt_per_m2)

    SCALAR_PHYS_2_VIRT(per_m2, 1 / (detail::DISTANCE_UNIT * detail::DISTANCE_UNIT))

    //--------------------------------------------------------------------------------------------------

    TYPEDEF_SCALAR(Phys_sec)
    TYPEDEF_SCALAR(Virt_sec)

    SCALAR_PHYS_2_VIRT(sec, detail::TIME_UNIT)

    //--------------------------------------------------------------------------------------------------

    TYPEDEF_VECTOR(Phys_m_per_sec)
    TYPEDEF_VECTOR(Virt_m_per_sec) // пиксели в секунду

    VECTOR_PHYS_2_VIRT(m_per_sec, detail::VELOCITY_UNIT)

    //--------------------------------------------------------------------------------------------------

    TYPEDEF_SCALAR(Phys_Joule)
    TYPEDEF_SCALAR(Virt_Joule)

    SCALAR_PHYS_2_VIRT(Joule, detail::JOULE_UNIT)

    //--------------------------------------------------------------------------------------------------

    TYPEDEF_SCALAR(Phys_Joule_per_Kelvin)
    TYPEDEF_SCALAR(Virt_Joule_per_Kelvin)

    SCALAR_PHYS_2_VIRT(Joule_per_Kelvin, detail::JOULE_UNIT)

    extern const Phys_Joule_per_Kelvin Phys_kB;
    extern const Virt_Joule_per_Kelvin Virt_kB;

    //--------------------------------------------------------------------------------------------------

    TYPEDEF_SCALAR(Phys_Joule_per_mole_Kelvin)
    TYPEDEF_SCALAR(Virt_Joule_per_mole_Kelvin)

    SCALAR_PHYS_2_VIRT(Joule_per_mole_Kelvin, detail::JOULE_UNIT / detail::MOLE_UNIT)

    //--------------------------------------------------------------------------------------------------

    TYPEDEF_VECTOR(Phys_Newton)
    TYPEDEF_VECTOR(Virt_Newton)

    VECTOR_PHYS_2_VIRT(Newton, detail::NEWTON_UNIT)

    //--------------------------------------------------------------------------------------------------

    TYPEDEF_SCALAR(Phys_Newton_per_m)
    TYPEDEF_SCALAR(Virt_Newton_per_m)

    SCALAR_PHYS_2_VIRT(Newton_per_m, detail::NEWTON_UNIT / detail::DISTANCE_UNIT)
}

//==================================================================================================

#undef TYPEDEF_SCALAR
#undef TYPEDEF_VECTOR

#undef SCALAR_PHYS_2_VIRT
#undef VECTOR_PHYS_2_VIRT

#endif // PHYSICS_H

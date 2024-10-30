#ifndef PHYSICS_H
#define PHYSICS_H

#include "Vect.h"

#define TYPEDEF_DOUBLE(type_name)   \
    struct type_name                \
    {                               \
        type_name(double val):      \
        val_(val)                   \
        {}                          \
                                    \
        double val_;                \
    };

#define TYPEDEF_VECTOR(type_name)   \
    TYPEDEF_DOUBLE(type_name)       \
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

//==================================================================================================

TYPEDEF_DOUBLE(P_per_mole)
static const P_per_mole Na = 6.02e23;

TYPEDEF_DOUBLE(P_J_per_K)
static const P_J_per_K k_b = 1.38e-23;

TYPEDEF_DOUBLE(P_g_per_mole)
static const P_g_per_mole Carbon_molar_mass = 12;

TYPEDEF_VECTOR(P_m_per_sec)
// пиксели в секунду
TYPEDEF_VECTOR(V_m_per_sec)

// 1 V_m_per_sec = (VELOCITY_UNIT) P_m_per_sec
#define VELOCITY_UNIT ((5 /* пикселей в секунду */) / (753.2 /* скорость молекулы углерода при 0 по цельсию */))

inline V_m_per_sec P2V_m_per_sec(const P_m_per_sec val) { return VELOCITY_UNIT       * val.val_; }
inline P_m_per_sec V2P_m_per_sec(const V_m_per_sec val) { return (1 / VELOCITY_UNIT) * val.val_; }

inline VectV_m_per_sec VectP2V_m_per_sec(const VectP_m_per_sec vect) { return VELOCITY_UNIT       * vect.vect_; }
inline VectP_m_per_sec VectV2P_m_per_sec(const VectV_m_per_sec vect) { return (1 / VELOCITY_UNIT) * vect.vect_; }

#undef VELOCITY_UNIT

//==================================================================================================

#undef TYPEDEF_DOUBLE
#undef TYPEDEF_VECTOR

#endif // PHYSICS_H

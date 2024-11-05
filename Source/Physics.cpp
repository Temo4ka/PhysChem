#include "../Headers//Physics.h"

const Units::Phys_per_mole Units        ::Phys_Na = 6.02e23;
const Units::Virt_per_mole Units        ::Virt_Na = Phys2Virt_per_mole(Phys_Na);

const Units::Phys_Joule_per_Kelvin Units::Phys_kB = 1.38e-23;
const Units::Virt_Joule_per_Kelvin Units::Virt_kB = Phys2Virt_Joule_per_Kelvin(Phys_kB);

#define MOLAR_MASS(gas_name, mass_value)    \
    const Units::g_per_mole Units::MolarMass_##gas_name = mass_value;

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

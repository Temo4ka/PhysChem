#include "../Headers//Physics.h"

const Units::Phys_per_mole              Units::Phys_Na = 6.02e23;
const Units::Virt_per_mole              Units::Virt_Na = Phys2Virt_per_mole(Phys_Na);

const Units::Phys_Joule_per_Kelvin      Units::Phys_kB = 1.38e-23;
const Units::Virt_Joule_per_Kelvin      Units::Virt_kB = Phys2Virt_Joule_per_Kelvin(Phys_kB);

const Units::Phys_Joule_per_mole_Kelvin Units::Phys_R  = Units::Phys_Na * Units::Phys_kB;
const Units::Virt_Joule_per_mole_Kelvin Units::Virt_R  = Phys2Virt_Joule_per_mole_Kelvin(Phys_R);

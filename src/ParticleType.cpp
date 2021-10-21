#include "ParticleType.hpp"
ParticleType::ParticleType(const char* name, double mass, int charge)
    : name_{name}, mass_{mass}, charge_{charge} {}
ParticleType::ParticleType(ParticleType& type)
    : name_{type.getName()}, mass_{type.getMass()}, charge_{type.getCharge()} {}
void ParticleType::print() const {
  std::cout << "Name: " << name_ << " Mass: " << mass_ << " Charge: " << charge_
            << '\n';
}

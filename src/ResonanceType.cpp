#include "ResonanceType.hpp"
ResonanceType::ResonanceType(const char* name, double mass, int charge,
                             double width)
    : ParticleType{name, mass, charge}, width_{width} {}
ResonanceType::ResonanceType(ResonanceType& type)
    : ParticleType{type.getName(), type.getMass(), type.getCharge()},
      width_{type.getWidth()} {}
void ResonanceType::print() const {
  ParticleType::print();
  std::cout << " Width: " << width_ << '\n';
}

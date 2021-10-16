#include "ParticleType.hpp"
#include "ResonanceType.hpp"

int main() {
  ParticleType particle{"Particella", 1.7, 1};
  particle.print();
  ResonanceType resonance{"Risonanza", 2.5, -1, 0.7};
  resonance.print();
  std::cout << resonance.getName() << ' ' << resonance.getMass() << ' '
            << resonance.getCharge() << ' ' << resonance.getWidth() << '\n';
  ParticleType* particelle[2];
  particelle[0] = new ParticleType{"Protone", 0.5, 2};
  particelle[1] = new ResonanceType{"Muone", 0.5, 2, 1.33};
  for (int i = 0; i != 2; ++i) {
    particelle[i]->print();
  }

  /*ParticleType protone{"protone", 938., 1};
  ParticleType elettrone{"elettrone", 0.5109, -1};
  ParticleType muone{"muone", 105, -1};
  ParticleType pione{"pione", 139.6, 1};
  ParticleType neutrone{"neutrone", 939.56, 0};
  Particle::particleType.push_back(&protone);
  Particle::particleType.push_back(&elettrone);
  Particle::particleType.push_back(&muone);
  Particle::particleType.push_back(&pione);
  Particle::particleType.push_back(&neutrone);
  Particle particell{"muone", 1., 1., 1.};
  std::cout << particell.getIndex();*/
}

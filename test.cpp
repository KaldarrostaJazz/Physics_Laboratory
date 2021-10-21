#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "Particle.hpp"
#include "ParticleType.hpp"
#include "ResonanceType.hpp"
#include "doctest.h"

TEST_CASE("ParticleType, ResonanceType") {
  ParticleType particle{"Particella", 1.7, 1};
  ResonanceType resonance{"Risonanza", 2.5, -1, 0.7};
  ParticleType* particelle[2];
  particelle[0] = &particle;
  particelle[1] = &resonance;
  particelle[0]->print();
  particelle[1]->print();
  std::cout << std::endl;

  CHECK(particle.getName() == "Particella");
  CHECK(particle.getMass() == 1.7);
  CHECK(particle.getCharge() == 1);
  CHECK(resonance.getName() == "Risonanza");
  CHECK(resonance.getMass() == 2.5);
  CHECK(resonance.getCharge() == -1);
  CHECK(resonance.getWidth() == 0.7);
}

TEST_CASE("Particle: addType on the heap") {
  Particle::addType("Protone", 938.272, 1);
  Particle::addType("Elettrone", 0.511, -1);
  Particle::addType("Neutrone", 939.565, 0);
  Particle::addType("Pione+", 139.6, 1, 6.11);
  Particle::addType("Pione-", 139.6, -1, 6.11);
  Particle::addType("Kaone", 497.648, 0, 19.23);

  CHECK_THROWS(Particle::addType("Protone", 12.3, 2, 4.5));
}

TEST_CASE("Particles properties") {
  Particle particella_1{"Protone", 1., 1., 1.};
  Particle particella_2{"Elettrone", 1., 1., 1.};
  Particle particella_3{"Neutrone", 1., 1., 1.};
  Particle particella_4{"Pione+", 1., 1., 1.};
  Particle particella_5{"Pione-", 1., 1., 1.};
  Particle particella_6{"Kaone", 1., 1., 1.};

  particella_1.print();
  particella_2.print();
  particella_3.print();
  particella_4.print();
  particella_5.print();
  particella_6.print();
  std::cout << std::endl;

  CHECK(particella_1.getIndex() == 0);
  CHECK(particella_2.getIndex() == 1);
  CHECK(particella_3.getIndex() == 2);
  CHECK(particella_4.getIndex() == 3);
  CHECK(particella_5.getIndex() == 4);
  CHECK(particella_6.getIndex() == 5);

  CHECK(particella_4.getMass() == doctest::Approx(139.6));
  CHECK(particella_2.getEnergy() == doctest::Approx(1.805857414));

  particella_2.setIndex("Kaone");
  CHECK(particella_2.getIndex() == 5);

  CHECK_THROWS(particella_1.setIndex(11));
  CHECK_THROWS(particella_1.setIndex("StdExcept"));

  particella_5.setP(2., 3.4, 0.6);
  CHECK(particella_5.getPx() == doctest::Approx(2.));
  CHECK(particella_5.getPy() == doctest::Approx(3.4));
  CHECK(particella_5.getPz() == doctest::Approx(0.6));
}

TEST_CASE("pTypes properties") {
  CHECK(Particle::getNumTypes() == 6);

  CHECK(Particle::getPType(0)->getName() == "Protone");
  CHECK(Particle::getPType(1)->getName() == "Elettrone");
  CHECK(Particle::getPType(2)->getName() == "Neutrone");
  CHECK(Particle::getPType(3)->getName() == "Pione+");
  CHECK(Particle::getPType(4)->getName() == "Pione-");
  CHECK(Particle::getPType(5)->getName() == "Kaone");

  CHECK(Particle::getPType(0)->getMass() == doctest::Approx(938.272));
  CHECK(Particle::getPType(1)->getMass() == doctest::Approx(0.511));
  CHECK(Particle::getPType(2)->getMass() == doctest::Approx(939.565));
  CHECK(Particle::getPType(3)->getMass() == doctest::Approx(139.6));
  CHECK(Particle::getPType(4)->getMass() == doctest::Approx(139.6));
  CHECK(Particle::getPType(5)->getMass() == doctest::Approx(497.648));

  CHECK(Particle::getPType(0)->getCharge() == 1);
  CHECK(Particle::getPType(1)->getCharge() == -1);
  CHECK(Particle::getPType(2)->getCharge() == 0);
  CHECK(Particle::getPType(3)->getCharge() == 1);
  CHECK(Particle::getPType(4)->getCharge() == -1);
  CHECK(Particle::getPType(5)->getCharge() == 0);

  Particle::printTypes();
  std::cout << std::endl;
}

TEST_CASE("addType from reference") {
  ResonanceType muone{"Muone", 105.6, -1, 0.457};
  ParticleType tauone{"Tauone", 1776.86, -1};
  Particle::addType(muone);
  Particle::addType(tauone);

  CHECK(Particle::getNumTypes() == 8);

  CHECK(Particle::getPType(6)->getName() == "Muone");
  CHECK(Particle::getPType(7)->getName() == "Tauone");
  CHECK(Particle::getPType(6)->getMass() == doctest::Approx(105.6));
  CHECK(Particle::getPType(7)->getMass() == doctest::Approx(1776.86));
  CHECK(Particle::getPType(6)->getCharge() == -1);
  CHECK(Particle::getPType(7)->getCharge() == -1);

  Particle::printTypes();
  std::cout << std::endl;
}

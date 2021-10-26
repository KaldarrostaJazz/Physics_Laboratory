#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <cmath>
#include <cstdlib>
#include <string>

#include "ResonanceType.hpp"

class Particle {
 public:
  // Constructor /////
  Particle();
  Particle(const char* name, double px, double py, double pz);
  Particle(Particle& p);
  ////////////////////

  // Operator = //////
  Particle& operator=(const Particle& other);
  ////////////////////

  // Decay method ////
  int decayTo(Particle& p1, Particle& p2) const;
  ////////////////////

  // Getters /////////
  int getIndex() const { return index_; }
  double getPx() const { return px_; }
  double getPy() const { return py_; }
  double getPz() const { return pz_; }
  double getP() const { return std::sqrt(px_ * px_ + py_ * py_ + pz_ * pz_); }
  double getMass() const { return pTypes[index_]->getMass(); }
  double getEnergy() const;
  double getInvMass(Particle& particle);
  static int getNumTypes() { return numTypes; }
  static ParticleType* getPType(int index) { return pTypes[index]; }
  ////////////////////

  // Setters /////////
  void setIndex(int index);
  void setIndex(const char* name);
  void setP(double px, double py, double pz);
  ////////////////////

  // Static methods //
  static void addType(const char* name, double mass, int charge,
                      double width = 0.);
  static void addType(ParticleType& newType);
  static void addType(ResonanceType& newType);
  ////////////////////

  // Printers ////////
  void print() const;
  static void printTypes();
  ////////////////////

 private:
  static const int maxTypes;
  static ParticleType* pTypes[];
  static int numTypes;

  static int findType(const char* name);

  void boost(double bx, double by, double bz);

  int index_;
  double px_{0.};
  double py_{0.};
  double pz_{0.};
};
inline Particle& Particle::operator=(const Particle& other) {
  this->index_ = other.getIndex();
  this->px_ = other.getPx();
  this->py_ = other.getPy();
  this->pz_ = other.getPz();
  return *this;
}
#endif

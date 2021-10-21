#ifndef PARTICLETYPE_HPP
#define PARTICLETYPE_HPP
#include <exception>
#include <iostream>
class ParticleType {
 public:
  ParticleType(const char* name, double mass, int charge);
  ParticleType(ParticleType& type);
  const char* getName() const { return name_; }
  double getMass() const { return mass_; }
  int getCharge() const { return charge_; }
  virtual double getWidth() const { return 0; }
  virtual void print() const;

 private:
  const char* name_;
  const double mass_;
  const int charge_;
};
#endif

#ifndef RESONANCETYPE_HPP
#define RESONANCETYPE_HPP
#include "ParticleType.hpp"

class ResonanceType : public ParticleType {
 public:
  ResonanceType(const char* name, double mass, int charge, double width);
  ResonanceType(ResonanceType& type);
  double getWidth() const { return width_; }
  void print() const;

 private:
  double const width_;
};
#endif

#include "Particle.hpp"

Particle::Particle() = default;
Particle::Particle(const char* name, double px, double py, double pz)
    : px_{px}, py_{py}, pz_{pz} {
  index_ = findType(name);
  if (index_ == numTypes) {
    index_ = -1;
    std::string error{"Can't find "};
    error.append(name);
    error.append(" among the particle types.\n");
    throw std::runtime_error(error);
  }
}
Particle::Particle(Particle& p)
    : index_{p.getIndex()}, px_{p.getPx()}, py_{p.getPy()}, pz_{p.getPz()} {}

int Particle::decayTo(Particle& p1, Particle& p2) const {
  if (getMass() == 0.0) {
    throw std::runtime_error("Decayment cannot be performed if mass is zero\n");
    return 1;
  }
  double massMot = getMass();
  double massP1 = p1.getMass();
  double massP2 = p2.getMass();
  if (index_ > -1) {
    float x1;
    float x2;
    float w;
    float y1;
    float y2;
    double invnum = 1. / RAND_MAX;
    do {
      x1 = 2. * rand() * invnum - 1.;
      x2 = 2. * rand() * invnum - 1.;
      w = x1 * x1 + x2 * x2;
    } while (w >= 1.);
    w = std::sqrt((-2. * std::log(w)) / w);
    y1 = x1 * w;
    y2 = x2 * w;
    massMot += pTypes[index_]->getWidth() * y1;
  }
  if (massMot < massP1 + massP2) {
    throw std::runtime_error(
        "Decayment cannot be performed because mass is too low in this "
        "channel\n");
    return 2;
  }
  double pout =
      std::sqrt((massMot * massMot - (massP1 + massP2) * (massP1 + massP2)) *
                (massMot * massMot - (massP1 - massP2) * (massP1 - massP2))) /
      massMot * 0.5;
  double norm = 2 * M_PI / RAND_MAX;
  double phi = rand() * norm;
  double theta = rand() * norm * 0.5 - M_PI / 2.;
  p1.setP(pout * std::sin(theta) * std::cos(phi),
          pout * std::sin(theta) * std::sin(phi), pout * std::cos(theta));
  p2.setP(-pout * std::sin(theta) * std::cos(phi),
          -pout * std::sin(theta) * std::sin(phi), -pout * std::cos(theta));
  double energy =
      std::sqrt(px_ * px_ + py_ * py_ + pz_ * pz_ + massMot * massMot);
  double bx = px_ / energy;
  double by = py_ / energy;
  double bz = pz_ / energy;
  p1.boost(bx, by, bz);
  p2.boost(bx, by, bz);
  return 0;
}

double Particle::getEnergy() const {
  double p_square = px_ * px_ + py_ * py_ + pz_ * pz_;
  double result = getMass() * getMass() + p_square;
  return std::sqrt(result);
}
double Particle::getInvMass(Particle& particle) {
  double px_tot = px_ + particle.getPx();
  double py_tot = py_ + particle.getPy();
  double pz_tot = pz_ + particle.getPz();
  double p_tot_square = px_tot * px_tot + py_tot * py_tot + pz_tot * pz_tot;
  double energy_tot = getEnergy() + particle.getEnergy();
  double result = energy_tot * energy_tot - p_tot_square;
  return std::sqrt(result);
}

void Particle::setIndex(int index) {
  if (index < numTypes) {
    index_ = index;
  } else {
    std::string error{"Type "};
    error.append(std::to_string(index));
    error.append(" doesn't exist.\n");
    throw std::runtime_error(error);
  }
}
void Particle::setIndex(const char* name) {
  if (findType(name) < numTypes) {
    index_ = findType(name);
  } else {
    std::string error{name};
    error.append(" doesn't exists.\n");
    throw std::runtime_error(error);
  }
}
void Particle::setP(double px, double py, double pz) {
  px_ = px;
  py_ = py;
  pz_ = pz;
}

void Particle::addType(const char* name, double mass, int charge,
                       double width) {
  if (numTypes <= 10) {
    if (findType(name) < numTypes) {
      std::string error{"Particle "};
      error.append(name);
      error.append(" already added.\n");
      throw std::runtime_error(error);
    } else {
      if (width != 0.) {
        pTypes[numTypes] = new ResonanceType{name, mass, charge, width};
        numTypes++;
      } else {
        pTypes[numTypes] = new ParticleType{name, mass, charge};
        numTypes++;
      }
    }
  } else {
    std::string error{"Can't add "};
    error.append(name);
    error.append(". Maximum number of particles reached (");
    error.append(std::to_string(maxTypes));
    error.append(").\n");
    throw std::runtime_error(error);
  }
}
void Particle::addType(ParticleType& newType) {
  const char* name = newType.getName();
  if (numTypes <= 10) {
    if (findType(name) < numTypes) {
      std::string error{"Particle "};
      error.append(name);
      error.append(" already added.\n");
      throw std::runtime_error(error);
    } else {
      pTypes[numTypes] = new ParticleType{newType};
      numTypes++;
    }
  } else {
    std::string error{"Can't add "};
    error.append(name);
    error.append(". Maximum number of particles reached (");
    error.append(std::to_string(maxTypes));
    error.append(").\n");
    throw std::runtime_error(error);
  }
}
void Particle::addType(ResonanceType& newType) {
  const char* name = newType.getName();
  if (numTypes <= 10) {
    if (findType(name) < numTypes) {
      std::string error{"Particle "};
      error.append(name);
      error.append(" already added.\n");
      throw std::runtime_error(error);
    } else {
      pTypes[numTypes] = new ResonanceType{newType};
      numTypes++;
    }
  } else {
    std::string error{"Can't add "};
    error.append(name);
    error.append(". Maximum number of particles reached (");
    error.append(std::to_string(maxTypes));
    error.append(").\n");
    throw std::runtime_error(error);
  }
}

void Particle::print() const {
  std::cout << "Index: " << index_ << " Name: " << pTypes[index_]->getName()
            << " Vector P: (" << px_ << ',' << py_ << ',' << pz_ << ")\n";
}
void Particle::printTypes() {
  for (int i = 0; i != numTypes; ++i) {
    pTypes[i]->print();
  }
}

const int Particle::maxTypes = 10;
ParticleType* Particle::pTypes[maxTypes];
int Particle::numTypes{0};

int Particle::findType(const char* name) {
  int index = 0;
  // auto first = pTypes[0];
  // auto last = pTypes[numTypes];
  for (; index != numTypes; ++index) {
    if (pTypes[index]->getName() == name) {
      return index;
    }
  }
  return index;
}

void Particle::boost(double bx, double by, double bz) {
  double energy = getEnergy();
  double b2 = bx * bx + by * by + bz * bz;
  double gamma = 1. / std::sqrt(1. - b2);
  double bp = bx * px_ + by * py_ + bz * pz_;
  double gamma2 = b2 > 0 ? (gamma - 1.) / b2 : 0.;
  px_ += gamma2 * bp * bx + gamma * bx * energy;
  py_ += gamma2 * bp * by + gamma * by * energy;
  pz_ += gamma2 * bp * bz + gamma * bz * energy;
}

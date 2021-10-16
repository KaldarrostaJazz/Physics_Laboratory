#include "Particle.hpp"

Particle::Particle(const char* name, double px, double py, double pz)
    : px_{px}, py_{py}, pz_{pz} {
  index_ = findType(name);
  if (index_ == numTypes) {
    std::string error{"Can't find "};
    error.append(name);
    error.append(" among the particle types.\n");
    throw std::runtime_error(error);
  }
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

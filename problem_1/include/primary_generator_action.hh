#ifndef PRIMARY_GENERATOR_ACTION_HH
#define PRIMARY_GENERATOR_ACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;

class primary_generator_action : public G4VUserPrimaryGeneratorAction {
public:
  primary_generator_action();
  ~primary_generator_action() override;
  void GeneratePrimaries(G4Event* event) override;

private:
  G4double sample_cs137_beta();
  G4double compute_spectrum_max(G4double t_max) const;

  G4ParticleGun* gun;
  G4double n_max_low;
  G4double n_max_high;
};

#endif

#ifndef PRIMARY_GENERATOR_ACTION_HH
#define PRIMARY_GENERATOR_ACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;
class detector_construction;

class primary_generator_action : public G4VUserPrimaryGeneratorAction {
public:
  primary_generator_action(detector_construction* det);
  ~primary_generator_action() override;
  void GeneratePrimaries(G4Event* event) override;

private:
  G4ParticleGun* gun;
  detector_construction* detector;
  G4double energies[5];
};

#endif

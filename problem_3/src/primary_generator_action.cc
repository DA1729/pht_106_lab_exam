#include "primary_generator_action.hh"
#include "detector_construction.hh"

#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4Event.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

primary_generator_action::primary_generator_action(detector_construction* det)
  : detector(det), energies{4 * MeV, 5 * MeV, 6 * MeV, 7 * MeV, 8 * MeV}
{
  gun = new G4ParticleGun(1);
  gun->SetParticleDefinition(
      G4ParticleTable::GetParticleTable()->FindParticle("alpha"));
  gun->SetParticleMomentumDirection({0, 0, 1});
}

primary_generator_action::~primary_generator_action()
{
  delete gun;
}

void primary_generator_action::GeneratePrimaries(G4Event* event)
{
  gun->SetParticlePosition({0, 0, detector->get_source_z()});
  G4int idx = (G4int)(G4UniformRand() * 5);
  if (idx > 4) idx = 4;
  gun->SetParticleEnergy(energies[idx]);
  gun->GeneratePrimaryVertex(event);
}

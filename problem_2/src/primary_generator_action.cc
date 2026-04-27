#include "primary_generator_action.hh"
#include "detector_construction.hh"

#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4Event.hh"
#include "G4SystemOfUnits.hh"

primary_generator_action::primary_generator_action(detector_construction* det)
  : detector(det)
{
  gun = new G4ParticleGun(1);
  gun->SetParticleDefinition(G4ParticleTable::GetParticleTable()->FindParticle("alpha"));
  gun->SetParticleMomentumDirection({0, 0, 1});
  gun->SetParticleEnergy(4 * MeV);
}

primary_generator_action::~primary_generator_action()
{
  delete gun;
}

void primary_generator_action::GeneratePrimaries(G4Event* event)
{
  G4double t = detector->get_thickness();
  gun->SetParticlePosition({0, 0, -t / 2 - 0.05 * t});
  gun->GeneratePrimaryVertex(event);
}

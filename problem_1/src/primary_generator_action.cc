#include "primary_generator_action.hh"

#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4Event.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "Randomize.hh"

primary_generator_action::primary_generator_action()
{
  gun = new G4ParticleGun(1);
  gun->SetParticleDefinition(G4ParticleTable::GetParticleTable()->FindParticle("e-"));
  n_max_low = compute_spectrum_max(0.514);
  n_max_high = compute_spectrum_max(1.176);
}

primary_generator_action::~primary_generator_action()
{
  delete gun;
}

G4double primary_generator_action::compute_spectrum_max(G4double t_max) const
{
  const G4double me = 0.511;
  G4double n_max = 0;
  for (int i = 1; i < 200; i++) {
    G4double t = t_max * i / 200.0;
    G4double pe = std::sqrt(t * t + 2 * t * me);
    G4double n = pe * (t + me) * (t_max - t) * (t_max - t);
    if (n > n_max) n_max = n;
  }
  return n_max * 1.05;
}

G4double primary_generator_action::sample_cs137_beta()
{
  G4double t_max, n_max;
  if (G4UniformRand() < 0.947) { t_max = 0.514; n_max = n_max_low; }
  else                          { t_max = 1.176; n_max = n_max_high; }

  const G4double me = 0.511;
  while (true) {
    G4double t = G4UniformRand() * t_max;
    G4double pe = std::sqrt(t * t + 2 * t * me);
    G4double n = pe * (t + me) * (t_max - t) * (t_max - t);
    if (G4UniformRand() * n_max < n) return t * MeV;
  }
}

void primary_generator_action::GeneratePrimaries(G4Event* event)
{
  const G4double crystal_half_z = 0.5 * 2.54 * cm;
  const G4double source_z = -(crystal_half_z + 5 * mm);
  gun->SetParticlePosition({0, 0, source_z});

  G4double cos_theta = G4UniformRand();
  G4double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);
  G4double phi = 2 * pi * G4UniformRand();
  gun->SetParticleMomentumDirection({sin_theta * std::cos(phi),
                                     sin_theta * std::sin(phi),
                                     cos_theta});

  gun->SetParticleEnergy(sample_cs137_beta());
  gun->GeneratePrimaryVertex(event);
}

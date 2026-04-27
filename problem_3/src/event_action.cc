#include "event_action.hh"

#include "G4Event.hh"
#include "G4PrimaryVertex.hh"
#include "G4PrimaryParticle.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"

event_action::event_action() : edep(0.0) {}

void event_action::BeginOfEventAction(const G4Event*)
{
  edep = 0.0;
}

void event_action::EndOfEventAction(const G4Event* event)
{
  G4double e_source = event->GetPrimaryVertex()->GetPrimary()->GetKineticEnergy();
  auto am = G4AnalysisManager::Instance();
  am->FillNtupleDColumn(0, edep / keV);
  am->FillNtupleDColumn(1, e_source / MeV);
  am->AddNtupleRow();
}

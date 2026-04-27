#include "event_action.hh"

#include "G4Event.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"

event_action::event_action() : edep(0.0) {}

void event_action::BeginOfEventAction(const G4Event*)
{
  edep = 0.0;
}

void event_action::EndOfEventAction(const G4Event*)
{
  auto analysis = G4AnalysisManager::Instance();
  analysis->FillNtupleDColumn(0, edep / keV);
  analysis->AddNtupleRow();
}

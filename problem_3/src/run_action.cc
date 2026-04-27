#include "run_action.hh"

#include "G4Run.hh"
#include "G4AnalysisManager.hh"

run_action::run_action()
{
  auto am = G4AnalysisManager::Instance();
  am->SetDefaultFileType("csv");
  am->SetVerboseLevel(0);
  am->CreateNtuple("spectrum", "alpha spectrum");
  am->CreateNtupleDColumn("edep_keV");
  am->CreateNtupleDColumn("e_source_MeV");
  am->FinishNtuple();
}

void run_action::BeginOfRunAction(const G4Run*)
{
  G4AnalysisManager::Instance()->OpenFile();
}

void run_action::EndOfRunAction(const G4Run*)
{
  auto am = G4AnalysisManager::Instance();
  am->Write();
  am->CloseFile();
}

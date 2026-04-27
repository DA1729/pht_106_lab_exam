#include "run_action.hh"

#include "G4Run.hh"
#include "G4AnalysisManager.hh"

run_action::run_action()
{
  auto analysis = G4AnalysisManager::Instance();
  analysis->SetDefaultFileType("csv");
  analysis->SetVerboseLevel(0);
  analysis->CreateNtuple("edep", "energy deposition in crystal");
  analysis->CreateNtupleDColumn("edep_keV");
  analysis->FinishNtuple();
}

void run_action::BeginOfRunAction(const G4Run*)
{
  G4AnalysisManager::Instance()->OpenFile();
}

void run_action::EndOfRunAction(const G4Run*)
{
  auto analysis = G4AnalysisManager::Instance();
  analysis->Write();
  analysis->CloseFile();
}

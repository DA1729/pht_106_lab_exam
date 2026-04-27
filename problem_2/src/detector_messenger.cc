#include "detector_messenger.hh"
#include "detector_construction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"

detector_messenger::detector_messenger(detector_construction* det)
  : detector(det)
{
  dir = new G4UIdirectory("/det/");
  dir->SetGuidance("detector commands");

  material_cmd = new G4UIcmdWithAString("/det/material", this);
  material_cmd->SetGuidance("set absorber material (air or silicon)");
  material_cmd->SetParameterName("key", false);
  material_cmd->AvailableForStates(G4State_PreInit);
}

detector_messenger::~detector_messenger()
{
  delete material_cmd;
  delete dir;
}

void detector_messenger::SetNewValue(G4UIcommand* cmd, G4String value)
{
  if (cmd == material_cmd) {
    detector->set_material(value);
  }
}

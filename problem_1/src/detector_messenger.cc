#include "detector_messenger.hh"
#include "detector_construction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"

detector_messenger::detector_messenger(detector_construction* det)
  : detector(det)
{
  dir = new G4UIdirectory("/det/");
  dir->SetGuidance("detector commands");

  casing_cmd = new G4UIcmdWithAString("/det/casing", this);
  casing_cmd->SetGuidance("set casing material (e.g. G4_Al, G4_AIR)");
  casing_cmd->SetParameterName("material", false);
  casing_cmd->AvailableForStates(G4State_PreInit);
}

detector_messenger::~detector_messenger()
{
  delete casing_cmd;
  delete dir;
}

void detector_messenger::SetNewValue(G4UIcommand* cmd, G4String value)
{
  if (cmd == casing_cmd) {
    detector->set_casing_material(value);
  }
}

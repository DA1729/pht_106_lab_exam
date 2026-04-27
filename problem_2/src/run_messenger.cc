#include "run_messenger.hh"
#include "run_action.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"

run_messenger::run_messenger(run_action* ra) : run(ra)
{
  dir = new G4UIdirectory("/io/");
  dir->SetGuidance("io commands");

  output_cmd = new G4UIcmdWithAString("/io/output", this);
  output_cmd->SetGuidance("set output csv path (without extension)");
  output_cmd->SetParameterName("path", false);
}

run_messenger::~run_messenger()
{
  delete output_cmd;
  delete dir;
}

void run_messenger::SetNewValue(G4UIcommand* cmd, G4String value)
{
  if (cmd == output_cmd) {
    run->set_output_path(value);
  }
}

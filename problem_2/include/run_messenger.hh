#ifndef RUN_MESSENGER_HH
#define RUN_MESSENGER_HH

#include "G4UImessenger.hh"
#include "globals.hh"

class run_action;
class G4UIdirectory;
class G4UIcmdWithAString;

class run_messenger : public G4UImessenger {
public:
  run_messenger(run_action* ra);
  ~run_messenger() override;
  void SetNewValue(G4UIcommand* cmd, G4String value) override;

private:
  run_action* run;
  G4UIdirectory* dir;
  G4UIcmdWithAString* output_cmd;
};

#endif

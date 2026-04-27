#ifndef DETECTOR_MESSENGER_HH
#define DETECTOR_MESSENGER_HH

#include "G4UImessenger.hh"
#include "globals.hh"

class detector_construction;
class G4UIdirectory;
class G4UIcmdWithAString;

class detector_messenger : public G4UImessenger {
public:
  detector_messenger(detector_construction* det);
  ~detector_messenger() override;
  void SetNewValue(G4UIcommand* cmd, G4String value) override;

private:
  detector_construction* detector;
  G4UIdirectory* dir;
  G4UIcmdWithAString* material_cmd;
};

#endif

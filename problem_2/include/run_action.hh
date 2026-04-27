#ifndef RUN_ACTION_HH
#define RUN_ACTION_HH

#include "G4UserRunAction.hh"
#include "globals.hh"
#include <vector>

class detector_construction;
class run_messenger;

class run_action : public G4UserRunAction {
public:
  run_action(detector_construction* det);
  ~run_action() override;

  void BeginOfRunAction(const G4Run*) override;
  void EndOfRunAction(const G4Run*) override;

  void add_edep(G4int bin, G4double edep) {
    if (bin >= 0 && bin < (G4int)edeps.size()) edeps[bin] += edep;
  }

  void set_output_path(const G4String& path) { output_path = path; }

private:
  detector_construction* detector;
  std::vector<G4double> edeps;
  G4String output_path;
  run_messenger* messenger;
};

#endif

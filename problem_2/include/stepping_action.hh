#ifndef STEPPING_ACTION_HH
#define STEPPING_ACTION_HH

#include "G4UserSteppingAction.hh"

class run_action;
class detector_construction;

class stepping_action : public G4UserSteppingAction {
public:
  stepping_action(run_action* ra, detector_construction* det);
  ~stepping_action() override = default;

  void UserSteppingAction(const G4Step* step) override;

private:
  run_action* run;
  detector_construction* detector;
};

#endif

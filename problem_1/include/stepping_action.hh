#ifndef STEPPING_ACTION_HH
#define STEPPING_ACTION_HH

#include "G4UserSteppingAction.hh"

class event_action;
class detector_construction;

class stepping_action : public G4UserSteppingAction {
public:
  stepping_action(event_action* ea, detector_construction* det);
  ~stepping_action() override = default;

  void UserSteppingAction(const G4Step* step) override;

private:
  event_action* event;
  detector_construction* detector;
};

#endif

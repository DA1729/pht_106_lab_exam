#ifndef ACTION_INITIALIZATION_HH
#define ACTION_INITIALIZATION_HH

#include "G4VUserActionInitialization.hh"

class detector_construction;

class action_initialization : public G4VUserActionInitialization {
public:
  action_initialization(detector_construction* det);
  ~action_initialization() override = default;

  void Build() const override;

private:
  detector_construction* detector;
};

#endif

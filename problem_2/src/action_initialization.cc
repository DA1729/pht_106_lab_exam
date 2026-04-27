#include "action_initialization.hh"
#include "primary_generator_action.hh"
#include "run_action.hh"
#include "stepping_action.hh"

action_initialization::action_initialization(detector_construction* det)
  : detector(det) {}

void action_initialization::Build() const
{
  SetUserAction(new primary_generator_action(detector));
  auto run = new run_action(detector);
  SetUserAction(run);
  SetUserAction(new stepping_action(run, detector));
}

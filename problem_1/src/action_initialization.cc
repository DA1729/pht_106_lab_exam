#include "action_initialization.hh"
#include "primary_generator_action.hh"
#include "run_action.hh"
#include "event_action.hh"
#include "stepping_action.hh"

action_initialization::action_initialization(detector_construction* det)
  : detector(det) {}

void action_initialization::Build() const
{
  SetUserAction(new primary_generator_action);
  SetUserAction(new run_action);
  auto event = new event_action;
  SetUserAction(event);
  SetUserAction(new stepping_action(event, detector));
}

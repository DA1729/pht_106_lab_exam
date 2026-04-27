#include "stepping_action.hh"
#include "event_action.hh"
#include "detector_construction.hh"

#include "G4Step.hh"
#include "G4LogicalVolume.hh"

stepping_action::stepping_action(event_action* ea, detector_construction* det)
  : event(ea), detector(det) {}

void stepping_action::UserSteppingAction(const G4Step* step)
{
  auto vol = step->GetPreStepPoint()->GetTouchableHandle()
                  ->GetVolume()->GetLogicalVolume();
  if (vol == detector->get_detector_logical()) {
    event->add_edep(step->GetTotalEnergyDeposit());
  }
}

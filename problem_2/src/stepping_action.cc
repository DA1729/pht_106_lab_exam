#include "stepping_action.hh"
#include "run_action.hh"
#include "detector_construction.hh"

#include "G4Step.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"

stepping_action::stepping_action(run_action* ra, detector_construction* det)
  : run(ra), detector(det) {}

void stepping_action::UserSteppingAction(const G4Step* step)
{
  auto vol = step->GetPreStepPoint()->GetTouchableHandle()
                  ->GetVolume()->GetLogicalVolume();
  if (vol != detector->get_absorber_logical()) return;

  G4double edep = step->GetTotalEnergyDeposit();
  if (edep <= 0.0) return;

  G4double z_pre = step->GetPreStepPoint()->GetPosition().z();
  G4double z_post = step->GetPostStepPoint()->GetPosition().z();
  G4double z_mid = 0.5 * (z_pre + z_post);

  G4double depth = z_mid + detector->get_thickness() / 2;
  G4double bin_width = detector->get_thickness() / detector->get_n_bins();
  G4int bin = (G4int)(depth / bin_width);
  run->add_edep(bin, edep);
}

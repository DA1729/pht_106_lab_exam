#include "run_action.hh"
#include "run_messenger.hh"
#include "detector_construction.hh"

#include "G4Run.hh"
#include "G4SystemOfUnits.hh"

#include <fstream>
#include <iomanip>

run_action::run_action(detector_construction* det)
  : detector(det), output_path("bragg"), messenger(nullptr)
{
  messenger = new run_messenger(this);
}

run_action::~run_action()
{
  delete messenger;
}

void run_action::BeginOfRunAction(const G4Run*)
{
  edeps.assign(detector->get_n_bins(), 0.0);
}

void run_action::EndOfRunAction(const G4Run* run)
{
  G4int events = run->GetNumberOfEvent();
  if (events == 0) return;

  G4double t = detector->get_thickness();
  G4int n = detector->get_n_bins();
  G4double bin_width = t / n;

  std::ofstream out(output_path + ".csv");
  out << "# depth_mm,edep_keV_per_event\n";
  out << std::setprecision(8);
  for (G4int i = 0; i < n; i++) {
    G4double depth = (i + 0.5) * bin_width / mm;
    G4double edep_per_event = edeps[i] / events / keV;
    out << depth << "," << edep_per_event << "\n";
  }
  out.close();
  G4cout << "wrote " << output_path << ".csv "
         << "(" << detector->get_material_key() << ", "
         << events << " events)" << G4endl;
}

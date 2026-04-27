#include "detector_construction.hh"
#include "detector_messenger.hh"

#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4UserLimits.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

detector_construction::detector_construction()
  : material_key("air"),
    material_name("G4_AIR"),
    absorber_thickness(100 * mm),
    absorber_transverse(50 * mm),
    n_bins(200),
    absorber_logical(nullptr),
    messenger(nullptr)
{
  messenger = new detector_messenger(this);
}

detector_construction::~detector_construction()
{
  delete messenger;
}

void detector_construction::set_material(const G4String& key)
{
  if (key == "air") {
    material_key = "air";
    material_name = "G4_AIR";
    absorber_thickness = 100 * mm;
    absorber_transverse = 50 * mm;
  } else if (key == "silicon" || key == "si") {
    material_key = "silicon";
    material_name = "G4_Si";
    absorber_thickness = 80 * um;
    absorber_transverse = 0.5 * mm;
  } else {
    G4cerr << "unknown material key: " << key << G4endl;
  }
}

G4VPhysicalVolume* detector_construction::Construct()
{
  auto nist = G4NistManager::Instance();
  auto vacuum = nist->FindOrBuildMaterial("G4_Galactic");
  auto absorber_mat = nist->FindOrBuildMaterial(material_name);

  G4double margin = 0.1 * absorber_thickness + 1 * um;
  G4double half_xy = absorber_transverse / 2 + margin;
  G4double half_z = absorber_thickness / 2 + margin;

  auto world_solid = new G4Box("world", half_xy, half_xy, half_z);
  auto world_log = new G4LogicalVolume(world_solid, vacuum, "world");
  auto world_phys = new G4PVPlacement(nullptr, {}, world_log, "world",
                                      nullptr, false, 0, true);
  world_log->SetVisAttributes(G4VisAttributes::GetInvisible());

  auto abs_solid = new G4Box("absorber",
                             absorber_transverse / 2,
                             absorber_transverse / 2,
                             absorber_thickness / 2);
  absorber_logical = new G4LogicalVolume(abs_solid, absorber_mat, "absorber");
  new G4PVPlacement(nullptr, {}, absorber_logical, "absorber",
                    world_log, false, 0, true);

  G4double max_step = (absorber_thickness / n_bins) / 4.0;
  absorber_logical->SetUserLimits(new G4UserLimits(max_step));

  auto vis = new G4VisAttributes(G4Colour(0.5, 0.7, 0.9, 0.5));
  vis->SetForceSolid(true);
  absorber_logical->SetVisAttributes(vis);

  return world_phys;
}

#include "detector_construction.hh"

#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

detector_construction::detector_construction()
  : air_gap(10 * mm),
    source_z(-5 * mm),
    detector_thickness(100 * um),
    detector_logical(nullptr) {}

G4VPhysicalVolume* detector_construction::Construct()
{
  auto nist = G4NistManager::Instance();
  auto air = nist->FindOrBuildMaterial("G4_AIR");
  auto si = nist->FindOrBuildMaterial("G4_Si");

  auto world_solid = new G4Box("world", 25 * mm, 25 * mm, 15 * mm);
  auto world_log = new G4LogicalVolume(world_solid, air, "world");
  auto world_phys = new G4PVPlacement(nullptr, {}, world_log, "world",
                                      nullptr, false, 0, true);
  world_log->SetVisAttributes(G4VisAttributes::GetInvisible());

  auto det_solid = new G4Box("detector", 10 * mm, 10 * mm,
                             detector_thickness / 2);
  detector_logical = new G4LogicalVolume(det_solid, si, "detector");

  G4double det_center_z = source_z + air_gap + detector_thickness / 2;
  new G4PVPlacement(nullptr, {0, 0, det_center_z}, detector_logical,
                    "detector", world_log, false, 0, true);

  auto vis = new G4VisAttributes(G4Colour(0.6, 0.7, 1.0, 0.6));
  vis->SetForceSolid(true);
  detector_logical->SetVisAttributes(vis);

  return world_phys;
}

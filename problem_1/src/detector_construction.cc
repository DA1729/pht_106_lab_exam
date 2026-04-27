#include "detector_construction.hh"
#include "detector_messenger.hh"

#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

detector_construction::detector_construction()
  : casing_material_name("G4_Al"), crystal_logical(nullptr), messenger(nullptr)
{
  messenger = new detector_messenger(this);
}

detector_construction::~detector_construction()
{
  delete messenger;
}

G4VPhysicalVolume* detector_construction::Construct()
{
  auto nist = G4NistManager::Instance();
  auto air = nist->FindOrBuildMaterial("G4_AIR");
  auto nai = nist->FindOrBuildMaterial("G4_SODIUM_IODIDE");
  auto casing_mat = nist->FindOrBuildMaterial(casing_material_name);

  G4double world_size = 30 * cm;
  auto world_solid = new G4Box("world", world_size / 2, world_size / 2, world_size / 2);
  auto world_logical = new G4LogicalVolume(world_solid, air, "world");
  auto world_phys = new G4PVPlacement(nullptr, {}, world_logical, "world",
                                      nullptr, false, 0, true);
  world_logical->SetVisAttributes(G4VisAttributes::GetInvisible());

  G4double crystal_radius = 0.5 * 2.54 * cm;
  G4double crystal_half_z = 0.5 * 2.54 * cm;
  G4double al_thickness = 0.5 * mm;

  auto casing_solid = new G4Tubs("casing", 0,
                                 crystal_radius + al_thickness,
                                 crystal_half_z + al_thickness,
                                 0, 360 * deg);
  auto casing_logical = new G4LogicalVolume(casing_solid, casing_mat, "casing");
  new G4PVPlacement(nullptr, {}, casing_logical, "casing",
                    world_logical, false, 0, true);
  auto casing_vis = new G4VisAttributes(G4Colour(0.6, 0.6, 0.6, 0.4));
  casing_vis->SetForceSolid(true);
  casing_logical->SetVisAttributes(casing_vis);

  auto crystal_solid = new G4Tubs("crystal", 0, crystal_radius,
                                  crystal_half_z, 0, 360 * deg);
  crystal_logical = new G4LogicalVolume(crystal_solid, nai, "crystal");
  new G4PVPlacement(nullptr, {}, crystal_logical, "crystal",
                    casing_logical, false, 0, true);
  auto crystal_vis = new G4VisAttributes(G4Colour(0.2, 0.8, 1.0, 0.6));
  crystal_vis->SetForceSolid(true);
  crystal_logical->SetVisAttributes(crystal_vis);

  return world_phys;
}

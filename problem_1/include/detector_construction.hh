#ifndef DETECTOR_CONSTRUCTION_HH
#define DETECTOR_CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4LogicalVolume;
class detector_messenger;

class detector_construction : public G4VUserDetectorConstruction {
public:
  detector_construction();
  ~detector_construction() override;

  G4VPhysicalVolume* Construct() override;

  void set_casing_material(const G4String& name) { casing_material_name = name; }
  G4LogicalVolume* get_crystal_logical() const { return crystal_logical; }

private:
  G4String casing_material_name;
  G4LogicalVolume* crystal_logical;
  detector_messenger* messenger;
};

#endif

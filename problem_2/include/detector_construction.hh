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

  void set_material(const G4String& key);

  G4double get_thickness() const { return absorber_thickness; }
  G4int get_n_bins() const { return n_bins; }
  G4String get_material_key() const { return material_key; }
  G4LogicalVolume* get_absorber_logical() const { return absorber_logical; }

private:
  G4String material_key;
  G4String material_name;
  G4double absorber_thickness;
  G4double absorber_transverse;
  G4int n_bins;
  G4LogicalVolume* absorber_logical;
  detector_messenger* messenger;
};

#endif

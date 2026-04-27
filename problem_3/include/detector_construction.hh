#ifndef DETECTOR_CONSTRUCTION_HH
#define DETECTOR_CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4LogicalVolume;

class detector_construction : public G4VUserDetectorConstruction {
public:
  detector_construction();
  ~detector_construction() override = default;

  G4VPhysicalVolume* Construct() override;

  G4double get_air_gap() const { return air_gap; }
  G4double get_source_z() const { return source_z; }
  G4LogicalVolume* get_detector_logical() const { return detector_logical; }

private:
  G4double air_gap;
  G4double source_z;
  G4double detector_thickness;
  G4LogicalVolume* detector_logical;
};

#endif

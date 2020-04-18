#ifndef Scintillator_H
#define Scintillator_H 1
#include "G4Material.hh"
#include "G4LogicalVolume.hh"

class Scintillator
{
    public:
    Scintillator(G4int det_number, G4double rMin, G4double rMax, G4double length);
    void Place(G4RotationMatrix *pRot, 
                        G4ThreeVector &tlate, 
                        const G4String &pName, 
                        G4LogicalVolume *pMotherLogical,  
                        G4int pCopyNo);
    
    private:

    void ConstructCylinder(double rMin, double rMax, double length);
    G4LogicalVolume* ConstructAluLayer();
    G4LogicalVolume* ConstructTeflonLayer();
    G4LogicalVolume* ConstructNaICrystal();
    G4LogicalVolume* CylinderLogVol;
    void ConstructNaI(int det_number, double rMin);


};

#endif

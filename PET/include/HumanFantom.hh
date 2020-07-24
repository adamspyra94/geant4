#ifndef HumanFantom_H
#define HumanFantom_H 1
#include "G4Material.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PSNofSecondary.hh"


class HumanFantom
{
    public:
    HumanFantom(double heigh, double radius);
    void Place(G4RotationMatrix *pRot, 
                        G4ThreeVector &tlate, 
                        const G4String &pName, 
                        G4LogicalVolume *pMotherLogical,  
                        G4int pCopyNo);
    void ConstructSDandField();
    
    private:
    void ConstructHumanFantom(double heigh, double radius);
    void ConstructSpine(double heigh);
    G4Material* MakeWater();
    
    G4LogicalVolume* fantomLogVol;
    G4LogicalVolume* ConstructSpine();


};

#endif

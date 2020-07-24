#include "NaISD.hh"
#include "Scintillator.hh"
#include "G4Tubs.hh"
#include "G4NistManager.hh"
#include "G4VisAttributes.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh" //jednostki
#include "G4PVPlacement.hh"
#include "G4Material.hh"


Scintillator::Scintillator(int det_number, double rMin, double rMax, double length)
{
    NaILogic=0;
    ConstructCylinder(rMin, rMax, length);
    ConstructNaI(det_number, rMin);
    //ConstructSDandField();
}

void Scintillator::ConstructCylinder(double rMin, double rMax, double length)
{
     G4NistManager* man=G4NistManager::Instance();
     G4Material* ppy = man->FindOrBuildMaterial("G4_POLYPROPYLENE");
     G4Tubs* theCylinder = new G4Tubs("theCylinder", rMin, rMax, length/2, 0*deg, 360*deg);
     CylinderLogVol = new G4LogicalVolume(theCylinder, ppy, "CylinderLogVol");

     G4VisAttributes* cylinderAtt = new G4VisAttributes(G4Colour(0.5,0.5,0.5, 0.7));
     //cylinderAtt->SetForceAuxEdgeVisible(true);
     //cylinderAtt->SetForceSolid(true);
     CylinderLogVol->SetVisAttributes(cylinderAtt);

//     G4ThreeVector pos(0,0, 0);
//     new G4PVPlacement(0,pos,CylinderLogVol, "cylinderPhy",worldLogic,0,0);
}

G4LogicalVolume* Scintillator::ConstructAluLayer()
{
	G4double rMin = 0.;
	G4double rMax = 3.6*cm;
	G4double halflength = 5.6*cm;
	G4NistManager* man=G4NistManager::Instance();
	G4Tubs* AluminiumSolid = new G4Tubs("AluminiumSolid", rMin, rMax, halflength, 0*deg, 360*deg);
	G4Material* alu = man->FindOrBuildMaterial("G4_Al");
	G4LogicalVolume* aluLogic = new G4LogicalVolume(AluminiumSolid, alu, "AluLogic");
	G4VisAttributes* aluVis = new G4VisAttributes(G4Colour(1,102./255.,0));
     aluVis->SetForceAuxEdgeVisible(true);
     //aluVis->SetForceSolid(true);
     aluLogic->SetVisAttributes(aluVis);
     return aluLogic;
}

G4LogicalVolume* Scintillator::ConstructTeflonLayer()
{
	G4double rMin = 0.;
	G4double rMax = 3.3*cm;
	G4double halflength = 5.3*cm;
	G4NistManager* man=G4NistManager::Instance();
	G4Tubs* TeflonSolid = new G4Tubs("TeflonSolid", rMin, rMax, halflength, 0*deg, 360*deg);
	G4Material* teflon = man->FindOrBuildMaterial("G4_TEFLON");
	G4LogicalVolume* teflonLogic = new G4LogicalVolume(TeflonSolid, teflon, "TeflonLogic");
	G4VisAttributes* teflonVis = new G4VisAttributes(G4Colour(0,1,0));
     teflonVis->SetForceAuxEdgeVisible(true);
     //teflonVis->SetForceSolid(true);
     teflonLogic->SetVisAttributes(teflonVis);
     return teflonLogic;
}
G4LogicalVolume* Scintillator::ConstructNaICrystal()
{
	G4double rMin = 0.;
	G4double rMax = 3.*cm;
	G4double halflength = 5.*cm;
	G4NistManager* man=G4NistManager::Instance();
	G4Tubs* NaISolid = new G4Tubs("NaISolid", rMin, rMax, halflength, 0*deg, 360*deg);
	G4Material* NaI = man->FindOrBuildMaterial("G4_SODIUM_IODIDE");
	NaILogic = new G4LogicalVolume(NaISolid, NaI, "NaILogic");
	G4VisAttributes* NaIVis = new G4VisAttributes(G4Colour(0.5,0.5,0));
     NaIVis->SetForceAuxEdgeVisible(true);
     NaIVis->SetForceSolid(true);
     NaILogic->SetVisAttributes(NaIVis);
     return NaILogic;
}

void Scintillator::ConstructNaI(int det_number,double rMin)
{
     G4LogicalVolume* aluLogic = ConstructAluLayer();
     G4LogicalVolume* teflonLogic = ConstructTeflonLayer();
     G4LogicalVolume* NaILogic = ConstructNaICrystal();
     //G4LogicalVolume* CylinderLogVol = ConstructNaICrystal();
     double rad = rMin+6.6*cm;
     double angle = (360./det_number)*deg;
     
     //G4ThreeVector pos_Al(0,rad,0);
     G4ThreeVector pos(0,0,0);
     //G4RotationMatrix* rot = new G4RotationMatrix();
     //rot -> rotateX(90*deg);
     new G4PVPlacement(0,pos,NaILogic, "NaIPhy",teflonLogic,0,0);
     new G4PVPlacement(0,pos,teflonLogic, "teflonPhy",aluLogic,0,0);
     for (int i=0; i<det_number; i++)
     {
     G4ThreeVector pos_Al(rad*sin(angle*i),rad*cos(angle*i),0);
     G4RotationMatrix* rot = new G4RotationMatrix();
     rot -> rotateZ(angle*i);
     rot -> rotateX(90*deg);
     new G4PVPlacement(rot,pos_Al,aluLogic, "aluPhy",CylinderLogVol,0,i);
     }


}


void Scintillator::Place(G4RotationMatrix *pRot, 
                        G4ThreeVector &tlate, 
                        const G4String &pName, 
                        G4LogicalVolume *pMotherLogical,  
                        G4int pCopyNo)
{
    new G4PVPlacement(pRot, tlate, CylinderLogVol, pName,  pMotherLogical, 0,pCopyNo);
}

void Scintillator::ConstructSDandField()
{
    /*G4MultiFunctionalDetector* detector = new G4MultiFunctionalDetector("naISensitiveDet");
    G4int depth = 2;
    G4VPrimitiveScorer* energyDepScorer = new G4PSEnergyDeposit("eDep",depth);       detector->RegisterPrimitive(energyDepScorer);
    NaILogic->SetSensitiveDetector(detector);
    G4SDManager* SDmanager = G4SDManager::GetSDMpointer();
    SDmanager->AddNewDetector(detector);*/
    
    NaISD* naISD = new NaISD("naISD", "eDep", 2);
    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    SDman->AddNewDetector(naISD);
    NaILogic->SetSensitiveDetector(naISD);
    
}	


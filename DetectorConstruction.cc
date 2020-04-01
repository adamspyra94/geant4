//
// $Id: DetectorConstruction.cc 12.16.2016 A. Fijalkowska $
//
/// \file DetectorConstruction.cc
/// \brief DetectorConstruction class
//
//
#include "DetectorConstruction.hh"
#include "G4PVPlacement.hh" //tworzenie physical volume
#include "G4SystemOfUnits.hh" //jednostki
#include "G4VisAttributes.hh" //sposob wyświetlania, kolory itp

#include "G4Box.hh" //prostopadłościan
#include "G4Tubs.hh" //walec
#include "G4ThreeVector.hh" //trzyelementowy wektor wbudowany w geant
#include "globals.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4SDManager.hh"
#include "G4PSEnergyDeposit.hh"



DetectorConstruction::DetectorConstruction()
{
    worldLogic = 0L;
    fantomLogVol=0L;
    cylinderLogVol=0L;
    man = G4NistManager::Instance();
}



DetectorConstruction::~DetectorConstruction() 
{
    if(worldLogic != 0L)
    	delete worldLogic;
    if(fantomLogVol != 0L)
    	delete fantomLogVol;
    if(cylinderLogVol != 0L)
    	delete cylinderLogVol;
}


G4VPhysicalVolume* DetectorConstruction::Construct()
{
    G4VPhysicalVolume* worldPhys = ConstructWorld();
    ConstructHumanFantom();
    ConstructCylinder();
    ConstructNaI();
    
    return worldPhys;
}


G4VPhysicalVolume* DetectorConstruction::ConstructWorld()
{

    G4double worldX = 1.5*m;
    G4double worldY = 1.5*m;
    G4double worldZ = 1.5*m;
    G4Box* worldSolid = new G4Box("worldSolid",worldX,worldY,worldZ);
    
    G4Material* vaccum = new G4Material("GalacticVacuum", 1., 1.01*g/mole,
                           CLHEP::universe_mean_density, 
                           kStateGas, 3.e-18*pascal, 2.73*kelvin);
                           
    worldLogic = new G4LogicalVolume(worldSolid, vaccum,"worldLogic", 0,0,0);
                                             
    //worldLogic->SetVisAttributes(G4VisAttributes::Invisible);
    G4VPhysicalVolume* worldPhys = new G4PVPlacement(0, G4ThreeVector(), worldLogic, "world", 0, false, 0);
    return worldPhys;

}

G4Material* DetectorConstruction::MakeWater()
{
    G4Element* H = man->FindOrBuildElement("H");
    G4Element* O = man->FindOrBuildElement("O");
    G4Material* water = new G4Material("water", 1.0*g/cm3, 2);
    water->AddElement(H,2);
    water->AddElement(O,1);
    return water;
}
void DetectorConstruction::ConstructHumanFantom()
{   
    G4LogicalVolume* spineLogic = ConstructSpine();
    G4LogicalVolume* fantomLogic = ConstructFantom();
     
    G4ThreeVector pos_fantom(0,0,0);
    G4ThreeVector pos_spine(0,-10*cm,41.5*cm);  
    new G4PVPlacement(0, pos_fantom, fantomLogic, "fantom", worldLogic, 0, 0);
    new G4PVPlacement(0, pos_spine, spineLogic, "spine", fantomLogic, 0, 0);
	
}
G4LogicalVolume* DetectorConstruction::ConstructFantom()
{
    G4double radiusMin = 0;
    G4double radiusMax = 15*cm;
    G4double length = 170*cm; 
    G4Tubs* fantomSolid = new G4Tubs("fantomSolid", radiusMin, radiusMax, length/2., 0*deg, 360*deg);
    G4Material* water = MakeWater();
    G4LogicalVolume* fantomLogic = new G4LogicalVolume(fantomSolid, water, "FantomLogic");
     
    G4VisAttributes* fantomVisAtt = new G4VisAttributes( G4Colour(0,0,1));
    fantomVisAtt->SetForceAuxEdgeVisible(true);// Can see outline when drawn with lines
    //fantomVisAtt->SetForceSolid(true);
    fantomLogic->SetVisAttributes(fantomVisAtt);
    return fantomLogic;
}

G4LogicalVolume* DetectorConstruction::ConstructSpine()
{
	G4double rMin = 0.;
	G4double rMax = 3*cm;
	G4double length = 85*cm;
	G4Tubs* SpineSolid = new G4Tubs("SpineSolid", rMin, rMax, length/2.0, 0*deg, 360*deg);
	G4Material* bone = man->FindOrBuildMaterial("G4_B-100_BONE");
	G4LogicalVolume* spineLogic = new G4LogicalVolume(SpineSolid, bone, "SpineLogic");
	G4VisAttributes* spineVis = new G4VisAttributes(G4Colour(1,1,1));
     spineVis->SetForceAuxEdgeVisible(true);
     //aluVis->SetForceSolid(true);
     spineLogic->SetVisAttributes(spineVis);
     return spineLogic;
}






void DetectorConstruction::ConstructCylinder()
{
     G4Material* ppy = man->FindOrBuildMaterial("G4_POLYPROPYLENE");
     G4double rMin = 40*cm;
     G4double rMax = 55*cm;
     G4double length = 15*cm;
     G4Tubs* theCylinder = new G4Tubs("theCylinder", rMin, rMax, length/2, 0*deg, 360*deg);
     cylinderLogVol = new G4LogicalVolume(theCylinder, ppy, "cylinderLogVol");

     G4VisAttributes* cylinderAtt = new G4VisAttributes(G4Colour(0.5,0.5,0.5, 0.7));
     cylinderAtt->SetForceAuxEdgeVisible(true);
     cylinderAtt->SetForceSolid(true);
     cylinderLogVol->SetVisAttributes(cylinderAtt);

     G4ThreeVector pos(0,0, 0);
     new G4PVPlacement(0,pos,cylinderLogVol, "cylinderPhy",worldLogic,0,0);
}
//krysztal wysoki na 10 cm, wysoki na 3 cm, teflon gruby na 3 mm, Al tez 3 mm

void DetectorConstruction::ConstructNaI()
{
     G4LogicalVolume* aluLogic = ConstructAluLayer();
     G4LogicalVolume* teflonLogic = ConstructTeflonLayer();
     G4LogicalVolume* NaILogic = ConstructNaICrystal();
     double rad = 46.6*cm;
     double angle = 10*deg;
     
     //G4ThreeVector pos_Al(0,rad,0);
     G4ThreeVector pos(0,0,0);
     //G4RotationMatrix* rot = new G4RotationMatrix();
     //rot -> rotateX(90*deg);
     
     for (int i=0; i<36; i++)
     {
     G4ThreeVector pos_Al(rad*sin(angle*i),rad*cos(angle*i),0);
     G4RotationMatrix* rot = new G4RotationMatrix();
     rot -> rotateZ(angle*i);
     rot -> rotateX(90*deg);
     new G4PVPlacement(rot,pos_Al,aluLogic, "aluPhy",cylinderLogVol,0,i);
     }
     new G4PVPlacement(0,pos,teflonLogic, "teflonPhy",aluLogic,0,0);
     new G4PVPlacement(0,pos,NaILogic, "NaIPhy",teflonLogic,0,0);
}

G4LogicalVolume* DetectorConstruction::ConstructAluLayer()
{
	G4double rMin = 0.;
	G4double rMax = 3.6*cm;
	G4double halflength = 5.6*cm;
	G4Tubs* AluminiumSolid = new G4Tubs("AluminiumSolid", rMin, rMax, halflength, 0*deg, 360*deg);
	G4Material* alu = man->FindOrBuildMaterial("G4_Al");
	G4LogicalVolume* aluLogic = new G4LogicalVolume(AluminiumSolid, alu, "AluLogic");
	G4VisAttributes* aluVis = new G4VisAttributes(G4Colour(1,102./255.,0));
     aluVis->SetForceAuxEdgeVisible(true);
     //aluVis->SetForceSolid(true);
     aluLogic->SetVisAttributes(aluVis);
     return aluLogic;
}

G4LogicalVolume* DetectorConstruction::ConstructTeflonLayer()
{
	G4double rMin = 0.;
	G4double rMax = 3.3*cm;
	G4double halflength = 5.3*cm;
	G4Tubs* TeflonSolid = new G4Tubs("TeflonSolid", rMin, rMax, halflength, 0*deg, 360*deg);
	G4Material* teflon = man->FindOrBuildMaterial("G4_Teflon");
	G4LogicalVolume* teflonLogic = new G4LogicalVolume(TeflonSolid, teflon, "TeflonLogic");
	G4VisAttributes* teflonVis = new G4VisAttributes(G4Colour(0,1,0));
     teflonVis->SetForceAuxEdgeVisible(true);
     //teflonVis->SetForceSolid(true);
     teflonLogic->SetVisAttributes(teflonVis);
     return teflonLogic;
}
G4LogicalVolume* DetectorConstruction::ConstructNaICrystal()
{
	G4double rMin = 0.;
	G4double rMax = 3.*cm;
	G4double halflength = 5.*cm;
	G4Tubs* NaISolid = new G4Tubs("NaISolid", rMin, rMax, halflength, 0*deg, 360*deg);
	G4Material* NaI = man->FindOrBuildMaterial("G4_SODIUM_IODIDE");
	G4LogicalVolume* NaILogic = new G4LogicalVolume(NaISolid, NaI, "NaILogic");
	G4VisAttributes* NaIVis = new G4VisAttributes(G4Colour(0.5,0.5,0));
     NaIVis->SetForceAuxEdgeVisible(true);
     NaIVis->SetForceSolid(true);
     NaILogic->SetVisAttributes(NaIVis);
     return NaILogic;
} 		
void DetectorConstruction::ConstructSDandField() 
{


}







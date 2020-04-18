//
// $Id: PrimaryGeneratorAction.hh 15.10.2018 A Fijalkowska $
//
/// \file PrimaryGeneratorAction.hh
/// \brief Definition of the PrimaryGeneratorAction class

#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction();
    virtual ~PrimaryGeneratorAction();

  public:
    virtual void GeneratePrimaries(G4Event*);

  private:
        void GeneratePositronIncident(G4Event*);
	void GenerateBackgroundIncident(G4Event*);
	void SetUpDefault();
	G4ThreeVector GenerateIsotropicDirection(G4double TMin, G4double TMax, G4double PMin, G4double PMax);
	G4ThreeVector GenerateBackgroundPosition(G4double size);
    G4ParticleGun* particleGun;
    G4ParticleTable* particleTable;

};


#endif 


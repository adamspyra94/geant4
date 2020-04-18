
// $Id: PrimaryGeneratorAction.cc 15.10.2018 A Fijalkowska $
//
/// \file PrimaryGeneratorAction.cc
/// \brief Implementation of the PrimaryGeneratorAction class
#include <math.h>
#include "PrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"


PrimaryGeneratorAction::PrimaryGeneratorAction() : G4VUserPrimaryGeneratorAction()
{
    particleGun = new G4ParticleGun();
    particleTable = G4ParticleTable::GetParticleTable();
	SetUpDefault();
}


PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete particleGun;
}

void PrimaryGeneratorAction::SetUpDefault()
{
	
	G4ParticleDefinition* particle = particleTable->FindParticle("gamma");
	particleGun->SetParticleDefinition(particle);
	particleGun->SetParticlePosition(G4ThreeVector(0.0*cm,0.0*cm,0.0*cm));
	particleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));
	particleGun->SetParticleEnergy(500.0*keV);
	
	int size = particleTable -> size();
	std::cout << "Rozmiar tablicy czastek: " << size << std::endl;
	for (int i = 0;i!=size;i++)
	{
	std:: cout << particleTable->GetParticleName(i)<<" ";
	}
	
	std::cout<<std::endl;
	

}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
   	GeneratePositronIncident(anEvent);
	//GenerateBackgroundIncident(anEvent);
}

void PrimaryGeneratorAction::GeneratePositronIncident(G4Event* anEvent)
{
	G4double TMin = 0*deg;
	G4double TMax = 180*deg;
	G4double PMin = 0*deg;
	G4double PMax = 360*deg;
   	G4ParticleDefinition* particle = particleTable->FindParticle("e+");
	particleGun->SetParticleDefinition(particle);
        particleGun->SetParticlePosition(G4ThreeVector(0.,0.,0.));
        particleGun->SetParticleMomentumDirection(GenerateIsotropicDirection(TMin, TMax, PMin, PMax));
	
	particleGun->SetParticleEnergy(587.0*keV);
	particleGun->GeneratePrimaryVertex(anEvent);

}
void PrimaryGeneratorAction::GenerateBackgroundIncident(G4Event* anEvent)
{
   	G4ParticleDefinition* particle = particleTable->FindParticle("gamma");
	particleGun->SetParticleDefinition(particle);
	G4double size = 1.5*m;
        particleGun->SetParticlePosition(GenerateBackgroundPosition(size));
        particleGun->SetParticleMomentumDirection(GenerateIsotropicDirection(0*deg, 180*deg, 0*deg, 360*deg));
	particleGun->SetParticleEnergy(1461*keV);
	particleGun->GeneratePrimaryVertex(anEvent);
}

G4ThreeVector PrimaryGeneratorAction::GenerateIsotropicDirection(G4double TMin, G4double TMax, G4double PMin, G4double PMax)
{
   double cos_theta = cos(TMax)+(cos(TMin)-cos(TMax))*G4UniformRand();
   double sin_theta = pow(1-cos_theta*cos_theta, 0.5);
   double phi = G4UniformRand()*(PMax-PMin)+PMin;
   return G4ThreeVector(sin_theta*cos(phi), sin_theta*sin(phi), cos_theta);
}

G4ThreeVector PrimaryGeneratorAction::GenerateBackgroundPosition(G4double size)
{
   return G4ThreeVector((G4UniformRand()*2-1)*size, (G4UniformRand()*2-1)*size, (G4UniformRand()*2-1)*size);

}


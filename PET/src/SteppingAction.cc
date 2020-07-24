//
// $Id: SteppingAction.cc 15.10.2018 A. Fijalkowska $
//
/// \file SteppingAction.cc
/// \brief Implementation of the SteppingAction class
//
//
#include "SteppingAction.hh"
#include "G4SteppingManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4Step.hh"

SteppingAction::SteppingAction():G4UserSteppingAction()
{

}

SteppingAction::~SteppingAction() {}


void SteppingAction::UserSteppingAction(const G4Step* theStep)
{
    G4Track* theTrack = theStep->GetTrack();
    G4String volumeName = theTrack->GetVolume()->GetName();
    if(volumeName == "fantom")
    {
        auto secondaries = theStep->GetSecondaryInCurrentStep();
    
        nrOfSec+=secondaries->size();
        //std::cout << nrOfSec << std::endl;
    }
    /*G4Track* theTrack = theStep->GetTrack();
    G4String volumeName = theTrack->GetVolume()->GetName();
   
    if (volumeName == "spinePhys")
    {
    G4double energia = theStep->GetTotalEnergyDeposit();//GetDeltaEnergy();
    EDepSpine += (energia/keV);
    //PrintStep(theStep);
    }*/
}

void SteppingAction::PrintStep(const G4Step* theStep)
{
    
    G4Track* theTrack = theStep->GetTrack();
    G4String particleName = theTrack->GetDefinition()->GetParticleName();      
    G4String processName =theStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
    
    G4double energy = theTrack->GetKineticEnergy() ;
    G4String volumeName = theTrack->GetVolume()->GetName();
    G4double deltaEn = theStep->GetDeltaEnergy();
    int trackNr = theTrack->GetTrackID ();

    std::cout << " trackNr: " << trackNr
              << " particle: " << particleName
		      << " process: " << processName
		      << " kinetic energy " << energy/MeV
		      << " delta en: " << deltaEn
		      << " volume name: " << volumeName << std::endl;

}

    G4double SteppingAction::EDepSpine=0;
    G4double SteppingAction::EDepSpineTotal=0;
    G4int SteppingAction::nrOfSec=0;
    G4int SteppingAction::nrOfSecTotal=0;

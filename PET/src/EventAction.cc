
// $Id: EventAction.cc 15.10.2018 A. Fijalkowska $
//
/// \file EventAction.cc
/// \brief Implementation of the EventAction class
//
//
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "G4SDManager.hh"
#include "G4THitsMap.hh"
#include "NaIHit.hh"

EventAction::EventAction()
{
    //output.open("E_Dep_Spine.txt");
    //output.open("Wtorne.txt");
    //output<<"Licznik"<<"\t"<<"Krok"<<std::endl;
    //n=0;
}
 
EventAction::~EventAction()
{

    //output<<"SUMA WTORNE KROK: "<<"\t"<<SteppingAction::nrOfSecTotal<<std::endl;
    //output<<"SUMA WTORNE LICZNIK: "<<"\t"<<n<<std::endl;
    //output.close();
    //std::cout<<"SUMA WTORNE KROK: "<<"\t"<<SteppingAction::nrOfSecTotal << std::endl;
    //std::cout<<"SUMA WTORNE LICZNIK: "<<"\t"<< n << std::endl;
    
}


void EventAction::BeginOfEventAction(const G4Event* anEvent)
{

}
 

void EventAction::EndOfEventAction(const G4Event* anEvent)
{   
    /*output<<anEvent->GetEventID()<<"\t"<<SteppingAction::EDepSpine<<"\t"<<"keV"<<std::endl;
    SteppingAction::EDepSpineTotal+=SteppingAction::EDepSpine;
    SteppingAction::EDepSpine=0;*/

/*
    G4HCofThisEvent *hitsCollOfThisEvent = anEvent->GetHCofThisEvent();
    if(!hitsCollOfThisEvent)
        return;


    G4SDManager* SDmanager = G4SDManager::GetSDMpointer();
    G4int naIcollId = SDmanager->GetCollectionID("naISensitiveDet/eDep");
    //std::cout<<naIcollId << std::endl;
    
    G4THitsMap<G4double>* NaIHitsCollection = static_cast<G4THitsMap<G4double>*>( hitsCollOfThisEvent->GetHC(naIcollId));
  
  
    std::map< G4int,G4double*>* NaIcolMap = NaIHitsCollection->GetMap();
    std::map< G4int,G4double*>::iterator itr;
    for (itr = NaIcolMap->begin(); itr != NaIcolMap->end(); itr++) 
    {
        std::cout << (itr->first) << " " << *(itr->second) << std::endl;

    }
    G4HCofThisEvent *hitsCollOfThisEvent = anEvent->GetHCofThisEvent();
    if(!hitsCollOfThisEvent)
        return;


    G4SDManager* SDmanager2 = G4SDManager::GetSDMpointer();
    G4int fantomcollId = SDmanager2->GetCollectionID("FantomSensitiveDet/sec");
    //std::cout<<fantomcollId << std::endl;
    
    G4THitsMap<G4double>* FantomSecondaries = static_cast<G4THitsMap<G4double>*>( hitsCollOfThisEvent->GetHC(fantomcollId));
  
  
    std::map< G4int,G4double*>* fantomcolMap = FantomSecondaries->GetMap();
    std::map< G4int,G4double*>::iterator itr;
    for (itr = fantomcolMap->begin(); itr != fantomcolMap->end(); itr++) 
    {
	//std::cout << *(itr->second) << std::endl;
	output << *(itr->second) << "\t";
	n+= *(itr->second);
    }
    
    // *(itr->second) << std::endl; //do pliku
    output << SteppingAction::nrOfSec <<std::endl; //do konsoli
    SteppingAction::nrOfSecTotal+=SteppingAction::nrOfSec;
    SteppingAction::nrOfSec=0;*/
    
    output << SteppingAction::nrOfSec <<std::endl;
    SteppingAction::nrOfSec=0;
    
    //G4HCofThisEvent *hitsCollOfThisEvent = anEvent->GetHCofThisEvent();
    //if(!hitsCollOfThisEvent)
     //   return;
    
    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    G4int naICollID=SDman->GetCollectionID("naISD/eDep");

    G4HCofThisEvent* hitsCE = anEvent->GetHCofThisEvent();
    if(!hitsCE)
        return;

    NaIHitsCollection* naIHC = (NaIHitsCollection*)( hitsCE->GetHC(naICollID) );

    G4int nrOfDetectors = naIHC->entries();
    for(G4int i=0; i!=nrOfDetectors; i++)
    {
        G4int moduleIndex = (*naIHC)[i]->GetCopyNr();
        G4double energyDep = (*naIHC)[i]->GetEdep();
        G4double dTime = (*naIHC)[i]->GetTime();
	std::cout << moduleIndex << " " << energyDep << " " << dTime << std::endl;
    }
    /*std::cout << "SUMA:" << std::endl;
    for(G4int i=0; i!=nrOfDetectors; i++)
    {
    	G4int moduleIndex = (*naIHC)[i]->GetCopyNr();
    	std::cout << (*naIHC)[i]->GetEdepTotal() << std::endl;
    }*/
    
}




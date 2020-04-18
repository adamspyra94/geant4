
// $Id: EventAction.cc 15.10.2018 A. Fijalkowska $
//
/// \file EventAction.cc
/// \brief Implementation of the EventAction class
//
//
#include "EventAction.hh"
#include "SteppingAction.hh"

EventAction::EventAction()
{
    output.open("E_Dep_Spine.txt");
}
 
EventAction::~EventAction()
{
    output<<"Energia zdeponowana w kregoslupie"<<"\t"<<SteppingAction::EDepSpineTotal<<"\t"<<"keV"<<std::endl;
    output.close();
}


void EventAction::BeginOfEventAction(const G4Event* anEvent)
{

}
 

void EventAction::EndOfEventAction(const G4Event* anEvent)
{
    output<<anEvent->GetEventID()<<"\t"<<SteppingAction::EDepSpine<<"\t"<<"keV"<<std::endl;
    SteppingAction::EDepSpineTotal+=SteppingAction::EDepSpine;
    SteppingAction::EDepSpine=0;
}




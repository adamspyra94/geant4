//
// $Id: SteppingAction.hh 15.10.2018 A. Fijalkowska $
//
/// \file SteppingAction.hh
/// \brief Definition of the SteppingAction class
//
#ifndef SteppingAction_H
#define SteppingAction_H 1

#include "G4UserSteppingAction.hh"

class SteppingAction : public G4UserSteppingAction
{
  public:
    SteppingAction();
    virtual ~SteppingAction();
    virtual void UserSteppingAction(const G4Step*);
    static double EDepSpine;
    static double EDepSpineTotal;
    static int nrOfSec;
    static int nrOfSecTotal;
  private:
    void PrintStep(const G4Step* theStep);
    
};

#endif

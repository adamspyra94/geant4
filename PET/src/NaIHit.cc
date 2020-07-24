#include "NaIHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include <iomanip>

G4ThreadLocal G4Allocator<NaIHit>* NaIHitAllocator = 0;

NaIHit::NaIHit(G4int copyNrVal): G4VHit()
{
   eDep = 0.;
   trackLength = 0.;
   dTime=0.;
   copyNr = copyNrVal;
}


NaIHit::~NaIHit() {}


NaIHit::NaIHit(const NaIHit& right): G4VHit()
{
  eDep        = right.eDep;
  dTime       = right.dTime;
  trackLength = right.trackLength;
  copyNr = right.copyNr;
}

const NaIHit& NaIHit::operator=(const NaIHit& right)
{
  eDep        = right.eDep;
  dTime       = right.dTime;
  trackLength = right.trackLength;
  copyNr = right.copyNr;
  return *this;
}


G4int NaIHit::operator==(const NaIHit& right) const
{
  return ( this == &right ) ? 1 : 0;
}

void NaIHit::Add_E(G4double energyDep) {
  eDep += energyDep;
}

void NaIHit::Add_T(G4double time) {
  dTime += time;
}

G4double NaIHit::GetEdep() { 
  return eDep; 
}

G4double NaIHit::GetTime() { 
  return dTime; 
}

G4double NaIHit::GetTrackLength() { 
  return trackLength; 
}

G4int NaIHit::GetCopyNr() { 
  return copyNr; 
}

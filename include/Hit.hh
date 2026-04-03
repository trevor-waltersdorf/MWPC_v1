#pragma once
#include "G4VHit.hh"
#include "G4THitsCollection.hh"

class WireHit : public G4VHit {
	public:
		WireHit() {}
		~WireHit() override {}

		void SetCopyNo(G4int no) {fCopyNo = no;}
		void SetEdep(G4double e) {fEdep = e;}

		G4int GetCopyNo() const {return fCopyNo;}
		G4double GetEdep() const {return fEdep;}
		
	private:
		G4int fCopyNo = -1;
		G4double fEdep = 0.;
};

using HitsCollection = G4THitsCollection<WireHit>;

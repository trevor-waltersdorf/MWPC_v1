#include "EventAction.hh"
#include "G4SystemOfUnits.hh"

void EventAction::EndOfEventAction(const G4Event *event) {
	G4HCofThisEvent *hce = event->GetHCofThisEvent();
	if (!hce) return;

	if (fHCID < 0) {
		fHCID = G4SDManager::GetSDMpointer()->GetCollectionID("WireHitsCollection");
	}

	HitsCollection *hc = static_cast<HitsCollection*>(hce->GetHC(fHCID));
	if (!hc) return;

	G4int nHits = hc->entries();
	G4cout << "Event hits: " << nHits << G4endl;

	for (G4int i = 0; i < nHits; i++) {
		WireHit *hit = (*hc)[i];
		G4cout << " Wire " << hit->GetCopyNo() << " Edep = " << hit->GetEdep() /MeV << " MeV" << G4endl;
	}
}

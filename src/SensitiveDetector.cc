#include "SensitiveDetector.hh"
#include "Hit.hh"

SensitiveDetector::SensitiveDetector(G4String name) : G4VSensitiveDetector(name) {
	collectionName.insert("WireHitsCollection");
}

SensitiveDetector::~SensitiveDetector() {}

void SensitiveDetector::Initialize(G4HCofThisEvent *hce) {
	fHitsCollection = new HitsCollection(SensitiveDetectorName, collectionName[0]);

	if (fHCID < 0) {
		fHCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
	}

	hce->AddHitsCollection(fHCID, fHitsCollection);
}

G4bool SensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *) {
    	G4double edep = aStep->GetTotalEnergyDeposit();
	if (edep == 0.) return false;

	G4TouchableHandle touchable = aStep->GetPreStepPoint()->GetTouchableHandle();
    	G4int copyNo = touchable->GetVolume(0)->GetCopyNo();
	
	WireHit *hit = new WireHit();
	hit->SetCopyNo(copyNo);
	hit->SetEdep(edep);
	fHitsCollection->insert(hit);

    	return true;
}

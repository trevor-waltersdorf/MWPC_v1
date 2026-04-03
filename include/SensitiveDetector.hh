#pragma once
#include "G4VSensitiveDetector.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "Hit.hh"

class SensitiveDetector : public G4VSensitiveDetector {
    public:
        SensitiveDetector(G4String);
        ~SensitiveDetector() override;

	void Initialize(G4HCofThisEvent* hce) override;
	G4bool ProcessHits(G4Step* aStep, G4TouchableHistory*) override;

    private:
	HitsCollection* fHitsCollection = nullptr;
	G4int fHCID = -1;
};


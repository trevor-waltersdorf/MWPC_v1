#pragma once
#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "Hit.hh"

class EventAction : public G4UserEventAction {
	public:
		EventAction() = default;
		~EventAction() override = default;

		void EndOfEventAction(const G4Event* event) override;

	private:
		G4int fHCID = -1;
};

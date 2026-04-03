#include "ActionInitialization.hh"
#include "PrimaryGenerator.hh"
#include "EventAction.hh"

ActionInitialization::ActionInitialization() {}

ActionInitialization::~ActionInitialization() {}

void ActionInitialization::BuildForMaster() const {}

void ActionInitialization::Build() const {
    PrimaryGenerator *generator = new PrimaryGenerator();
    SetUserAction(generator);

    EventAction *eventAction = new EventAction();
    SetUserAction(eventAction);
}

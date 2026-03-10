#include "G4ElectricField.hh"
#include "G4ThreeVector.hh"

class ElectricField : public G4ElectricField {
    public:
        ElectricField(G4double radius, G4double lambda) 
            : fRadius(radius), fLambda(lambda) {}
        ~ElectricField() {}
    
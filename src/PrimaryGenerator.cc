#include "PrimaryGenerator.hh"

PrimaryGenerator::PrimaryGenerator(){
    fParticleGun = new G4ParticleGun(1);

    // Particle Type
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition *particle = particleTable->FindParticle("mu+");

    fParticleGun->SetParticleEnergy(4. * GeV);
    fParticleGun->SetParticleDefinition(particle);
}

PrimaryGenerator::~PrimaryGenerator() {
    delete fParticleGun;
}

void PrimaryGenerator::GeneratePrimaries(G4Event *anEvent) {
    // Particle Position
    G4double x = (G4UniformRand()-.5) * 8 * cm;
    G4double y = 0.1 * m;
    G4double z = (G4UniformRand()-.5) * 8 * cm;
    G4ThreeVector pos(x, y, z);

    //Particle Direction
    G4double px = (G4UniformRand()-.5) * .1;
    G4double py = -1.;
    G4double pz = (G4UniformRand()-.5) * .1;
    G4ThreeVector mom(px, py, pz);

    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);
    fParticleGun->GeneratePrimaryVertex(anEvent);
}

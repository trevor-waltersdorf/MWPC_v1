#include "DetectorConstruction.hh"

DetectorConstruction::DetectorConstruction() {
}

DetectorConstruction::~DetectorConstruction() {
}

G4VPhysicalVolume *DetectorConstruction::Construct() {
    G4bool checkOverlaps = true;

    G4NistManager *nist = G4NistManager::Instance();
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_Ar");
    G4Material *leadMat = nist->FindOrBuildMaterial("G4_Pb");
    G4Material *detMat = nist->FindOrBuildMaterial("G4_W");

    G4double xWorld = 0.2 * m;
    G4double yWorld = 0.2 * m;
    G4double zWorld = 0.2 * m;

    G4Box *solidWorld = new G4Box("solidWorld", 0.5 * xWorld, 0.5 * yWorld, 0.5 * zWorld);
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicalWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, checkOverlaps);

    G4double leadSize = 1. * cm;
    bool leadArr[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 0, 0, 1, 1, 0},
        {0, 1, 1, 0, 0, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    G4Box *solidLead = new G4Box("solidLead", 0.5 * leadSize, 0.5 * leadSize, 0.5 * leadSize);
    G4LogicalVolume *logicLead = new G4LogicalVolume(solidLead, leadMat, "logicLead");
    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (leadArr[i][j]) {
                new G4PVPlacement(0, G4ThreeVector((i - 4.) * cm, 0., (j - 4.) * cm), logicLead, "physLead", logicWorld, false, checkOverlaps);
            }
        }
    }

    G4VisAttributes *leadVisAtt = new G4VisAttributes(G4Color(100.0, 100.0, 100.0, 0.75));
    leadVisAtt->SetForceSolid(true);
    logicLead->SetVisAttributes(leadVisAtt);

    G4double wireRadius = 1 * cm;
    G4double wireLength = 10. * cm;
    G4RotationMatrix* rotm = new G4RotationMatrix();
    rotm->rotateY(90.*deg);
    G4double hSpace = 0.5 * cm;
    G4int number = 20;

    G4Tubs *solidDetector = new G4Tubs("solidDetector", 0., wireRadius, 0.5 * wireLength, 0., 360.*deg);
    logicDetector = new G4LogicalVolume(solidDetector, detMat, "logicDetector");

 
    for (int i = 0; i < number; i++) {
        new G4PVPlacement(0, G4ThreeVector((0.5 * i - 4.75) * cm, 3 * cm, 0 * cm), logicDetector, std::to_string(100 + i), logicWorld, false, 100 + i, checkOverlaps);
        new G4PVPlacement(rotm, G4ThreeVector(0 * cm, 3.25 * cm, (0.5 * i - 4.75) * cm), logicDetector, std::to_string(200 + i), logicWorld, false, 200 + i, checkOverlaps);
    }
    for (int i = 0; i < number; i++) {
        new G4PVPlacement(0, G4ThreeVector((0.5 * i - 4.75) * cm, 5 * cm, 0 * cm), logicDetector, std::to_string(300 + i), logicWorld, false, 300 + i, checkOverlaps);
        new G4PVPlacement(rotm, G4ThreeVector(0 * cm, 5.25 * cm, (0.5 * i - 4.75) * cm), logicDetector, std::to_string(400 + i), logicWorld, false, 400 + i, checkOverlaps);
    }
    for (int i = 0; i < number; i++) {
        new G4PVPlacement(0, G4ThreeVector((0.5 * i - 4.75) * cm, -3 * cm, 0 * cm), logicDetector, std::to_string(500 + i), logicWorld, false, 500 + i, checkOverlaps);
        new G4PVPlacement(rotm, G4ThreeVector(0 * cm, -3.25 * cm, (0.5 * i - 4.75) * cm), logicDetector, std::to_string(600 + i), logicWorld, false, 600 + i, checkOverlaps);
    }
    for (int i = 0; i < number; i++) {
        new G4PVPlacement(0, G4ThreeVector((0.5 * i - 4.75) * cm, -5 * cm, 0 * cm), logicDetector, std::to_string(700 + i), logicWorld, false, 700 + i, checkOverlaps);
        new G4PVPlacement(rotm, G4ThreeVector(0 * cm, -5.25 * cm, (0.5 * i - 4.75) * cm), logicDetector, std::to_string(800 + i), logicWorld, false, 800 + i, checkOverlaps);
    }

    G4VisAttributes *detVisAtt = new G4VisAttributes(G4Color(200.0, 200.0, 0.0, 0.75));
    detVisAtt->SetForceSolid(true);
    logicDetector->SetVisAttributes(detVisAtt);

    return physWorld;
}

void DetectorConstruction::ConstructSDandField() {
    SensitiveDetector *sensDet = new SensitiveDetector("SensitiveDetector");
    logicDetector->SetSensitiveDetector(sensDet);
    G4SDManager::GetSDMpointer()->AddNewDetector(sensDet);
}

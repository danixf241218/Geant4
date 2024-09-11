#include "DetectorConstruction.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Orb.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "SensitiveDetector.hh"
#include "G4SDManager.hh"



DetectorConstruction::DetectorConstruction()
{
  
}


G4VPhysicalVolume* DetectorConstruction::Construct()
{
// Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();

  // Envelope parameters
  //
  G4double env_sizeXY = 5*cm, env_sizeZ = 5*cm;
  
  //Gases
  
  G4Material* Argon = nist->FindOrBuildMaterial("G4_Ar");
  G4Material* Neon = nist->FindOrBuildMaterial("G4_Ne"); 
  G4Material* Helio = nist->FindOrBuildMaterial("G4_He");
  G4Material* Xenon = nist->FindOrBuildMaterial("G4_Xe");
  G4Material* oxigeno = nist->FindOrBuildMaterial("G4_O");
  G4Material* agua= nist->FindOrBuildMaterial("G4_WATER");
  
  //materiales del detector
  
  G4Material *GaN = new G4Material("GaN", 6.1*g/cm3,2);
  GaN->AddElement(nist->FindOrBuildElement("Ga"),1);
  GaN->AddElement(nist->FindOrBuildElement("N"),1);
  
  G4Material *SiC = new G4Material("SiC",3.21*g/cm3,2);
  SiC->AddElement(nist->FindOrBuildElement("Si"),1);
  SiC->AddElement(nist->FindOrBuildElement("C"),1);
  
  G4Material *hBN = new G4Material("hBN",2.27*g/cm3,2);
  hBN->AddElement(nist->FindOrBuildElement("B"),1);
  hBN->AddElement(nist->FindOrBuildElement("N"),1);
  
  

  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //
  // World
  //
  G4double world_sizeXY = 5*env_sizeXY; // poner a 200 para ver aire
  G4double world_sizeZ  = 5*env_sizeZ;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");

  auto solidWorld = new G4Box("World",                           // its name
     world_sizeXY,  world_sizeXY, world_sizeZ);  // its size

  auto logicWorld = new G4LogicalVolume(solidWorld,  // its solid
    world_mat,                                       // its material
    "World");                                        // its name

  auto physiWorld = new G4PVPlacement(nullptr,  // no rotation
    G4ThreeVector(),                           // at (0,0,0)
    logicWorld,                                // its logical volume
    "World",                                   // its name
    nullptr,                                   // its mother  volume
    false,                                     // no boolean operation
    0,                                         // copy number
    checkOverlaps);                            // overlaps checking

  //
  // Envelope
  //
        G4double pRmin_env = 0.*cm;
	G4double pRmax_env = 1.001*cm;
	G4double pSPhi = 0.*deg;
    	G4double pDPhi = 360.*deg;
    	G4double pSTheta = 0.*deg;
    	G4double pDTheta = 180.*deg;
    	
    	G4double pRmindetector = 1.001*cm;
    	G4double pRmaxdetector = 1.002*cm;

  
  
  
  auto solidEnv = new G4Sphere("Envelope",                    // its name
    pRmin_env, pRmax_env, pSPhi,pDPhi,pSTheta,pDTheta);  // its size

  auto logicEnv = new G4LogicalVolume(solidEnv,  // its solid
    oxigeno,                                     // its material gas
    "Envelope");                                 // its name

  new G4PVPlacement(nullptr,  // no rotation
    G4ThreeVector(),          // at (0,0,0)
    logicEnv,                 // its logical volume
    "Envelope",               // its name
    logicWorld,               // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checking
    
    // volumen sensible o detector
    
    auto solidDetector = new G4Sphere("Detector",pRmindetector,pRmaxdetector,pSPhi,pDPhi, pSTheta, pDTheta);
    auto logicDetector = new G4LogicalVolume(solidDetector,SiC,"Detector");
    new G4PVPlacement(nullptr,G4ThreeVector(),logicDetector,"Detector",logicWorld,false,0,checkOverlaps);
   
   G4ThreeVector pos1 = G4ThreeVector();

   
  

  //materiales de la fuente 
  
   G4Material *Plutonium_matshape2 = new G4Material("Plutonium", 94, 236, 19.84*g/cm3);
    G4Material* Aluminio = nist->FindOrBuildMaterial("G4_Al");
   
    
  G4ThreeVector pos2 = G4ThreeVector();

  // seccion esferica fuente 
  
  G4double shape2_rmina =  0.*cm; 
  G4double shape2_rmaxb =  1*cm; 
  
  
  
  auto solidShape2 = new G4Sphere("Shape2", shape2_rmina, shape2_rmaxb,
    pSPhi,pDPhi, pSTheta, pDTheta);

  auto logicShape2 = new G4LogicalVolume(solidShape2,  // its solid
    Aluminio,                                       // its material
   "Shape2");                                         // its name

  new G4PVPlacement(nullptr,  // no rotation
    pos2,                     // at position
    logicShape2,              // its logical volume
    "Shape2",                 // its name
    logicEnv,                 // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checking



  //
  
   fScoringVolume = logicDetector;
  //always return the physical World
  //  
  return physiWorld;
}

void DetectorConstruction::ConstructSDandField()
{

     auto *SensDet= new SensitiveDetector("SensitiveDetector");
     G4SDManager::GetSDMpointer()->AddNewDetector(SensDet);
     SetSensitiveDetector("Detector", SensDet);
     //logicDetector->SetSensitiveDetector(SensDet);

}


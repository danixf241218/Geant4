#include "SteppingAction.hh"
#include "DetectorConstruction.hh"
#include "CLHEP/Units/PhysicalConstants.h"

SteppingAction::SteppingAction(EventAction *eventAction)
{
    fEventAction = eventAction;
}

SteppingAction::~SteppingAction()
{}

void SteppingAction::UserSteppingAction(const G4Step *step)
{

	
	 
	const G4LogicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
	
	const DetectorConstruction *detectorConstruction = static_cast<const DetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
	
	G4LogicalVolume *fScoringVolume = detectorConstruction->GetScoringVolume();
	

	if(volume !=fScoringVolume)
	return; 

        
        const G4ParticleDefinition* particleDef = step->GetTrack()->GetDefinition();
        
	G4double cgen = particleDef->GetPDGCharge();
	
	if(cgen > 0){
	fEventAction->AddCgen(cgen);
	}


        if (particleDef->GetParticleName() == "alpha"){
        G4double length = step->GetStepLength();
        fEventAction->AddLength(length);}
       
        
        G4double edep = step->GetTotalEnergyDeposit();
        fEventAction->AddEdep(edep);
        
        if (volume == detectorConstruction->GetScoringVolume()){
	G4double time = step->GetPreStepPoint()->GetGlobalTime();
	G4double power = edep / time;
	fEventAction->AddPowerAbsorbed(power);
  
}
}



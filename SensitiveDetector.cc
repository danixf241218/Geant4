#include "SensitiveDetector.hh"
#include "SteppingAction.hh"
#include "EventAction.hh"

SensitiveDetector::SensitiveDetector(G4String name): G4VSensitiveDetector(name)
{}


SensitiveDetector::~SensitiveDetector()
{}


G4bool SensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
	G4Track *track = aStep->GetTrack();
	
	//track->SetTrackStatus(fStopAndKill); 
	
	G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
	G4StepPoint *postStepPoint = aStep->GetPostStepPoint();
	
	G4ThreeVector posAlpha = preStepPoint->GetPosition();
	G4ThreeVector momAlpha = preStepPoint->GetMomentum();
	
	
	G4cout << "alpha position:" << posAlpha << G4endl;
	
	
	const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
	
	G4int copyNo = touchable->GetCopyNumber();
	
	G4VPhysicalVolume *physVol = touchable->GetVolume();
	G4ThreeVector posDetector = physVol->GetTranslation();
	
	G4cout << "detector position:" << posDetector << G4endl;
	
	
	
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
	
	
	man->FillNtupleIColumn(1, 0, evt);
	man->FillNtupleDColumn(1, 1, posAlpha[0]);
	man->FillNtupleDColumn(1, 2, posAlpha[1]);
	man->FillNtupleDColumn(1, 3, posAlpha[2]);
	man->AddNtupleRow(1);
	
	man->FillNtupleIColumn(2, 0, evt);
	//man->FillNtupleDColumn(2, 1, posDetector[0]);
	//man->FillNtupleDColumn(2, 2, posDetector[1]);
	//man->FillNtupleDColumn(2, 3, posDetector[2]);
	man->AddNtupleRow(2);
	




	

	
	return true;
}

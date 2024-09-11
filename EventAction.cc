#include "EventAction.hh"

EventAction::EventAction(RunAction*)
{
	fEdep = 0.;
	fCgen = 0.;
	fLength = 0.;
	fPowerAbsorbed = 0.;
	}

EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event*)
{
	fEdep = 0.;
	fCgen = 0.;
	fLength = 0.;
	fPowerAbsorbed = 0.;
	}

void EventAction::EndOfEventAction(const G4Event*)
{
	G4cout << "Energia depositada:" << fEdep << G4endl;
	G4cout << "Cantidad de cargas generadas:" << fCgen << G4endl;
	G4cout << "Distancia recorrida en este paso: " << fLength*1000 << " um" << G4endl;
	G4cout << "Potencia absorbida:" << fPowerAbsorbed << G4endl;
	
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	man->FillNtupleDColumn(0, 0, fEdep);
	man->FillNtupleDColumn(0, 1, fCgen);
	man->FillNtupleDColumn(0, 2, fLength);
	man->FillNtupleDColumn(0, 3, fPowerAbsorbed);
	man->AddNtupleRow(0);
	}
	

#include "RunAction.hh"


RunAction::RunAction()
{}
	

RunAction::~RunAction()
{}

void RunAction::BeginOfRunAction(const G4Run*)
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	man->OpenFile("output.root");
	
	
	man->CreateNtuple("Distance", "Distance");
	man->CreateNtupleDColumn("fEdep"); 
	man->CreateNtupleDColumn("fCgen");
	man->CreateNtupleDColumn("fLength");
	man->CreateNtupleDColumn("fPowerAbsorbed");
    	man->FinishNtuple(0);
	
	
	man->CreateNtuple("Hits", "Hits");
	man->CreateNtupleIColumn("fEvent");
    	man->CreateNtupleDColumn("fx");
    	man->CreateNtupleDColumn("fy");
    	man->CreateNtupleDColumn("fz");
    	man->FinishNtuple(1);
    	
    	man->CreateNtuple("Scoring", "Scoring");
    	man->CreateNtupleDColumn("fEvent");
    	man->FinishNtuple(2);
    	
    	
	
	

}

void RunAction::EndOfRunAction(const G4Run*)
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();
    	man->Write();
    	man->CloseFile();
}

#include "PhysicsList.hh"


PhysicsList :: PhysicsList()
{
G4int verb = 0;
    SetVerboseLevel(verb);
	RegisterPhysics( new G4EmStandardPhysics());
	RegisterPhysics( new G4DecayPhysics(verb));
	RegisterPhysics( new G4RadioactiveDecayPhysics(verb));
	RegisterPhysics( new G4HadronPhysicsQGSP_BERT_HP);
	RegisterPhysics( new G4IonElasticPhysics(verb));
	RegisterPhysics( new G4IonPhysics(verb));
	
}

PhysicsList::~PhysicsList()
{

}

/*/ Método ConstructProcess
void PhysicsList::ConstructProcess() {
    // Llama a los constructores de procesos de las partículas base
    AddTransportation();
    
    // Construye los procesos electromagnéticos estándar
    G4EmStandardPhysics* emPhysics = new G4EmStandardPhysics();
    emPhysics->ConstructProcess();
}
// Método SetCuts (puedes ajustar los cortes según sea necesario)
void PhysicsList::SetCuts() {
    // Ajusta los cortes para diferentes tipos de partículas
    SetCutsWithDefault();
}*/

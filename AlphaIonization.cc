#include "AlphaIonization.hh"

G4alphaIonisation::G4alphaIonisation(const G4String& name)
:G4VEnergyLossProcess(name),theParticle(0),isInitialised(false)

{
	G4Exception("G4alphaIonisation::G4alphaIonisation","em0007",JustWarning, "The process is not ready for use - incorrect results are expected");
	
 SetLinearLossLimit(0.02);
 SetStepFunction(0.2, 0.01*mm);

SetProcessSubType(fIonisation);

mass = 0.0;
ratio = 0.0;
eth = 8*MeV;

}

 G4alphaIonisation::~G4alphaIonisation()
 {}
 
 G4bool G4alphaIonisation::IsApplicable(const G4ParticleDefinition& p)
 {
   return (!p.IsShortLived() &&
        std::fabs(p.GetPDGCharge()/CLHEP::eplus - 2) < 0.01);
 }
 
 G4double G4alphaIonisation::MinPrimaryEnergy(const G4ParticleDefinition*, 
                                              const G4Material*, 
                                              G4double cut)
                                              {
   G4double x = 0.5*cut/electron_mass_c2;
   G4double gam = x*ratio + std::sqrt((1. + x)*(1. + x*ratio*ratio));
  return mass*(gam - 1.0);
}

void G4alphaIonisation::InitialiseEnergyLossProcess(
                       const G4ParticleDefinition* part,
                       const G4ParticleDefinition* bpart)
                       
{
   if(!isInitialised) {
 
     theParticle = part;
     G4String pname = part->GetParticleName();
 
     // define base particle
     const G4ParticleDefinition* theBaseParticle = 0;
     if(bpart == 0) { 
       if(pname != "alpha") { theBaseParticle = G4Alpha::Alpha(); }
     } else { theBaseParticle = bpart; }
 
     mass  = part->GetPDGMass();
     ratio = electron_mass_c2/mass;
 
     SetBaseParticle(theBaseParticle);
     SetSecondaryParticle(G4Electron::Electron());
 
     if (!EmModel(1)) { SetEmModel(new G4BraggIonModel(), 1); }
     EmModel(1)->SetLowEnergyLimit(MinKinEnergy());
 
     // model limit defined for alpha
     eth = (EmModel(1)->HighEnergyLimit())*mass/proton_mass_c2;
     EmModel(1)->SetHighEnergyLimit(eth);
 
     if (!FluctModel()) { SetFluctModel(new G4UniversalFluctuation()); }
    AddEmModel(1, EmModel(1), new G4IonFluctuations());
 
     if (!EmModel(2)) { SetEmModel(new G4BetheBlochModel(),2); }  
     EmModel(2)->SetLowEnergyLimit(eth);
     EmModel(2)->SetHighEnergyLimit(MaxKinEnergy());
     AddEmModel(2, EmModel(2), FluctModel());    
 
     isInitialised = true;
   }
 }
 

 
 void G4alphaIonisation::PrintInfo()
 {}


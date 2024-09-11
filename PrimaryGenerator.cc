#include "PrimaryGenerator.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4Alpha.hh"
#include "G4GeneralParticleSource.hh"





PrimaryGenerator::PrimaryGenerator()
{

    G4int n_particle = 1;
    fParticleGun = new G4ParticleGun(n_particle); 
    G4ParticleDefinition* particle = G4Alpha::AlphaDefinition();
    fParticleGun->SetParticleDefinition(particle);
    
    
};
 
PrimaryGenerator::~PrimaryGenerator()
{


    delete fParticleGun;
};

void PrimaryGenerator:: GeneratePrimaries(G4Event *anEvent)
{
	
    G4double shape2_rmaxb = 1* cm;
    
    G4double theta = acos(2.0 * G4UniformRand() - 1.0);  
    G4double phi = 2.0 * CLHEP::pi * G4UniformRand(); 
    G4double x0 =  shape2_rmaxb* sin(theta) * cos(phi);
    G4double y0 =  shape2_rmaxb * sin(theta) * sin(phi);
    G4double z0 =  shape2_rmaxb * cos(theta);
    
    G4ThreeVector position(x0, y0, z0);
    fParticleGun->SetParticlePosition(position);

	
   fParticleGun->SetParticleMomentumDirection(G4ThreeVector(x0,y0,z0));
   G4ThreeVector pos(0.,0.,0.);
  
 
    G4double sigmaE1=0.0168226 *MeV;
    G4double sigmaE2=0.0120315 *MeV;
    G4double sigmaE3=0.0327423 *MeV;
    G4double sigmaE4=0.0418377 *MeV;
    G4double sigmaE5=0.00836474 *MeV;
    G4double sigmaE6=0.00160725 *MeV;


    G4double Et= fabs (CLHEP::RandGauss::shoot(5.71783*MeV, sigmaE1))+(CLHEP::RandGauss::shoot(5.71313*MeV, sigmaE2))+(CLHEP::RandGauss::shoot(5.75952*MeV, sigmaE3))+(CLHEP::RandGauss::shoot(5.80495*MeV, sigmaE4))+(CLHEP::RandGauss::shoot(5.75321*MeV, sigmaE5))+(CLHEP::RandGauss::shoot(5.76264*MeV, sigmaE6));
    
    G4double Ei = Et/6;
    fParticleGun->SetParticleEnergy(Ei *MeV); 
  
  
     // inserataer aqui la del plutonio 236 emisor de alphas puro
        
    G4cout << "Ei=" << Ei << G4endl;


  fParticleGun->GeneratePrimaryVertex(anEvent);





};



//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file B1PrimaryGeneratorAction.cc
/// \brief Implementation of the B1PrimaryGeneratorAction class

// Here is where the particle definitions, energies, etc. are defined.

#include "B1PrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4IonTable.hh"
#include <stdlib.h>
#include <fstream>
#include <cmath>
#include <iostream>

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1PrimaryGeneratorAction::B1PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0),
  fParticleGun2(0),
  fEnvelopeBox(0)
{

  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);
  fParticleGun2  = new G4ParticleGun(n_particle);

  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();

  // Define the particle type and location.
  G4String particleName;
  G4String particleName2;
  G4ParticleDefinition* particle
    = particleTable->FindParticle(particleName="e+");
    G4ParticleDefinition* particle2
      = particleTable->FindParticle(particleName2="e-");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun2->SetParticleDefinition(particle2);
  G4double size = 0.8;
  G4double x0 = 24.0259286*cm;
  G4double y0 = 24.0259286*cm;
  G4double z0 = 61.944725*cm;

  fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));
  fParticleGun2->SetParticlePosition(G4ThreeVector(x0,y0,z0));

  // Open the files that will contain the weights after calculation.
  roseE.open("roseE.txt");
  roseE.precision(10);
	roseE << fixed;

  roseM.open("roseM.txt");
  roseM.precision(10);
	roseM << fixed;

  stieblingE.open("stieblingE.txt");
  stieblingE.precision(10);
	stieblingE << fixed;

  stieblingM.open("stieblingM.txt");
  stieblingM.precision(10);
	stieblingM << fixed;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1PrimaryGeneratorAction::~B1PrimaryGeneratorAction()
{
  delete fParticleGun;
  delete fParticleGun2;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{

  G4double envSizeXY = 0;
  G4double envSizeZ = 0;

  if (!fEnvelopeBox)
  {
    G4LogicalVolume* envLV
      = G4LogicalVolumeStore::GetInstance()->GetVolume("Envelope");
    if ( envLV ) fEnvelopeBox = dynamic_cast<G4Box*>(envLV->GetSolid());
  }

  // check for errors
  if ( fEnvelopeBox ) {
    envSizeXY = fEnvelopeBox->GetXHalfLength()*2.;
    envSizeZ = fEnvelopeBox->GetZHalfLength()*2.;
  }
  else  {
    G4ExceptionDescription msg;
    msg << "Envelope volume of box shape not found.\n";
    msg << "Perhaps you have changed geometry.\n";
    msg << "The gun will be place at the center.";
    G4Exception("B1PrimaryGeneratorAction::GeneratePrimaries()",
     "MyCode0002",JustWarning,msg);
  }

  /////////////////////////////////////////////////////////////////

  // The following calculation of the weights that will be applied to the energy
  // distributions after running the simulation is taken from a calculation
  // performed by Dr. Azuelos at Montreal in a simulation he performed.
  // These weighting calculations are exported to files and used in post-processing.
  // These calculations are based on equations from M.E. Rose, Phys. Rev. 76 (1949) 678
  // and Stiebing, K E et al. Journal of Physics G: Nuclear and Particle Physics 30.2 (2004): 165–180

  // first electron in cone around  y axis
  G4double cthmax =1.;
  G4double cthmin = 0.9063; //25 degrees
  G4double costh1= cthmin + (cthmax - cthmin) * G4UniformRand();
  G4double phi1 = 2 * 3.1416 * G4UniformRand();
  G4double sinth1 = sqrt( 1. - costh1 * costh1);
  // cone around y axis
  G4double py1 = costh1;
  G4double px1 = sinth1*cos(phi1);
  G4double pz1 = sinth1*sin(phi1);
  // back to world coordinates
  costh1=pz1;
  phi1=atan2(py1,px1);


  // positron generated at random

  cthmax = 1.0 ;
  cthmin = -1.0;
  G4double costh2 = cthmin + (cthmax - cthmin) * G4UniformRand();
  G4double phi2 = 2 * 3.1416 * G4UniformRand();
  G4double sinth2 = sqrt( 1. - costh2 * costh2);
  G4double pz2 = costh2;
  G4double px2 = sinth2 * cos(phi2);
  G4double py2 = sinth2*sin(phi2);

  // calculate the weight, based on  M.E. Rose, Phys. Rev. 76 (1949) 678
  G4double cosdth = px1*px2 + py1*py2 + pz1*pz2;  // cos of opening angle
  //  G4double akmin = 25.;
  //G4double akmax=40.;
  G4double akmin = 35.;   // 18 MeV
  G4double akmax=35.;
  G4double ak = akmin + (akmax-akmin) * G4UniformRand();   // choose ak randomly
  G4double wp = 1. + (ak-2.) * G4UniformRand();      // choose wp randomly
  G4double wm = ak - wp;
  G4double pp = sqrt(wp*wp-1.);
  G4double pm = sqrt(wm*wm-1.);
  G4double pmz = pm * cosdth;
  G4double pmx = pm * sqrt(1.-cosdth*cosdth);
  G4double  q = sqrt((pp+pmz)*(pp+pmz) + pmx*pmx);
  G4double alpha = 1./137;
  G4double pi = 3.14159265;
  //  Rose weight  E1
  G4double t1 = 2*alpha/(2*pi) * (pp*pm/q) * (q/ak) / pow((ak*ak-q*q),2); // eq.(7) of Rose
  G4double t2 = 3*(wp*wm+1-pp*pm*cosdth/3.);
  G4double t3 = (q*q/(ak*ak)-2.) * (wp*wm-1.+pp*pm*cosdth);
  G4double weightRoseE1 = t1*(t2+t3) ;   // arbitrary normalization ( d(cosdth), d(ak), d(wp) )

  //Stiebing weight, E1
  t1 = alpha/(16*pow(pi*ak,3))*pp*pm;
  t2 = 4*ak*ak/pow((ak*ak-q*q),2) + 2 * (pp*pp+pm*pm)/(ak*ak-q*q) +1;
  G4double   weightStieblingE1 = t1*t2 ;   // arbitrary normalization ( d(cosdth), d(ak), d(wp) )

  // Rose M1
  t1 = 2*alpha/pi * (pp*pm/q) * pow((q/ak),3)  /    pow((ak*ak-q*q),2);
  t2 = 1.+ wp*wm -  pp*pm/(q*q) * (pm+pp*cosdth)*(pp+pm*cosdth);
  G4double   weightRoseM1 = t1*t2 ;   // arbitrary normalization ( d(cosdth), d(ak), d(wp) )

  //Stiebing weight, M1
  t1 = alpha/(16*pow(pi*ak,3))*pp*pm;
  t2 = 4*ak*ak/pow((ak*ak-q*q),2) + 2 * (pp*pp+pm*pm)/(ak*ak-q*q) -1;
  G4double   weightStieblingM1 = t1*t2 ;   // arbitrary normalization ( d(cosdth), d(ak), d(wp) )


  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(px1,py1,costh1));
  fParticleGun->SetParticleEnergy((wp-1.)*0.511);

  fParticleGun2->SetParticleMomentumDirection(G4ThreeVector(px2,py2,costh2));
  fParticleGun2->SetParticleEnergy((wm-1.)*0.511);


  // export results to data files
  roseE << weightRoseE1;
  roseE << "\r\n";

  roseM << weightRoseM1;
  roseM << "\r\n";

  stieblingE << weightStieblingE1;
  stieblingE << "\r\n";

  stieblingM << weightStieblingM1;
  stieblingM << "\r\n";


  ////////////////////////////////////////////////////////////////


  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;



    G4ParticleDefinition* particle
      = particleTable->FindParticle(particleName="e-");
    fParticleGun->SetParticleDefinition(particle);


     particle
      = particleTable->FindParticle(particleName="e+");
    fParticleGun2->SetParticleDefinition(particle);


    fParticleGun->GeneratePrimaryVertex(anEvent);
    fParticleGun2->GeneratePrimaryVertex(anEvent);



}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

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
#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include "G4DecayTable.hh"
#include "G4GeneralPhaseSpaceDecay.hh"


using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1PrimaryGeneratorAction::B1PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0),
  fParticleGun2(0),
  fEnvelopeBox(0)
{



  srand(time(NULL));

  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);
  fParticleGun2  = new G4ParticleGun(n_particle);

  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();

  // Define the particle type and location.
  // G4String particleName;
  // G4String particleName2;
  // G4ParticleDefinition* particle
  //   = particleTable->FindParticle(particleName="e+");
  //   G4ParticleDefinition* particle2
  //     = particleTable->FindParticle(particleName2="e-");
  // fParticleGun->SetParticleDefinition(particle);
  // fParticleGun2->SetParticleDefinition(particle2);
  G4double size = 0.8;
  G4double x0 = 0;
  G4double y0 = 0;
  G4double z0 = 0;

  fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));
  fParticleGun2->SetParticlePosition(G4ThreeVector(x0,y0,z0));

  eventTracker.open("data2.txt");
  string line3;
  while(getline(eventTracker, line3)) {
    events += 1;
  }


  string line2;

  ipcIn.open("ipcNumber.txt");
  while (getline(ipcIn, line2)) {
    count += 3;
  }

  string line3new;
  x17In.open("x17Number.txt");
  while (getline(x17In, line3new)) {
    x17count += 4;
  }

  ipcNumber.open("ipcNumber.txt", fstream::app);
  angles.open("priorRose.txt");
  string line;
  while (getline(angles, line)) {
    angleData.push_back(atof(line.c_str()));
  }

  x17Number.open("x17Number.txt", fstream::app);
  x17angles.open("x17angles.txt");
  string line4;
  while (getline(x17angles, line4)) {
    x17angleData.push_back(atof(line4.c_str()));
  }


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

  events = events + 1;
  if (events % 10000 == 0) {
    cout << events << endl;
  }

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
  //Import energies and weighted angles
  // if (events % 10000 == 0) {
  //
  // }

  G4int ipcx17Prob = rand() % 10000000 + 1;

  if (ipcx17Prob > 14814) {

    ipcEvents += 1;

    ipcNumber << events << endl;

    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();

    G4String particleName;
    G4String particleName2;
    G4ParticleDefinition* particle
      = particleTable->FindParticle(particleName="e+");
      G4ParticleDefinition* particle2
        = particleTable->FindParticle(particleName2="e-");
    fParticleGun->SetParticleDefinition(particle);
    fParticleGun2->SetParticleDefinition(particle2);

    G4double positronE;
    G4double electronE;
    G4double angle;


    positronE = angleData.at(count);
    electronE = angleData.at(count+1);
    angle = angleData.at(count+2);
    count = count + 3;



    G4double pi = 3.14159265;

    G4double u = 1 - 2*G4UniformRand();

    G4double theta = 2*pi*G4UniformRand();

    G4double x = sqrt(1-u*u)*cos(theta);
    G4double y = sqrt(1-u*u)*sin(theta);
    G4double z = u;


    G4ThreeVector positronV = G4ThreeVector(x, y, z);

    G4double zElectron = cos(angle);
    G4double phi = 2*pi*G4UniformRand();
    G4double xElectron = sqrt(1-zElectron*zElectron)*cos(phi);
    G4double yElectron = sqrt(1-zElectron*zElectron)*sin(phi);

    G4ThreeVector electronV;
    electronV.setX(xElectron);
    electronV.setY(yElectron);
    electronV.setZ(zElectron);
    electronV.rotateUz(positronV);


    fParticleGun->SetParticleMomentumDirection(positronV);
    fParticleGun->SetParticleEnergy(positronE);


    fParticleGun2->SetParticleMomentumDirection(electronV);
    fParticleGun2->SetParticleEnergy(electronE);

    fParticleGun->GeneratePrimaryVertex(anEvent);
    fParticleGun2->GeneratePrimaryVertex(anEvent);

  }
  else if (ipcx17Prob <= 14814) {
    x17Events += 1;

    x17Number << events << endl;

    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();

    G4String particleName;
    G4String particleName2;
    G4ParticleDefinition* particle
      = particleTable->FindParticle(particleName="e+");
      G4ParticleDefinition* particle2
        = particleTable->FindParticle(particleName2="e-");
    fParticleGun->SetParticleDefinition(particle);
    fParticleGun2->SetParticleDefinition(particle2);

    G4double positronE;
    G4double electronE;
    G4double angle;

    positronE = x17angleData.at(x17count);
    electronE = x17angleData.at(x17count+1);
    angle = x17angleData.at(x17count+3);
    angle = acos(angle);

    angle = 2.33672;

    x17count = x17count + 4;



    G4double pi = 3.14159265;

    G4double u = 1 - 2*G4UniformRand();

    G4double theta = 2*pi*G4UniformRand();

    G4double x = sqrt(1-u*u)*cos(theta);
    G4double y = sqrt(1-u*u)*sin(theta);
    G4double z = u;


    G4ThreeVector positronV = G4ThreeVector(x, y, z);

    G4double zElectron = cos(angle);
    G4double phi = 2*pi*G4UniformRand();
    G4double xElectron = sqrt(1-zElectron*zElectron)*cos(phi);
    G4double yElectron = sqrt(1-zElectron*zElectron)*sin(phi);

    G4ThreeVector electronV;
    electronV.setX(xElectron);
    electronV.setY(yElectron);
    electronV.setZ(zElectron);
    electronV.rotateUz(positronV);


    fParticleGun->SetParticleMomentumDirection(positronV);
    fParticleGun->SetParticleEnergy(positronE);


    fParticleGun2->SetParticleMomentumDirection(electronV);
    fParticleGun2->SetParticleEnergy(electronE);

    fParticleGun->GeneratePrimaryVertex(anEvent);
    fParticleGun2->GeneratePrimaryVertex(anEvent);

  }

  else {
    G4int Z = 4, A = 8;
    G4double ionCharge   = 0.*eplus;
    G4double excitEnergy = 18.15*MeV;

    G4ParticleDefinition* ion
       = G4IonTable::GetIonTable()->GetIon(Z,A,excitEnergy);
    fParticleGun->SetParticleDefinition(ion);
    fParticleGun->SetParticleCharge(ionCharge);
    fParticleGun->SetParticleEnergy(0*eV);

    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));
    fParticleGun->GeneratePrimaryVertex(anEvent);

  }








  ////////////////////////////////////////////////////////////////









}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

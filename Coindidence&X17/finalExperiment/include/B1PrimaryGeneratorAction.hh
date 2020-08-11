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
/// \file B1PrimaryGeneratorAction.hh
/// \brief Definition of the B1PrimaryGeneratorAction class

#ifndef B1PrimaryGeneratorAction_h
#define B1PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"
#include <fstream>
#include "G4DecayTable.hh"
#include "G4GeneralPhaseSpaceDecay.hh"
using namespace std;

class G4ParticleGun;
class G4Event;
class G4Box;

/// The primary generator action class with particle gun.

class B1PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    B1PrimaryGeneratorAction();
    virtual ~B1PrimaryGeneratorAction();
    // Define the output file streams for the weights
    ofstream roseE;
    ofstream roseM;
    ofstream stieblingE;
    ofstream stieblingM;
    vector<double> angleData;
    vector<double> x17angleData;
    G4int count = 0;
    G4int x17count = 0;
    G4int stuff = 0;
    G4int events = 0;

    ifstream angles;
    ifstream x17angles;
    ifstream ipcIn;
    ifstream x17In;
    ofstream ipcNumber;
    ofstream x17Number;
    ifstream eventTracker;
    G4DecayTable* x17decay;
    G4GeneralPhaseSpaceDecay* x17channel;
    G4ParticleDefinition* x17;


    G4double energy = 0.;
    G4int ipcEvents = 0;
    G4int x17Events = 0;

    // method from the base class
    virtual void GeneratePrimaries(G4Event*);

    // method to access particle guns for electron and positron
    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }
    const G4ParticleGun* GetParticleGun2() const { return fParticleGun2; }

  private:
    G4ParticleGun*  fParticleGun;
    G4ParticleGun* fParticleGun2;
    G4Box* fEnvelopeBox;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

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
/// \file B1SteppingAction.hh
/// \brief Definition of the B1SteppingAction class

#ifndef B1SteppingAction_h
#define B1SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"
#include <fstream>
#include "G4PVPlacement.hh"
#include "B1PrimaryGeneratorAction.hh"
using namespace std;

class B1EventAction;

class G4LogicalVolume;

/// Stepping action class

class B1SteppingAction : public G4UserSteppingAction
{
  public:
    B1SteppingAction(B1EventAction* eventAction);
    virtual ~B1SteppingAction();
    ofstream output;
    G4int four = 0;
    G4int five = 0;

    // method from the base class
    virtual void UserSteppingAction(const G4Step*);


  private:
    B1EventAction*  fEventAction;
    G4LogicalVolume* fScoringVolume;
    G4LogicalVolume* fScoringVolume2;
    G4LogicalVolume* fScoringVolume3;
    G4LogicalVolume* fScoringVolume4;
    G4LogicalVolume* fScoringVolume5;
    G4LogicalVolume* fScoringVolume6;
    G4LogicalVolume* fScoringVolume7;
    G4LogicalVolume* fScoringVolume8;
    G4LogicalVolume* fScoringVolume9;
    G4LogicalVolume* fScoringVolume10;
    G4LogicalVolume* fScoringVolume11;
    G4LogicalVolume* fScoringVolume12;
    G4LogicalVolume* fScoringVolume13;
    G4LogicalVolume* fScoringVolume14;
    G4LogicalVolume* fScoringVolume15;
    G4LogicalVolume* fScoringVolume16;
    G4LogicalVolume* fScoringVolume17;
    G4LogicalVolume* fScoringVolume18;
    G4PVPlacement* chambphys;
    const B1PrimaryGeneratorAction* generatorAction;



};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

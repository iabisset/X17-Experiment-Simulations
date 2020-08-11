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
/// \file B1EventAction.cc
/// \brief Implementation of the B1EventAction class

#include "B1EventAction.hh"
#include "B1RunAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1EventAction::B1EventAction(B1RunAction* runAction)
: G4UserEventAction(),
  fRunAction(runAction),
  fEdep(0.),
  fEdep2(0.),
  fEdep3(0.),
  fEdep4(0.),
  fEdep5(0.),
  fEdep6(0.),
  fEdep7(0.),
  fEdep8(0.),
  fEdep9(0.),
  fEdep10(0.),
  fEdep11(0.),
  fEdep12(0.),
  fEdep13(0.),
  fEdep14(0.),
  fEdep15(0.),
  fEdep16(0.),
  fEdep17(0.),
  fEdep18(0.)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1EventAction::~B1EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1EventAction::BeginOfEventAction(const G4Event*)
{
  fEdep = 0.;
  fEdep2 = 0.;
  fEdep3 = 0.;
  fEdep4 = 0.;
  fEdep5 = 0.;
  fEdep6 = 0.;
  fEdep7 = 0.;
  fEdep8 = 0.;
  fEdep9 = 0.;
  fEdep10 = 0.;
  fEdep11 = 0.;
  fEdep12 = 0.;
  fEdep13 = 0.;
  fEdep14 = 0.;
  fEdep15 = 0.;
  fEdep16 = 0.;
  fEdep17 = 0.;
  fEdep18 = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1EventAction::EndOfEventAction(const G4Event*)
{
  // accumulate statistics in run action
  fRunAction->AddEdep(fEdep);
  fRunAction->AddEdep2(fEdep2);
  fRunAction->AddEdep3(fEdep3);
  fRunAction->AddEdep4(fEdep4);
  fRunAction->AddEdep5(fEdep5);
  fRunAction->AddEdep6(fEdep6);
  fRunAction->AddEdep7(fEdep7);
  fRunAction->AddEdep8(fEdep8);
  fRunAction->AddEdep9(fEdep9);
  fRunAction->AddEdep10(fEdep10);
  fRunAction->AddEdep11(fEdep11);
  fRunAction->AddEdep12(fEdep12);
  fRunAction->AddEdep13(fEdep13);
  fRunAction->AddEdep14(fEdep14);
  fRunAction->AddEdep15(fEdep15);
  fRunAction->AddEdep16(fEdep16);
  fRunAction->AddEdep17(fEdep17);
  fRunAction->AddEdep18(fEdep18);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

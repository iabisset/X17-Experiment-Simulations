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
/// \file B1SteppingAction.cc
/// \brief Implementation of the B1SteppingAction class

#include "B1SteppingAction.hh"
#include "B1EventAction.hh"
#include "B1DetectorConstruction.hh"
#include "B1PrimaryGeneratorAction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include <iostream>
#include <cmath>
using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1SteppingAction::B1SteppingAction(B1EventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fScoringVolume(0),
  fScoringVolume2(0),
  fScoringVolume3(0),
  fScoringVolume4(0),
  fScoringVolume5(0),
  fScoringVolume6(0),
  fScoringVolume7(0),
  fScoringVolume8(0),
  fScoringVolume9(0),
  fScoringVolume10(0),
  fScoringVolume11(0),
  fScoringVolume12(0),
  fScoringVolume13(0),
  fScoringVolume14(0),
  fScoringVolume15(0),
  fScoringVolume16(0),
  fScoringVolume17(0),
  fScoringVolume18(0)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1SteppingAction::~B1SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1SteppingAction::UserSteppingAction(const G4Step* step)
{
  if (!fScoringVolume) {
    const B1DetectorConstruction* detectorConstruction
      = static_cast<const B1DetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
        generatorAction
         = static_cast<const B1PrimaryGeneratorAction*>
           (G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());

    fScoringVolume = detectorConstruction->GetScoringVolume();
    fScoringVolume2 = detectorConstruction->GetScoringVolume2();
    fScoringVolume3 = detectorConstruction->GetScoringVolume3();
    fScoringVolume4 = detectorConstruction->GetScoringVolume4();
    fScoringVolume5 = detectorConstruction->GetScoringVolume5();
    fScoringVolume6 = detectorConstruction->GetScoringVolume6();
    fScoringVolume7 = detectorConstruction->GetScoringVolume7();
    fScoringVolume8 = detectorConstruction->GetScoringVolume8();
    fScoringVolume9 = detectorConstruction->GetScoringVolume9();
    fScoringVolume10 = detectorConstruction->GetScoringVolume10();
    fScoringVolume11 = detectorConstruction->GetScoringVolume11();
    fScoringVolume12 = detectorConstruction->GetScoringVolume12();
    fScoringVolume13 = detectorConstruction->GetScoringVolume13();
    fScoringVolume14 = detectorConstruction->GetScoringVolume14();
    fScoringVolume15 = detectorConstruction->GetScoringVolume15();
    fScoringVolume16 = detectorConstruction->GetScoringVolume16();
    fScoringVolume17 = detectorConstruction->GetScoringVolume17();
    fScoringVolume18 = detectorConstruction->GetScoringVolume18();

    output.open("hits.txt", fstream::app);
    output.precision(10);
    output << fixed;


  }



  // get volume of the current step
  G4LogicalVolume* volume
    = step->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();



  if (step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume()->GetName() != "World" && (step->GetTrack()->GetParticleDefinition()->GetParticleName() == "e+" || step->GetTrack()->GetParticleDefinition()->GetParticleName() == "e-") && (step->GetPreStepPoint()->GetPhysicalVolume()->GetLogicalVolume() !=  fScoringVolume17) && (step->GetPostStepPoint()->GetPhysicalVolume()->GetLogicalVolume() == fScoringVolume17)) {
    G4ThreeVector hit = step->GetPostStepPoint()->GetPosition();
    G4double length = sqrt((hit.getX()*hit.getX()) + (hit.getY()*hit.getY()) + (hit.getZ()*hit.getZ()));

    output << hit.getX()/length << "\r\n" << hit.getY()/length << "\r\n" << hit.getZ()/length << "\r\n" << generatorAction->events << "\r\n" <<step->GetTrack()->GetParticleDefinition()->GetParticleName();
    output << "\r\n";
    output.flush();
  }


  // check if we are in scoring volume
  if (volume != fScoringVolume && volume != fScoringVolume2 && volume != fScoringVolume3 && volume != fScoringVolume4 && volume != fScoringVolume5 && volume != fScoringVolume6
   && volume != fScoringVolume7 && volume != fScoringVolume8 && volume != fScoringVolume9 && volume != fScoringVolume10 && volume != fScoringVolume11 && volume != fScoringVolume12
  && volume != fScoringVolume13 && volume != fScoringVolume14 && volume != fScoringVolume15 && volume != fScoringVolume16 && volume != fScoringVolume17 && volume != fScoringVolume18) {
    return;
  }
  else if (volume == fScoringVolume) {
    // collect energy deposited in this step if in first detector
    G4double edepStep = step->GetTotalEnergyDeposit();
    // if ((step->GetTrack()->GetParticleDefinition()->GetParticleName() == "e-" || step->GetTrack()->GetParticleDefinition()->GetParticleName() == "e+")) {
    //   output << step->GetTrack()->GetParticleDefinition()->GetParticleName() << endl;
    // }
    //G4double kEnergy = step->GetTrack()->GetKineticEnergy();
    //step->GetTrack()->SetKineticEnergy(0);
    fEventAction->AddEdep(edepStep);

  }
  else if (volume == fScoringVolume2) {
    // collect energy deposited in this step if in second detector
    // if (step->GetTrack()->GetParticleDefinition()->GetParticleName() == "gamma") {
    //   step->GetTrack()->SetPosition(G4ThreeVector(0, 0, 0));
    //   step->GetTrack()->SetMomentumDirection(G4ThreeVector(0, 0, 1));
    //
    // }
    G4double edepStep = step->GetTotalEnergyDeposit();
    fEventAction->AddEdep2(edepStep);
  }
  else if (volume == fScoringVolume3) {
    // collect energy deposited in this step if in second detector
    // if (step->GetTrack()->GetParticleDefinition()->GetParticleName() == "gamma") {
    //   step->GetTrack()->SetPosition(G4ThreeVector(0, 0, 0));
    //   step->GetTrack()->SetMomentumDirection(G4ThreeVector(0, 0, 1));
    //
    // }
    G4double edepStep = step->GetTotalEnergyDeposit();
    fEventAction->AddEdep3(edepStep);
  }
  else if (volume == fScoringVolume4) {
    // collect energy deposited in this step if in second detector
    // if (step->GetTrack()->GetParticleDefinition()->GetParticleName() == "gamma") {
    //   step->GetTrack()->SetPosition(G4ThreeVector(0, 0, 0));
    //   step->GetTrack()->SetMomentumDirection(G4ThreeVector(0, 0, 1));
    //
    // }
    G4double edepStep = step->GetTotalEnergyDeposit();
    fEventAction->AddEdep4(edepStep);
  }
  else if (volume == fScoringVolume5) {
    // collect energy deposited in this step if in second detector
    // if (step->GetTrack()->GetParticleDefinition()->GetParticleName() == "gamma") {
    //   step->GetTrack()->SetPosition(G4ThreeVector(0, 0, 0));
    //   step->GetTrack()->SetMomentumDirection(G4ThreeVector(0, 0, 1));
    //
    // }
    G4double edepStep = step->GetTotalEnergyDeposit();
    fEventAction->AddEdep5(edepStep);
  }
  else if (volume == fScoringVolume6) {
    // collect energy deposited in this step if in second detector
    // if (step->GetTrack()->GetParticleDefinition()->GetParticleName() == "gamma") {
    //   step->GetTrack()->SetPosition(G4ThreeVector(0, 0, 0));
    //   step->GetTrack()->SetMomentumDirection(G4ThreeVector(0, 0, 1));
    //
    // }
    G4double edepStep = step->GetTotalEnergyDeposit();
    fEventAction->AddEdep6(edepStep);
  }
  else if (volume == fScoringVolume7) {
    // collect energy deposited in this step if in second detector
    // if (step->GetTrack()->GetParticleDefinition()->GetParticleName() == "gamma") {
    //   step->GetTrack()->SetPosition(G4ThreeVector(0, 0, 0));
    //   step->GetTrack()->SetMomentumDirection(G4ThreeVector(0, 0, 1));
    //
    // }
    G4double edepStep = step->GetTotalEnergyDeposit();
    fEventAction->AddEdep7(edepStep);
  }
  else if (volume == fScoringVolume8) {
    // collect energy deposited in this step if in second detector
    // if (step->GetTrack()->GetParticleDefinition()->GetParticleName() == "gamma") {
    //   step->GetTrack()->SetPosition(G4ThreeVector(0, 0, 0));
    //   step->GetTrack()->SetMomentumDirection(G4ThreeVector(0, 0, 1));
    //
    // }
    G4double edepStep = step->GetTotalEnergyDeposit();
    fEventAction->AddEdep8(edepStep);
  }
  else if (volume == fScoringVolume9) {
    // collect energy deposited in this step if in second detector
    // if (step->GetTrack()->GetParticleDefinition()->GetParticleName() == "gamma") {
    //   step->GetTrack()->SetPosition(G4ThreeVector(0, 0, 0));
    //   step->GetTrack()->SetMomentumDirection(G4ThreeVector(0, 0, 1));
    //
    // }
    G4double edepStep = step->GetTotalEnergyDeposit();
    fEventAction->AddEdep9(edepStep);
  }
  else if (volume == fScoringVolume10) {
    // collect energy deposited in this step if in second detector
    // if (step->GetTrack()->GetParticleDefinition()->GetParticleName() == "gamma") {
    //   step->GetTrack()->SetPosition(G4ThreeVector(0, 0, 0));
    //   step->GetTrack()->SetMomentumDirection(G4ThreeVector(0, 0, 1));
    //
    // }
    G4double edepStep = step->GetTotalEnergyDeposit();
    fEventAction->AddEdep10(edepStep);
  }
  else if (volume == fScoringVolume11) {
    // collect energy deposited in this step if in second detector
    // if (step->GetTrack()->GetParticleDefinition()->GetParticleName() == "gamma") {
    //   step->GetTrack()->SetPosition(G4ThreeVector(0, 0, 0));
    //   step->GetTrack()->SetMomentumDirection(G4ThreeVector(0, 0, 1));
    //
    // }
    G4double edepStep = step->GetTotalEnergyDeposit();
    fEventAction->AddEdep11(edepStep);
  }
  else if (volume == fScoringVolume12) {
    // collect energy deposited in this step if in second detector
    // if (step->GetTrack()->GetParticleDefinition()->GetParticleName() == "gamma") {
    //   step->GetTrack()->SetPosition(G4ThreeVector(0, 0, 0));
    //   step->GetTrack()->SetMomentumDirection(G4ThreeVector(0, 0, 1));
    //
    // }
    G4double edepStep = step->GetTotalEnergyDeposit();
    fEventAction->AddEdep12(edepStep);
  }
  else if (volume == fScoringVolume13) {
    // collect energy deposited in this step if in second detector
    // if (step->GetTrack()->GetParticleDefinition()->GetParticleName() == "gamma") {
    //   step->GetTrack()->SetPosition(G4ThreeVector(0, 0, 0));
    //   step->GetTrack()->SetMomentumDirection(G4ThreeVector(0, 0, 1));
    //
    // }
    G4double edepStep = step->GetTotalEnergyDeposit();
    fEventAction->AddEdep13(edepStep);
  }
  else if (volume == fScoringVolume14) {
    // collect energy deposited in this step if in second detector
    // if (step->GetTrack()->GetParticleDefinition()->GetParticleName() == "gamma") {
    //   step->GetTrack()->SetPosition(G4ThreeVector(0, 0, 0));
    //   step->GetTrack()->SetMomentumDirection(G4ThreeVector(0, 0, 1));
    //
    // }
    G4double edepStep = step->GetTotalEnergyDeposit();
    fEventAction->AddEdep14(edepStep);
  }
  else if (volume == fScoringVolume15) {
    // collect energy deposited in this step if in second detector
    // if (step->GetTrack()->GetParticleDefinition()->GetParticleName() == "gamma") {
    //   step->GetTrack()->SetPosition(G4ThreeVector(0, 0, 0));
    //   step->GetTrack()->SetMomentumDirection(G4ThreeVector(0, 0, 1));
    //
    // }
    G4double edepStep = step->GetTotalEnergyDeposit();
    fEventAction->AddEdep15(edepStep);
  }
  else if (volume == fScoringVolume16) {
    // collect energy deposited in this step if in second detector
    // if (step->GetTrack()->GetParticleDefinition()->GetParticleName() == "gamma") {
    //   step->GetTrack()->SetPosition(G4ThreeVector(0, 0, 0));
    //   step->GetTrack()->SetMomentumDirection(G4ThreeVector(0, 0, 1));
    //
    // }
    G4double edepStep = step->GetTotalEnergyDeposit();
    fEventAction->AddEdep16(edepStep);
  }
  else if (volume == fScoringVolume17) {
    // collect energy deposited in this step if in second detector

    G4double edepStep = step->GetTotalEnergyDeposit();
    fEventAction->AddEdep17(edepStep);
  }
  else if (volume == fScoringVolume18) {
    // collect energy deposited in this step if in second detector
    // if (step->GetTrack()->GetParticleDefinition()->GetParticleName() == "gamma") {
    //   step->GetTrack()->SetPosition(G4ThreeVector(0, 0, 0));
    //   step->GetTrack()->SetMomentumDirection(G4ThreeVector(0, 0, 1));
    //
    // }
    G4double edepStep = step->GetTotalEnergyDeposit();
    fEventAction->AddEdep18(edepStep);
  }




}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

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
/// \file B1EventAction.hh
/// \brief Definition of the B1EventAction class

#ifndef B1EventAction_h
#define B1EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class B1RunAction;

/// Event action class
///

class B1EventAction : public G4UserEventAction
{
  public:
    B1EventAction(B1RunAction* runAction);
    virtual ~B1EventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    void AddEdep(G4double edep) { fEdep += edep; }
    void AddEdep2(G4double edep2) { fEdep2 += edep2; }
    void AddEdep3(G4double edep3) { fEdep3 += edep3; }
    void AddEdep4(G4double edep4) { fEdep4 += edep4; }
    void AddEdep5(G4double edep5) { fEdep5 += edep5; }
    void AddEdep6(G4double edep6) { fEdep6 += edep6; }
    void AddEdep7(G4double edep7) { fEdep7 += edep7; }
    void AddEdep8(G4double edep8) { fEdep8 += edep8; }
    void AddEdep9(G4double edep9) { fEdep9 += edep9; }
    void AddEdep10(G4double edep10) { fEdep10 += edep10; }
    void AddEdep11(G4double edep11) { fEdep11 += edep11; }
    void AddEdep12(G4double edep12) { fEdep12 += edep12; }
    void AddEdep13(G4double edep13) { fEdep13 += edep13; }
    void AddEdep14(G4double edep14) { fEdep14 += edep14; }
    void AddEdep15(G4double edep15) { fEdep15 += edep15; }
    void AddEdep16(G4double edep16) { fEdep16 += edep16; }
    void AddEdep17(G4double edep17) { fEdep17 += edep17; }
    void AddEdep18(G4double edep18) { fEdep18 += edep18; }


  private:
    B1RunAction* fRunAction;
    G4double     fEdep;
    G4double     fEdep2;
    G4double     fEdep3;
    G4double     fEdep4;
    G4double     fEdep5;
    G4double     fEdep6;
    G4double     fEdep7;
    G4double     fEdep8;
    G4double     fEdep9;
    G4double     fEdep10;
    G4double     fEdep11;
    G4double     fEdep12;
    G4double     fEdep13;
    G4double     fEdep14;
    G4double     fEdep15;
    G4double     fEdep16;
    G4double     fEdep17;
    G4double     fEdep18;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

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
/// \file B1RunAction.hh
/// \brief Definition of the B1RunAction class

#ifndef B1RunAction_h
#define B1RunAction_h 1

#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include "globals.hh"
#include "G4RunManager.hh"
#include <fstream>
#include <vector>

using namespace std;

class G4Run;

/// Run action class
///
/// In EndOfRunAction(), it calculates the dose in the selected volume
/// from the energy deposit accumulated via stepping and event actions.
/// The computed dose is then printed on the screen.

class B1RunAction : public G4UserRunAction
{
  public:
    // Declare output streams for the energy deposit data for each scintillator
    ofstream out;
    ofstream out2;
    ofstream out3;
    ofstream out4;
    ofstream out5;
    ofstream out6;
    ofstream out7;
    ofstream out8;
    ofstream out9;
    ofstream out10;
    ofstream out11;
    ofstream out12;
    ofstream out13;
    ofstream out14;
    ofstream out15;
    ofstream out16;
    ofstream out17;
    ofstream out18;

    B1RunAction();
    virtual ~B1RunAction();

    vector<double> data1;
    vector<double> data2;
    vector<double> data3;
    vector<double> data4;
    vector<double> data5;
    vector<double> data6;
    vector<double> data7;
    vector<double> data8;
    vector<double> data9;
    vector<double> data10;
    vector<double> data11;
    vector<double> data12;
    vector<double> data13;
    vector<double> data14;
    vector<double> data15;
    vector<double> data16;
    vector<double> data17;
    vector<double> data18;

    // virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);

    void AddEdep (G4double edep);
    void AddEdep2 (G4double edep);
    void AddEdep3 (G4double edep);
    void AddEdep4 (G4double edep);
    void AddEdep5 (G4double edep);
    void AddEdep6 (G4double edep);
    void AddEdep7 (G4double edep);
    void AddEdep8 (G4double edep);
    void AddEdep9 (G4double edep);
    void AddEdep10 (G4double edep);
    void AddEdep11 (G4double edep);
    void AddEdep12 (G4double edep);
    void AddEdep13 (G4double edep);
    void AddEdep14 (G4double edep);
    void AddEdep15 (G4double edep);
    void AddEdep16 (G4double edep);
    void AddEdep17 (G4double edep);
    void AddEdep18 (G4double edep);

  private:
    // Energy depositions for each scintillator
    G4Accumulable<G4double> fEdep;
    G4Accumulable<G4double> fEdep2;
    G4Accumulable<G4double> fEdep3;
    G4Accumulable<G4double> fEdep4;
    G4Accumulable<G4double> fEdep5;
    G4Accumulable<G4double> fEdep6;
    G4Accumulable<G4double> fEdep7;
    G4Accumulable<G4double> fEdep8;
    G4Accumulable<G4double> fEdep9;
    G4Accumulable<G4double> fEdep10;
    G4Accumulable<G4double> fEdep11;
    G4Accumulable<G4double> fEdep12;
    G4Accumulable<G4double> fEdep13;
    G4Accumulable<G4double> fEdep14;
    G4Accumulable<G4double> fEdep15;
    G4Accumulable<G4double> fEdep16;
    G4Accumulable<G4double> fEdep17;
    G4Accumulable<G4double> fEdep18;
};

#endif

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
/// \file B1RunAction.cc
/// \brief Implementation of the B1RunAction class

#include "B1RunAction.hh"
#include "B1PrimaryGeneratorAction.hh"
#include "B1DetectorConstruction.hh"
// #include "B1Run.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include <iostream>
using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1RunAction::B1RunAction()
: G4UserRunAction(),
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
{


  // Register accumulable to the accumulable manager
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->RegisterAccumulable(fEdep);
  accumulableManager->RegisterAccumulable(fEdep2);
  accumulableManager->RegisterAccumulable(fEdep3);
  accumulableManager->RegisterAccumulable(fEdep4);
  accumulableManager->RegisterAccumulable(fEdep5);
  accumulableManager->RegisterAccumulable(fEdep6);
  accumulableManager->RegisterAccumulable(fEdep7);
  accumulableManager->RegisterAccumulable(fEdep8);
  accumulableManager->RegisterAccumulable(fEdep9);
  accumulableManager->RegisterAccumulable(fEdep10);
  accumulableManager->RegisterAccumulable(fEdep11);
  accumulableManager->RegisterAccumulable(fEdep12);
  accumulableManager->RegisterAccumulable(fEdep13);
  accumulableManager->RegisterAccumulable(fEdep14);
  accumulableManager->RegisterAccumulable(fEdep15);
  accumulableManager->RegisterAccumulable(fEdep16);
  accumulableManager->RegisterAccumulable(fEdep17);
  accumulableManager->RegisterAccumulable(fEdep18);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1RunAction::~B1RunAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1RunAction::BeginOfRunAction(const G4Run*)
{

  // open data files that energy deposition results will be sent to.
  out.open("data.txt", fstream::app);
  out.precision(4);
	out << fixed;

  out2.open("data2.txt", fstream::app);
  out2.precision(4);
	out2 << fixed;

  out3.open("data3.txt", fstream::app);
  out3.precision(4);
	out3 << fixed;

  out4.open("data4.txt", fstream::app);
  out4.precision(4);
	out4 << fixed;

  out5.open("data5.txt", fstream::app);
  out5.precision(4);
	out5 << fixed;

  out6.open("data6.txt", fstream::app);
  out6.precision(4);
	out6 << fixed;

  out7.open("data7.txt", fstream::app);
  out7.precision(4);
	out7 << fixed;

  out8.open("data8.txt", fstream::app);
  out8.precision(4);
	out8 << fixed;

  out9.open("data9.txt", fstream::app);
  out9.precision(4);
	out9 << fixed;

  out10.open("data10.txt", fstream::app);
  out10.precision(4);
	out10 << fixed;

  out11.open("data11.txt", fstream::app);
  out11.precision(4);
	out11 << fixed;

  out12.open("data12.txt", fstream::app);
  out12.precision(4);
	out12 << fixed;

  out13.open("data13.txt", fstream::app);
  out13.precision(4);
	out13 << fixed;

  out14.open("data14.txt", fstream::app);
  out14.precision(4);
	out14 << fixed;

  out15.open("data15.txt", fstream::app);
  out15.precision(4);
	out15 << fixed;

  out16.open("data16.txt", fstream::app);
  out16.precision(4);
	out16 << fixed;

  out17.open("data17.txt", fstream::app);
  out17.precision(4);
	out17 << fixed;

  out18.open("data18.txt", fstream::app);
  out18.precision(4);
	out18 << fixed;
  // inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);

  // reset accumulables to their initial values
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Reset();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1RunAction::EndOfRunAction(const G4Run* run)
{
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;

  // Merge accumulables
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Merge();

  G4double edep  = fEdep.GetValue();
  G4double edep2 = fEdep2.GetValue();
  G4double edep3 = fEdep3.GetValue();
  G4double edep4 = fEdep4.GetValue();
  G4double edep5 = fEdep5.GetValue();
  G4double edep6 = fEdep6.GetValue();
  G4double edep7 = fEdep7.GetValue();
  G4double edep8 = fEdep8.GetValue();
  G4double edep9 = fEdep9.GetValue();
  G4double edep10 = fEdep10.GetValue();
  G4double edep11 = fEdep11.GetValue();
  G4double edep12 = fEdep12.GetValue();
  G4double edep13 = fEdep13.GetValue();
  G4double edep14 = fEdep14.GetValue();
  G4double edep15 = fEdep15.GetValue();
  G4double edep16 = fEdep16.GetValue();
  G4double edep17 = fEdep17.GetValue();
  G4double edep18 = fEdep18.GetValue();


  // Run conditions

  const B1PrimaryGeneratorAction* generatorAction
   = static_cast<const B1PrimaryGeneratorAction*>
     (G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
  G4String runCondition;
  G4String runCondition2;

  if (generatorAction)
  {
    const G4ParticleGun* particleGun = generatorAction->GetParticleGun();
    const G4ParticleGun* particleGun2 = generatorAction->GetParticleGun2();

    runCondition += particleGun->GetParticleDefinition()->GetParticleName();
    runCondition += " of ";

    runCondition2 += particleGun2->GetParticleDefinition()->GetParticleName();
    runCondition2 += " of ";

    G4double particleEnergy = particleGun->GetParticleEnergy();
    runCondition += G4BestUnit(particleEnergy,"Energy");

    G4double particleEnergy2 = particleGun2->GetParticleEnergy();
    runCondition2 += G4BestUnit(particleEnergy2,"Energy");

  }

  // Print information to the console
  if (IsMaster()) {
    G4cout
     << G4endl
     << "--------------------End of Global Run-----------------------";
  }
  else {
    G4cout
     << G4endl
     << "--------------------End of Local Run------------------------";
  }

  G4cout
     << G4endl
     << " The run consists of " << nofEvents << " "<< runCondition
     << G4endl
     << " Cumulated energy per run, in fixed volume : "
     << G4BestUnit(edep,"Energy")
     << G4endl
     << "------------------------------------------------------------"
     << G4endl
     << G4endl;

   G4cout
      << G4endl
      << " The run consists of " << nofEvents << " "<< runCondition2
      << G4endl
      << " Cumulated energy per run, in variable volume : "
      << G4BestUnit(edep2,"Energy")
      << G4endl
      << "------------------------------------------------------------"
      << G4endl
      << G4endl;

      for (int i = 0; i < data1.size(); ++i) {
        out << data1.at(i);
        out << "\r\n";
        out.flush();
      }
      for (int i = 0; i < data2.size(); ++i) {
        out2 << data2.at(i);
        out2 << "\r\n";
        out2.flush();
      }
      for (int i = 0; i < data3.size(); ++i) {
        out3 << data3.at(i);
        out3 << "\r\n";
        out3.flush();
      }
      for (int i = 0; i < data4.size(); ++i) {
        out4 << data4.at(i);
        out4 << "\r\n";
        out4.flush();
      }
      for (int i = 0; i < data5.size(); ++i) {
        out5 << data5.at(i);
        out5 << "\r\n";
        out5.flush();
      }
      for (int i = 0; i < data6.size(); ++i) {
        out6 << data6.at(i);
        out6 << "\r\n";
        out6.flush();
      }
      for (int i = 0; i < data7.size(); ++i) {
        out7 << data7.at(i);
        out7 << "\r\n";
        out7.flush();
      }
      for (int i = 0; i < data8.size(); ++i) {
        out8 << data8.at(i);
        out8 << "\r\n";
        out8.flush();
      }
      for (int i = 0; i < data9.size(); ++i) {
        out9 << data9.at(i);
        out9 << "\r\n";
        out9.flush();
      }
      for (int i = 0; i < data10.size(); ++i) {
        out10 << data10.at(i);
        out10 << "\r\n";
        out10.flush();
      }
      for (int i = 0; i < data11.size(); ++i) {
        out11 << data11.at(i);
        out11 << "\r\n";
        out11.flush();
      }
      for (int i = 0; i < data12.size(); ++i) {
        out12 << data12.at(i);
        out12 << "\r\n";
        out12.flush();
      }
      for (int i = 0; i < data13.size(); ++i) {
        out13 << data13.at(i);
        out13 << "\r\n";
        out13.flush();
      }
      for (int i = 0; i < data14.size(); ++i) {
        out14 << data14.at(i);
        out14 << "\r\n";
        out14.flush();
      }
      for (int i = 0; i < data15.size(); ++i) {
        out15 << data15.at(i);
        out15 << "\r\n";
        out15.flush();
      }
      for (int i = 0; i < data16.size(); ++i) {
        out16 << data16.at(i);
        out16 << "\r\n";
        out16.flush();
      }
      for (int i = 0; i < data17.size(); ++i) {
        out17 << data17.at(i);
        out17 << "\r\n";
        out17.flush();
      }
      for (int i = 0; i < data18.size(); ++i) {
        out18 << data18.at(i);
        out18 << "\r\n";
        out18.flush();
      }


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1RunAction::AddEdep(G4double edep)
{

  // output energy of an event to the file for detector 1.
  out << edep;
  out << "\r\n";
  out.flush();

  //data1.push_back(edep);

  fEdep  += edep;
}

void B1RunAction::AddEdep2(G4double edep)
{
  // output energy of an event to the file for detector 2.
  out2 << edep;
  out2 << "\r\n";
  out2.flush();

  //data2.push_back(edep);

  fEdep2  += edep;

}

void B1RunAction::AddEdep3(G4double edep)
{
  // output energy of an event to the file for detector 2.
  out3 << edep;
  out3 << "\r\n";
  out3.flush();

  //data3.push_back(edep);

  fEdep3  += edep;

}

void B1RunAction::AddEdep4(G4double edep)
{
  // output energy of an event to the file for detector 2.
  out4 << edep;
  out4 << "\r\n";
  out4.flush();

  //data4.push_back(edep);

  fEdep4  += edep;

}

void B1RunAction::AddEdep5(G4double edep)
{
  // output energy of an event to the file for detector 2.
  out5 << edep;
  out5 << "\r\n";
  out5.flush();

  //data5.push_back(edep);

  fEdep5  += edep;

}

void B1RunAction::AddEdep6(G4double edep)
{
  // output energy of an event to the file for detector 2.
  out6 << edep;
  out6 << "\r\n";
  out6.flush();

  //data6.push_back(edep);

  fEdep6  += edep;

}

void B1RunAction::AddEdep7(G4double edep)
{
  // output energy of an event to the file for detector 2.
  out7 << edep;
  out7 << "\r\n";
  out7.flush();

  //data7.push_back(edep);

  fEdep7  += edep;

}

void B1RunAction::AddEdep8(G4double edep)
{
  // output energy of an event to the file for detector 2.
  out8 << edep;
  out8 << "\r\n";
  out8.flush();

  //data8.push_back(edep);

  fEdep8  += edep;

}

void B1RunAction::AddEdep9(G4double edep)
{
  // output energy of an event to the file for detector 2.
  out9 << edep;
  out9 << "\r\n";
  out9.flush();

  //data9.push_back(edep);

  fEdep9  += edep;

}

void B1RunAction::AddEdep10(G4double edep)
{
  // output energy of an event to the file for detector 2.
  out10 << edep;
  out10 << "\r\n";
  out10.flush();

  //data10.push_back(edep);

  //fEdep10  += edep;

}

void B1RunAction::AddEdep11(G4double edep)
{
  // output energy of an event to the file for detector 2.
  out11 << edep;
  out11 << "\r\n";
  out11.flush();

  //data11.push_back(edep);

  fEdep11  += edep;

}

void B1RunAction::AddEdep12(G4double edep)
{
  // output energy of an event to the file for detector 2.
  out12 << edep;
  out12 << "\r\n";
  out12.flush();

  //data12.push_back(edep);

  fEdep12  += edep;

}

void B1RunAction::AddEdep13(G4double edep)
{
  // output energy of an event to the file for detector 2.
  out13 << edep;
  out13 << "\r\n";
  out13.flush();

  //data13.push_back(edep);

  fEdep13  += edep;

}

void B1RunAction::AddEdep14(G4double edep)
{
  // output energy of an event to the file for detector 2.
  out14 << edep;
  out14 << "\r\n";
  out14.flush();

  //data14.push_back(edep);

  fEdep14  += edep;

}

void B1RunAction::AddEdep15(G4double edep)
{
  // output energy of an event to the file for detector 2.
  out15 << edep;
  out15 << "\r\n";
  out15.flush();

  //data15.push_back(edep);

  fEdep15  += edep;

}

void B1RunAction::AddEdep16(G4double edep)
{
  // output energy of an event to the file for detector 2.
  out16 << edep;
  out16 << "\r\n";
  out16.flush();

  //data16.push_back(edep);

  fEdep16  += edep;

}

void B1RunAction::AddEdep17(G4double edep)
{
  // output energy of an event to the file for detector 2.
  out17 << edep;
  out17 << "\r\n";
  out17.flush();

  //data17.push_back(edep);

  fEdep17  += edep;

}

void B1RunAction::AddEdep18(G4double edep)
{
  // output energy of an event to the file for detector 2.
  out18 << edep;
  out18 << "\r\n";
  out18.flush();

  //data18.push_back(edep);

  fEdep18  += edep;

}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

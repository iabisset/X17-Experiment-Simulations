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
/// \file B1DetectorConstruction.hh
/// \brief Definition of the B1DetectorConstruction class

#ifndef B1DetectorConstruction_h
#define B1DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4VSDFilter.hh"
#include "G4PVPlacement.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

/// Detector construction class to define materials and geometry.

class B1DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    B1DetectorConstruction();
    virtual ~B1DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();

    G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }
    G4LogicalVolume* GetScoringVolume2() const { return fScoringVolume2; }
    G4LogicalVolume* GetScoringVolume3() const { return fScoringVolume3; }
    G4LogicalVolume* GetScoringVolume4() const { return fScoringVolume4; }
    G4LogicalVolume* GetScoringVolume5() const { return fScoringVolume5; }
    G4LogicalVolume* GetScoringVolume6() const { return fScoringVolume6; }
    G4LogicalVolume* GetScoringVolume7() const { return fScoringVolume7; }
    G4LogicalVolume* GetScoringVolume8() const { return fScoringVolume8; }
    G4LogicalVolume* GetScoringVolume9() const { return fScoringVolume9; }
    G4LogicalVolume* GetScoringVolume10() const { return fScoringVolume10; }
    G4LogicalVolume* GetScoringVolume11() const { return fScoringVolume11; }
    G4LogicalVolume* GetScoringVolume12() const { return fScoringVolume12; }
    G4LogicalVolume* GetScoringVolume13() const { return fScoringVolume13; }
    G4LogicalVolume* GetScoringVolume14() const { return fScoringVolume14; }
    G4LogicalVolume* GetScoringVolume15() const { return fScoringVolume15; }
    G4LogicalVolume* GetScoringVolume16() const { return fScoringVolume16; }
    G4LogicalVolume* GetScoringVolume17() const { return fScoringVolume17; }
    G4LogicalVolume* GetScoringVolume18() const { return fScoringVolume18; }




  protected:
    // declare scoring volumes
    G4LogicalVolume*  fScoringVolume;
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
  

    G4bool  fCheckOverlaps; // option to activate checking of volumes overlaps
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

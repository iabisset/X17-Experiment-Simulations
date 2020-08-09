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
/// \file B1DetectorConstruction.cc
/// \brief Implementation of the B1DetectorConstruction class


// Here, the geometries and materials are defined. This simulation consists
// of a chamber and two detectors to pick up coincident events of electrons
// and positrons.

#include "B1DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VSolid.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/framework/XMLPScanToken.hpp>
#include <xercesc/parsers/SAXParser.hpp>

#include <xercesc/util/XMLString.hpp>
#include <xercesc/sax/AttributeList.hpp>
#include <xercesc/sax/SAXParseException.hpp>
#include "G4GDMLParser.hh"



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::B1DetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0),
  fScoringVolume2(0),

  fWireCylinderLogical(NULL),
  fCheckOverlaps(true)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::~B1DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B1DetectorConstruction::Construct()
{

  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();

  // Envelope parameters
  //
  G4double env_sizeXY = 200*cm, env_sizeZ = 200*cm;


  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  // All materials in this simulation apart from the world volume are
  // polystyrene
  G4Material* poly = nist->FindOrBuildMaterial("G4_POLYSTYRENE");

  // vacuum material definition for the world volume
  G4int nel;
  G4double A, Z;
  G4Element* elN  = new G4Element("Nitrogen","N",  Z=7.,  A= 14.00674*g/mole);
  G4Element* elO  = new G4Element("Oxygen",  "O",  Z=8.,  A= 15.9994*g/mole);
  G4double density2 = 1.e-25*g/cm3;
  G4Material* Vacuum = new G4Material("Vacuum", density2, nel=2);
  Vacuum-> AddElement(elN, .7);
  Vacuum-> AddElement(elO, .3);



  // Defining the world volume


    G4double world_sizeXY = 1.2*env_sizeXY;
    G4double world_sizeZ  = 1.2*env_sizeZ;


  G4Box* solidWorld =
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size

  G4LogicalVolume* logicWorld =
    new G4LogicalVolume(solidWorld,          //its solid
                        Vacuum,           //its material
                        "World");            //its name

  G4VPhysicalVolume* physWorld =
  new G4PVPlacement(0,                     //no rotation
                    G4ThreeVector(),       //at (0,0,0)
                    logicWorld,            //its logical volume
                    "World",               //its name
                    0,                     //its mother  volume
                    false,                 //no boolean operation
                    0,                     //copy number
                    checkOverlaps);        //overlaps checking

//
// Envelope
//
G4Box* solidEnv =
  new G4Box("Envelope",                    //its name
      0.5*env_sizeXY, 0.5*env_sizeXY, 0.5*env_sizeZ); //its size

G4LogicalVolume* logicEnv =
  new G4LogicalVolume(solidEnv,            //its solid
                      Vacuum,             //its material
                      "Envelope");         //its name

new G4PVPlacement(0,                       //no rotation
                  G4ThreeVector(),         //at (0,0,0)
                  logicEnv,                //its logical volume
                  "Envelope",              //its name
                  logicWorld,              //its mother  volume
                  false,                   //no boolean operation
                  0,                       //copy number
                  checkOverlaps);          //overlaps checking


   // Definition of the beam chamber the positron will be incident on in coincident events
   G4VSolid* variableDetector = new G4Box("variableDetector", 3.5*cm, 6*cm, 3.5*cm);
   G4LogicalVolume* variableDetectorLogical = new G4LogicalVolume(variableDetector, poly,"variableLog");
   G4VPhysicalVolume* variablePhysical = new G4PVPlacement(0,
                                                        G4ThreeVector((24.0259286)*cm, (24.0259286+6+8)*cm, 61.944725*cm),
                                                        variableDetectorLogical,
                                                      "variablePhysical",
                                                      logicEnv,
                                                      false,
                                                       0,
                                                       checkOverlaps);

// Definition of the cylinder beam chamber
G4Tubs* tubApprox = new G4Tubs("ApproxTub",6*cm,6.1*cm,18*cm,0.0*deg,360.0*deg);
G4LogicalVolume* tubLogical = new G4LogicalVolume(tubApprox, poly,"tubLogical");
G4VPhysicalVolume* tubPhysical = new G4PVPlacement(0,
                                                        G4ThreeVector((24.0259286)*cm, (24.0259286)*cm, 61.944725*cm),
                                                        tubLogical,
                                                      "tubPhysical",
                                                      logicEnv,
                                                      false,
                                                       0,
                                                       checkOverlaps);

   // Definiition of the detector the positron will be incident on in coincident events.
   G4VSolid* fixedDetector = new G4Box("fixedDetector", 6.*cm, 3.5*cm, 3.5*cm);
   G4LogicalVolume* fixedDetectorLogical = new G4LogicalVolume(fixedDetector, poly,"fixedLog");
   G4VPhysicalVolume* fixedPhysical = new G4PVPlacement(0,
                                                        G4ThreeVector((24.0259286-6-8)*cm, 24.0259286*cm, 61.944725*cm),
                                                        fixedDetectorLogical,
                                                      "fixedPhysical",
                                                      logicEnv,
                                                      false,
                                                       0,
                                                       checkOverlaps);
// assign the volumes so that the deposited energy is tracked.
fScoringVolume2 = fixedDetectorLogical;
fScoringVolume = variableDetectorLogical;



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

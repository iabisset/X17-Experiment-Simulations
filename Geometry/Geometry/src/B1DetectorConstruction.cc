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
// of

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


  // declare materials
  G4Material* poly = nist->FindOrBuildMaterial("G4_POLYSTYRENE");
  G4Material* carb = nist->FindOrBuildMaterial("G4_C");
  G4Material* Al = nist->FindOrBuildMaterial("G4_Al");
  
   // vacuum material definition needed intially
  G4int nel;
  G4double A, Z;
  G4Element* elN  = new G4Element("Nitrogen","N",  Z=7.,  A= 14.00674*g/mole);
  G4Element* elO  = new G4Element("Oxygen",  "O",  Z=8.,  A= 15.9994*g/mole);
  G4double density2 = 1.e-25*g/cm3;
  G4Material* Vacuum = new G4Material("Vacuum", density2, nel=2);
  Vacuum-> AddElement(elN, .7);
  Vacuum-> AddElement(elO, .3);

  // parse the geometry files
  G4GDMLParser fParser;
  fParser.Read("bar1.gdml");
  fParser.Read("bar2.gdml");
  fParser.Read("bar3.gdml");
  fParser.Read("bar4.gdml");
  fParser.Read("bar5.gdml");
  fParser.Read("bar6.gdml");
  fParser.Read("bar7.gdml");
  fParser.Read("bar8.gdml");
  fParser.Read("bar9.gdml");
  fParser.Read("bar10.gdml");
  fParser.Read("bar11.gdml");
  fParser.Read("bar12.gdml");
  fParser.Read("bar13.gdml");
  fParser.Read("bar14.gdml");
  fParser.Read("bar15.gdml");
  fParser.Read("bar16.gdml");
  fParser.Read("chamber.gdml");
  fParser.Read("restReduced.gdml");
  fParser.Read("carbon.gdml");



  // Envelope parameters
  //
  G4double env_sizeXY = 200*cm, env_sizeZ = 200*cm;
  G4Material* env_mat = nist->FindOrBuildMaterial("G4_AIR");

  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //
  // World volume definition
  //

  G4double world_sizeXY = 1.2*env_sizeXY;
  G4double world_sizeZ  = 1.2*env_sizeZ;
  G4Box* solidWorld =
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size


  G4LogicalVolume* logicWorld =
    new G4LogicalVolume(solidWorld,          //its solid
                        env_mat,           //its material
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
                      env_mat,             //its material
                      "Envelope");         //its name

new G4PVPlacement(0,                       //no rotation
                  G4ThreeVector(),         //at (0,0,0)
                  logicEnv,                //its logical volume
                  "Envelope",              //its name
                  logicWorld,              //its mother  volume
                  false,                   //no boolean operation
                  0,                       //copy number
                  checkOverlaps);          //overlaps checking


// Declare logical volumes 

G4LogicalVolume* bar1 = fParser.GetVolume("bar1");
G4LogicalVolume* bar2 = fParser.GetVolume("bar2");
G4LogicalVolume* bar3 = fParser.GetVolume("bar3");
G4LogicalVolume* bar4 = fParser.GetVolume("bar4");
G4LogicalVolume* bar5 = fParser.GetVolume("bar5");
G4LogicalVolume* bar6 = fParser.GetVolume("bar6");
G4LogicalVolume* bar7 = fParser.GetVolume("bar7");
G4LogicalVolume* bar8 = fParser.GetVolume("bar8");
G4LogicalVolume* bar9 = fParser.GetVolume("bar9");
G4LogicalVolume* bar10 = fParser.GetVolume("bar10");
G4LogicalVolume* bar11 = fParser.GetVolume("bar11");
G4LogicalVolume* bar12 = fParser.GetVolume("bar12");
G4LogicalVolume* bar13 = fParser.GetVolume("bar13");
G4LogicalVolume* bar14 = fParser.GetVolume("bar14");
G4LogicalVolume* bar15 = fParser.GetVolume("bar15");
G4LogicalVolume* bar16 = fParser.GetVolume("bar16");

G4LogicalVolume* carbon = fParser.GetVolume("carbon");

G4LogicalVolume* chamber = fParser.GetVolume("chamber");
G4LogicalVolume* rest = fParser.GetVolume("restReduced");

// Set materials

bar1->SetMaterial(poly);
bar2->SetMaterial(poly);
bar3->SetMaterial(poly);
bar4->SetMaterial(poly);
bar5->SetMaterial(poly);
bar6->SetMaterial(poly);
bar7->SetMaterial(poly);
bar8->SetMaterial(poly);
bar9->SetMaterial(poly);
bar10->SetMaterial(poly);
bar11->SetMaterial(poly);
bar12->SetMaterial(poly);
bar13->SetMaterial(poly);
bar14->SetMaterial(poly);
bar15->SetMaterial(poly);
bar16->SetMaterial(poly);

chamber->SetMaterial(Al);
carbon->SetMaterial(carb);
rest->SetMaterial(Al);




// The bars are based on identical files, and must be rotated individually.

G4RotationMatrix* rotat = new G4RotationMatrix();
G4RotationMatrix* rotat2 = new G4RotationMatrix();
G4RotationMatrix* rotat3 = new G4RotationMatrix();
G4RotationMatrix* rotat4 = new G4RotationMatrix();
G4RotationMatrix* rotat5 = new G4RotationMatrix();
G4RotationMatrix* rotat6 = new G4RotationMatrix();
G4RotationMatrix* rotat7 = new G4RotationMatrix();
G4RotationMatrix* rotat8 = new G4RotationMatrix();
G4RotationMatrix* rotat9 = new G4RotationMatrix();
G4RotationMatrix* rotat10 = new G4RotationMatrix();
G4RotationMatrix* rotat11 = new G4RotationMatrix();
G4RotationMatrix* rotat12 = new G4RotationMatrix();
G4RotationMatrix* rotat13 = new G4RotationMatrix();
G4RotationMatrix* rotat14 = new G4RotationMatrix();
G4RotationMatrix* rotat15 = new G4RotationMatrix();
rotat->rotateZ(22.5*deg);
rotat2->rotateZ(2*22.5*deg);
rotat3->rotateZ(3*22.5*deg);
rotat4->rotateZ(4*22.5*deg);
rotat5->rotateZ(5*22.5*deg);
rotat6->rotateZ(6*22.5*deg);
rotat7->rotateZ(7*22.5*deg);
rotat8->rotateZ(8*22.5*deg);
rotat9->rotateZ(9*22.5*deg);
rotat10->rotateZ(10*22.5*deg);
rotat11->rotateZ(11*22.5*deg);
rotat12->rotateZ(12*22.5*deg);
rotat13->rotateZ(13*22.5*deg);
rotat14->rotateZ(14*22.5*deg);
rotat15->rotateZ(15*22.5*deg);

// The volumes are placed in the environment volume

new G4PVPlacement(0, G4ThreeVector(0, 0, 0), bar1, "bar1", logicEnv, false, 0, checkOverlaps);
new G4PVPlacement(rotat, G4ThreeVector(0, 0, 0), bar2, "bar2", logicEnv, false, 0, checkOverlaps);
new G4PVPlacement(rotat2, G4ThreeVector(0, 0, 0), bar3, "bar3", logicEnv, false, 0, checkOverlaps);
new G4PVPlacement(rotat3, G4ThreeVector(0, 0, 0), bar4, "bar4", logicEnv, false, 0, checkOverlaps);
new G4PVPlacement(rotat4, G4ThreeVector(0, 0, 0), bar5, "bar5", logicEnv, false, 0, checkOverlaps);
new G4PVPlacement(rotat5, G4ThreeVector(0, 0, 0), bar6, "bar6", logicEnv, false, 0, checkOverlaps);
new G4PVPlacement(rotat6, G4ThreeVector(0, 0, 0), bar7, "bar7", logicEnv, false, 0, checkOverlaps);
new G4PVPlacement(rotat7, G4ThreeVector(0, 0, 0), bar8, "bar8", logicEnv, false, 0, checkOverlaps);
new G4PVPlacement(rotat8, G4ThreeVector(0, 0, 0), bar9, "bar9", logicEnv, false, 0, checkOverlaps);
new G4PVPlacement(rotat9, G4ThreeVector(0, 0, 0), bar10, "bar10", logicEnv, false, 0, checkOverlaps);
new G4PVPlacement(rotat10, G4ThreeVector(0, 0, 0), bar11, "bar11", logicEnv, false, 0, checkOverlaps);
new G4PVPlacement(rotat11, G4ThreeVector(0, 0, 0), bar12, "bar12", logicEnv, false, 0, checkOverlaps);
new G4PVPlacement(rotat12, G4ThreeVector(0, 0, 0), bar13, "bar13", logicEnv, false, 0, checkOverlaps);
new G4PVPlacement(rotat13, G4ThreeVector(0, 0, 0), bar14, "bar14", logicEnv, false, 0, checkOverlaps);
new G4PVPlacement(rotat14, G4ThreeVector(0, 0, 0), bar15, "bar15", logicEnv, false, 0, checkOverlaps);
new G4PVPlacement(rotat15, G4ThreeVector(0, 0, 0), bar16, "bar16", logicEnv, false, 0, checkOverlaps);


new G4PVPlacement(0, G4ThreeVector((-24.0259286)*cm, (-24.0259286)*cm, -61.944725*cm), carbon, "carbonreduced", logicEnv, false, 0, checkOverlaps);
new G4PVPlacement(0, G4ThreeVector((-24.0259286)*cm, (-24.0259286)*cm, -61.944725*cm), rest, "restreduced", logicEnv, false, 0, checkOverlaps);
new G4PVPlacement(0, G4ThreeVector((-24.0259286)*cm, (-24.0259286)*cm, -61.944725*cm), chamber, "chamberreduced", logicEnv, false, 0, checkOverlaps);




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

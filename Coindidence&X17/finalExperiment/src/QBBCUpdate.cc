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
//---------------------------------------------------------------------------
//
// ClassName:QBBC
//
// Author: 11 April 2006 V. Ivanchenko
//
// Modified:
// 24.11.06 V.Ivanchenko: Add G4HadronHElasticPhysics and G4NeutronTrackingCut
// 16.05.07 V.Ivanchenko: rename EM builders
// 20.04.11 V.Ivanchenko: remove extra headers of elastic builders
//                        added FTFP/Binary ion physics
// 16.10.12 A.Ribon: renamed the used physics classes
//
//----------------------------------------------------------------------------
//



// This is a modified version of the standard QBBC physics list which I have
// modified to use Livermore E&M physics

#include "QBBCUpdate.hh"
#include "globals.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleDefinition.hh"


#include "G4EmStandardPhysics.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4EmExtraPhysics.hh"
#include "G4StoppingPhysics.hh"
#include "G4EmLivermorePhysics.hh"

#include "G4Radioactivation.hh"

#include "G4NuclideTable.hh"
#include "G4LossTableManager.hh"
#include "G4UAtomicDeexcitation.hh"
#include "G4NuclearLevelData.hh"
#include "G4DeexPrecoParameters.hh"
#include "G4NuclideTable.hh"
#include "G4DecayPhysics.hh"


#include "G4HadronInelasticQBBC.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4HadronElasticPhysicsXS.hh"
#include "G4HadronElasticPhysicsHP.hh"
#include "G4ChargeExchangePhysics.hh"
#include "G4IonPhysicsXS.hh"
#include "G4IonElasticPhysics.hh"
#include "G4NeutronTrackingCut.hh"
#include "G4PhysicsListHelper.hh"
#include "G4IonConstructor.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4DecayTable.hh"
#include "G4GeneralPhaseSpaceDecay.hh"
#include "G4RadioactiveDecay.hh"
#include <cmath>
using namespace std;

QBBCUpdate::QBBCUpdate()
{

  G4int ver = 1;

  const G4double minute = 60*second;
  const G4double hour   = 60*minute;
  const G4double day    = 24*hour;
  const G4double year   = 365*day;
  new G4UnitDefinition("minute", "min", "Time", minute);
  new G4UnitDefinition("hour",   "h",   "Time", hour);
  new G4UnitDefinition("day",    "d",   "Time", day);
  new G4UnitDefinition("year",   "y",   "Time", year);

  G4NuclideTable::GetInstance()->SetThresholdOfHalfLife(0.1*picosecond);
  G4NuclideTable::GetInstance()->SetLevelTolerance(1.0*eV);

 //  G4ParticleTable* particleTable2 = G4ParticleTable::GetParticleTable();
 //
 //
 //  G4DecayTable* x17decay = new G4DecayTable();
 //  G4GeneralPhaseSpaceDecay* x17channel = new G4GeneralPhaseSpaceDecay(
 //                                                    "x17", // parent name
 //                                                    16.7*MeV,
 //                                                    1., // branching ratio
 //                                                    2, // number of daughters
 //                                                    "e-", // daughter 1
 //                                                    "e+" // daughter 2
 //                                                  );
 //
 //  G4String newName = "x17";
 //
 //  G4ParticleDefinition* x17 = new G4ParticleDefinition(
 //                                                    newName,   // name
 //                                                    16.7*MeV,   // mass
 //                                                    0.0*MeV,   // width
 //                                                    0.0,       // charge
 //                                                     2,        // 2*spin
 //                                                    +1,        // parity
 //                                                    -1,        // C-conjugation
 //                                                     0,        // 2*Isospin
 //                                                     0,        // 2*Isospin3
 //                                                     0,        // G-Parity
 //                                                     "boson",  // type
 //                                                     0,        // Lepton Number
 //                                                     0,        // baryon number
 //                                                     22,       // PDG encoding
 //                                                     false,     // stable
 //                                                     pow(10, -14)*s,      // lifetime
 //                                                     x17decay,     // decay table
 //                                                     true,    // shortlived?
 //                                                     "boson", // subtype
 //                                                     22);      // anti_encoding
 //
 // G4ParticleDefinition* particle
 //   = particleTable2->FindParticle("e-");
 //   G4ParticleDefinition* particle2
 //     = particleTable2->FindParticle("e+");
 // x17channel->SetDaughter(0, particle);
 // x17channel->SetDaughter(1, particle2);
 // x17channel->SetParent(x17);
 // x17channel->SetParentMass(16.7*MeV);
 // x17decay->Insert(x17channel);
 // x17->SetDecayTable(x17decay);


  defaultCutValue = 0.7*mm;
  SetVerboseLevel(1);

  // EM Physics
  RegisterPhysics( new G4EmLivermorePhysics(ver) );

  // Synchroton Radiation & GN Physics
  RegisterPhysics( new G4EmExtraPhysics(ver) );

   // Hadron Physics
  RegisterPhysics( new G4HadronElasticPhysicsXS(ver) );

  RegisterPhysics( new G4StoppingPhysics(ver) );

  RegisterPhysics( new G4IonPhysicsXS(ver) );

  RegisterPhysics( new G4IonElasticPhysics(ver) );

  RegisterPhysics( new G4HadronInelasticQBBC(ver));

  // Neutron tracking cut
  RegisterPhysics( new G4NeutronTrackingCut(ver) );

  RegisterPhysics( new G4RadioactiveDecayPhysics(ver));


  // G4RadioactiveDecay* decayPhysics = new G4RadioactiveDecay();

  //G4GenericIon::GenericIon();
  //G4PhysicsListHelper::GetPhysicsListHelper()->RegisterProcess(decayPhysics, G4GenericIon::GenericIon());
  //G4PhysicsListHelper::GetPhysicsListHelper()->RegisterProcess(decayPhysics, x17);


}


QBBCUpdate::~QBBCUpdate()
{}

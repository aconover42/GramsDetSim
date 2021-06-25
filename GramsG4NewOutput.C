#include <TFile.h>
#include <TBranch.h>
#include <TTree.h>

#include <vector>
#include <list>

#include <GramsG4WriteNtuplesAction.cc>
#include <GramsG4WriteNtuplesAction.hh>

#include <GramsG4LArHit.cc>
#include <GramsG4LArHit.hh>

#include <GramsG4LArSensitiveDetector.cc>
#include <GramsG4LArSensitiveDetector.hh>


typedef std::vector<double_t> vector_t;
typedef std::vector<vector_t> nested_t;


void MakeNtuple ()

{


  TFile* inputFile = new TFile("gramsg4.root");
  if ( inputFile == 0 )
   {
     std::cout << "Error: file gramsg4.root not found" << std::endl;
     return;
   }

  // Open the tree within the input file: 

  TTree* newOutputTree; 
  inputFile->GetObject("newOutputTree", newOutputTree);
  if ( newOutputTree == 0 )
    {
      std::cout << "Error: TTree newOutputTree not found" << std::endl;
      return;
    }

  // Make branch GG4LevelBranch: 
  TBranch* GG4LevelBranch;

  // Define a dummy object to hold contents of file
  // Here, the object is a gramsg4 pointer (I just paralleled the ExampleEvent pointer from the example)
  // Is that what it's supposed to be? *****************************************************************************************

  gramsg4* GG4Level = 0;

  // Connect GG4Level with a branch:
  newOutputTree->SetBranchAddress("GG4LevelBranch" , &GG4Level , &GG4LevelBranch);

  // Define how we will write the ntuple: 
  TFile* outputFile = new TFile("newNtuple.root","recreate"); 
  // From ROOT documentation: "RECREATE: create a new file, if the file already exists it will be overwritten"
  TTree* ntuple = new TTree("newOutputNtuple", "Selected variables from the gramsg4 objects"); //("name","title")

  // Allocate the variables we'll write:
 
  Int_t run;
  Int_t event;
  Double_t pri_E;
  Double_t pri_xPos;
  Double_t pri_yPos;
  Double_t pri_zPos;
  Double_t pri_t;
  Double_t pri_px;
  Double_t pri_py;
  Double_t pri_pz;

  Int_t compt_p;
  vector_t compt_E; // see TKDEAdapter.h line 62 
  vector_t compt_xPos;
  vector_t compt_yPos;
  vector_t compt_zPos;
  vector_t compt_t;
  nested_t compt_Eion;
  nested_t compt_Ephot;
  vector_t compt_TrackID;
  vector_t compt_ParentID;

  Int_t abs_p;
  vector_t abs_E;
  vector_t abs_xPos;
  vector_t abs_yPos;
  vector_t abs_zPos;
  vector_t abs_t;
  nested_t abs_Eion;
  nested_t abs_Ephot;
  vector_t abs_TrackID;
  vector_t abs_ParentID;

  Int_t pair_p;
  vector_t pair_E;
  vector_t pair_xPos;
  vector_t pair_yPos;
  vector_t pair_zPos;
  vector_t pair_t;
  nested_t pair_Eion;
  nested_t pair_Ephot;
  vector_t pair_TrackID;
  vector_t pair_ParentID;

  Int_t brem_p;
  vector_t brem_E;
  vector_t brem_xPos;
  vector_t brem_yPos;
  vector_t brem_zPos;
  vector_t brem_t;
  nested_t brem_Eion;
  nested_t brem_Ephot;
  vector_t brem_TrackID;
  vector_t brem_ParentID;


  // I am calling them "pri___" instead of "gamma___" in case we have other particles entering the detector

  // Create variables for array size: ****************************where do these go? they will be based on info from run*************************** 

  //*******************************for the sake of simlicity while building I am assigning them all size 'filler' = 10***************************** 
  int filler = 10;

  int s_compt_E = filler;
  int s_compt_xPos = filler;
  int s_compt_yPos = filler;
  int s_compt_zPos = filler;
  int s_compt_t = filler;
  int s_compt_Eion1 = filler; //the nested vectors need 2 dimensions
  int s_compt_Eion2 = filler;
  int s_compt_Ephot1 = filler;
  int s_compt_Ephot2 = filler;
  int s_compt_TrackID = filler;
  int s_compt_ParentID = filler;

  int s_abs_E = filler;
  int s_abs_xPos = filler;
  int s_abs_yPos = filler;
  int s_abs_zPos = filler;
  int s_abs_t = filler;
  int s_abs_Eion1 = filler;
  int s_abs_Eion2 = filler;
  int s_abs_Ephot1 = filler;
  int s_abs_Ephot2 = filler;
  int s_abs_TrackID = filler;
  int s_abs_ParentID = filler;

  int s_pair_E = filler;
  int s_pair_xPos = filler;
  int s_pair_yPos = filler;
  int s_pair_zPos = filler;
  int s_pair_t = filler;
  int s_pair_Eion1 = filler;
  int s_pair_Eion2 = filler;
  int s_pair_Ephot1 = filler;
  int s_pair_Ephot2 = filler;
  int s_pair_TrackID = filler;
  int s_pair_ParentID = filler;


  //Assign each variable its own branch:

  ntuple->Branch("event", &event , "event/I"); //("name", address, "leaflist")
  ntuple->Branch("pri_E", &pri_E , "pri_E/D");
  ntuple->Branch("pri_xPos", &pri_xPos , "pri_xPos/D");
  ntuple->Branch("pri_yPos" , &pri_yPos , "pri_yPos/D");
  ntuple->Branch("pri_zPos" , &pri_zPos , "pri_zPos/D");
  ntuple->Branch("pri_t" , &pri_t , "pri_t/D");
  ntuple->Branch("pri_px" , &pri_px , "pri_px/D");
  ntuple->Branch("pri_py" , &pri_py , "pri_py/D");
  ntuple->Branch("pri_pz" , &pri_pz , "pri_pz/D");

  ntuple->Branch("compt_p" , &compt_p , "compt_p/I");
  ntuple->Branch("compt_E" , &compt_E , "compt_E[s_compt_E]/D");
  ntuple->Branch("compt_xPos" , &compt_xPos , "compt_xPos[s_compt_xPos]/D");
  ntuple->Branch("compt_yPos" , &compt_yPos , "compt_yPos[s_compt_yPos]/D");
  ntuple->Branch("compt_zPos" , &compt_zPos , "compt_zPos[s_compt_zPos]/D");
  ntuple->Branch("compt_Eion" , &compt_Eion , "compt_Eion[s_compt_Eion1][s_compt_Eion2]/D");
  ntuple->Branch("compt_Ephot" , &compt_Ephot , "compt_Ephot[s_compt_Ephot1][s_compt_Ephot2]/D");
  ntuple->Branch("compt_TrackID" , &compt_TrackID , "compt_TrackID[s_compt_TrackID]/D");
  ntuple->Branch("compt_ParentID" , &compt_ParentID , "compt_ParentID[s_compt_ParentID]/D");

  ntuple->Branch("abs_p" , &abs_p , "abs_p/I");
  ntuple->Branch("abs_E" , &abs_E , "abs_E[s_abs_E]/D");
  ntuple->Branch("abs_xPos" , &abs_xPos , "abs_xPos[s_abs_xPos]/D");
  ntuple->Branch("abs_yPos" , &abs_yPos , "abs_yPos[s_abs_yPos]/D");
  ntuple->Branch("abs_zPos" , &abs_zPos , "abs_zPos[s_abs_zPos]/D");
  ntuple->Branch("abs_Eion" , &abs_Eion , "compt_Eion[s_abs_Eion1][s_abs_Eion2]/D");
  ntuple->Branch("abs_Ephot" , &abs_Ephot , "abs_Ephot[s_abs_Ephot1][s_abs_Ephot2]/D");
  ntuple->Branch("abs_TrackID" , &abs_TrackID , "abs_TrackID[s_abs_TrackID]/D");
  ntuple->Branch("abs_ParentID" , &abs_ParentID , "abs_ParentID[s_abs_ParentID]/D");

  ntuple->Branch("pair_p" , &pair_p , "pair_p/I");
  ntuple->Branch("pair_E" , &pair_E , "pair_E[s_pair_E]/D");
  ntuple->Branch("pair_xPos" , &pair_xPos , "pair_xPos[s_pair_xPos]/D");
  ntuple->Branch("pair_yPos" , &pair_yPos , "pair_yPos[s_pair_yPos]/D");
  ntuple->Branch("pair_zPos" , &pair_zPos , "pair_zPos[s_pair_zPos]/D");
  ntuple->Branch("pair_Eion" , &pair_Eion , "pair_Eion[s_pair_Eion1][s_pair_Eion2]/D");
  ntuple->Branch("pair_Ephot" , &pair_Ephot , "pair_Ephot[s_pair_Ephot1][s_pair_Ephot2]/D");
  ntuple->Branch("pair_TrackID" , &pair_TrackID , "pair_TrackID[s_pair_TrackID]/D");
  ntuple->Branch("pair_ParentID" , &pair_ParentID , "pair_ParentID[s_pair_ParentID]/D");

  ntuple->Branch("brem_p" , &brem_p , "brem_p/I");
  ntuple->Branch("brem_E" , &brem_E , "brem_E[s_brem_E]/D");
  ntuple->Branch("brem_xPos" , &brem_xPos , "brem_xPos[s_brem_xPos]/D");
  ntuple->Branch("brem_yPos" , &brem_yPos , "brem_yPos[s_brem_yPos]/D");
  ntuple->Branch("brem_zPos" , &brem_zPos , "brem_zPos[s_brem_zPos]/D");
  ntuple->Branch("brem_Eion" , &brem_Eion , "brem_Eion[s_brem_Eion1][s_brem_Eion2]/D");
  ntuple->Branch("brem_Ephot" , &brem_Ephot , "abs_Ephot[s_brem_Ephot1][s_brem_Ephot2]/D");
  ntuple->Branch("brem_TrackID" , &brem_TrackID , "brem_TrackID[s_brem_TrackID]/D");
  ntuple->Branch("brem_ParentID" , &brem_ParentID , "brem_ParentID[s_brem_ParentID]/D");


  //how to specify type for vector? see TTree::Branch(name, address , leaflist , bufsize) in ROOT doc ************************************

  //For each entry of the tree: 

  Int_t numberOfEntries = newOutputTree->GetEntriesFast(); 

  //From TTree.h line 460: virtual Long64_t GetEntriesFast() const { return fEntries; }
  //From RtypesCore.h line 80:  typedef long long  Long64_t; //Portable signed long integer 8 bytes 
  //From TTree.h line 84: Long64_t  fEntries; ///<number of entries

  for ( Int_t entry = 0; entry != numberOfEntries; ++entry ) // bool != "not equal to", ++ pre-increment "add 1 to entry"
    {
      // Get the GG4Level object from the file: 
      newOutputTree->GetEntry(entry);
      // Now GG4Level points to a gramsg4 object (if done right?) *************************************************************************
      // run = GG4Level->GetRun(); //only necessary if we include "run" column? 

      event = gramsg4->GetEvent();
      //is it gramsg4->GetEvent()? from browsing ROOT doc -- what is a "friend"? ***********************************************************

      // Set initial values:
      run = 0 ; // probably need something relating to this outside of this fct but that is low priority  
      pri_E = 0.;
      pri_xPos = 0.;
      pri_yPos = 0.;
      pri_zPos = 0.;
      pri_t = 0.;
      pri_px = 0.;
      pri_py = 0.;
      pri_pz = 0.;



      //Clear vectors: 
      compt_p.clear();
      compt_E.clear();
      compt_xPos.clear();
      compt_yPos.clear();
      compt_zPos.clear();
      compt_t.clear();
      compt_Eion.clear();
      compt_Ephot.clear();
      //compt_TrackID; // see GramsG4LArHit.cc etc. to figure this one out
      //compt_ParentID;

      abs_p.clear();
      abs_E.clear();
      abs_xPos.clear();
      abs_yPos.clear();
      abs_t.clear();
      abs_Eion.clear();
      abs_Ephot.clear();
      // abs_TrackID;
      // abs_ParentID;

      pair_p.clear();
      pair_E.clear();
      pair_xPos.clear();
      pair_yPos.clear();
      pair_zPos.clear();
      pair_t.clear();
      pair_Eion.clear();
      pair_Ephot.clear();
      // pair_TrackID;
      // pair_ParentID;

      brem_p.clear();
      brem_E.clear();
      brem_xPos.clear();
      brem_yPos.clear();
      brem_zPos.clear();
      brem_t.clear();
      brem_Eion.clear();
      brem_Ephot.clear();
      // brem_TrackID;
      // brem_ParentID;


      // Compute values: 

      pri_E = TMath::Sqrt( pri_px * pri_px + pri_py * pri_py + pri_pz * pri_pz );

      // in the example LeptonPx etc. are used -- are there keywords here that can do the same thing, like PrimaryPx ? *************************

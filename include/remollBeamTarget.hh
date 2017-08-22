#ifndef __REMOLLBEAMTARGET_HH
#define __REMOLLBEAMTARGET_HH

#include "remolltypes.hh"
#include "remollglobs.hh"
#include "remollVertex.hh"
#include "G4ThreeVector.hh"
#include <vector>

/*!
     Class that contains information on 
     the beam and target.  It needs to be
     aware of and consistant with what is
     in the geometry.

     This is responsible for:
         Rastering, arbitrary beam angle
	 Sampling along the target
	 Pre-vertex multiple scattering
	 External radiative effects
	 Luminosity calculations
 
     This is implemented in the singleton model

*/

class G4GenericMessenger;
class G4VPhysicalVolume;
class G4Material;
class remollMultScatt;

class remollBeamTarget {

    private:
        // Static geometry objects
	static G4String fActiveTargetVolume;
        static std::vector <G4VPhysicalVolume*> fTargetVolumes;
        static G4VPhysicalVolume* fTargetMother;

        // Effective lengths are weighted by density (i.e. in 1/cm^2)
        static G4double fTotalTargetEffectiveLength;
        static G4double fActiveTargetEffectiveLength;
        // Positions are in physical distances (i.e. in cm)
        static G4double fMotherTargetAbsolutePosition;
        static G4double fActiveTargetRelativePosition;

        static void UpdateInfo();

    public:
        // Static geometry functions
        static void ResetTargetVolumes(){ fTargetVolumes.clear(); fTargetMother = 0; UpdateInfo(); }
        static void SetMotherVolume( G4VPhysicalVolume *v ){ fTargetMother = v; UpdateInfo(); }
        static void AddTargetVolume( G4VPhysicalVolume *v ){ fTargetVolumes.push_back(v); UpdateInfo(); }
        static std::vector<G4VPhysicalVolume*> GetTargetVolumes(){ return fTargetVolumes; }

        void SetActiveTargetVolume(G4String name);
        void SetTargetPos(G4double z);
        void SetTargetLen(G4double l);

    public:
        remollBeamTarget();
	virtual ~remollBeamTarget();

	G4double GetEffLumin();


	remollVertex SampleVertex(SampType_t);

	G4double fBeamE;
	G4double fBeamCurr;
	G4double fBeamPol;

	remollMultScatt *fMS;

    private:
	G4GenericMessenger* fMessenger;

	G4Material *fDefaultMat;
	
    public:
	// Base position, angle *sampled* info
	G4ThreeVector fVer, fDir;
	G4double fSampE, fRadLen;
	G4double fTravLen;
	G4double fEcut, fEffMatLen;

	// Base position/angle sampling info
        G4bool fOldRaster;
	G4double fRasterX, fRasterY;
	G4double fX0, fY0;
	G4double fTh0, fPh0;
	G4double fdTh, fdPh, fCorrTh, fCorrPh;

};


#endif//__REMOLLBEAMTARGET_HH


/**
  \file HayamiRSFunc.h
  \brief header of HayamiRSFunction

  \author Jean-Christophe FABRE <fabrejc@supagro.inra.fr>
*/


#ifndef __HAYAMIRSFUNC_H__
#define __HAYAMIRSFUNC_H__


#include "openfluid-core.h"
#include "openfluid-base.h"
#include "HayamiTools.h"

// =====================================================================
// =====================================================================

/**

*/
class HayamiRSFunction : public openfluid::base::PluggableFunction
{

  private:

    int m_MaxSteps;

    float m_MeanCelerity;

    float m_MeanSigma;

    float m_MeanSlope;

    float m_MeanManning;

    float m_RSBuffer;

    /**
      Calibration step for height-discharge relation (meters)
    */
    float m_CalibrationStep;

    IDKernelMap m_RSKernel;

    bool m_UseUpSUOutput;

    openfluid::core::IDSerieOfScalarValuePtrMap m_Input;

    openfluid::core::IDFloatMap m_CurrentInputSum;

    openfluid::core::IDSerieOfScalarValuePtrMap m_HeightDischarge;

    bool computeWaterHeightFromDischarge(int ID, float Discharge, float *Height);

    /**
         for groundwater flow use
        */
     float m_CoeffInfiltration;
     float m_CoeffDrainage;
     float m_CoeffGW;


     openfluid::core::IDFloatMap m_ThetaIni;
     openfluid::core::IDFloatMap m_ThetaSat;


  public:

    /**
      Constructor
    */
    HayamiRSFunction();

    /**
      Destructor
    */
    ~HayamiRSFunction();

    bool initParams(openfluid::core::FuncParamsMap_t Params);

    bool prepareData();

    bool checkConsistency();

    bool initializeRun(const openfluid::base::SimulationInfo* SimInfo);

    bool runStep(const openfluid::base::SimulationStatus* SimStatus);

    bool finalizeRun(const openfluid::base::SimulationInfo* SimInfo);

};

// =====================================================================
// =====================================================================


DECLARE_PLUGIN_HOOKS




#endif  // __HAYAMIRSFUNC_H__



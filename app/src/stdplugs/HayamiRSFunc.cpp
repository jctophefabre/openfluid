/**
  \file HayamiRSFunc.h
  \brief header of HayamiRSFunction

  \author Jean-Christophe FABRE <fabrejc@ensam.inra.fr>
*/


#include "HayamiRSFunc.h"
#include <math.h>

#include <iostream>

// =====================================================================
// =====================================================================

mhydasdk::base::PluggableFunction* GetMHYDASPluggableFunction()
{
  return new HayamiRSFunction();
}

// =====================================================================
// =====================================================================


HayamiRSFunction::HayamiRSFunction()
                : PluggableFunction()
{

  mp_Signature->Author = wxT("Jean-Christophe FABRE");
  mp_Signature->AuthorEmail = wxT("fabrejc@ensam.inra.fr");
  mp_Signature->ID = wxT("hayamirs");
  mp_Signature->FunctionType = mhydasdk::base::SIMULATION;
  mp_Signature->Name = wxT("Hayami hydrological transfer on reach segments");
  mp_Signature->Description = wxT("");
  mp_Signature->Domain = wxT("Transfer");

  DECLARE_RS_PRODUCED_VAR("qoutput",wxT("Output volume at the outlet of the ditch"),wxT("m3/s"));
  DECLARE_RS_PRODUCED_VAR("waterheight",wxT("Water height at the outlet of the ditch"),wxT("m"));
  DECLARE_RS_REQUIRED_PROPERTY("nmanning",wxT("-"),wxT("-"));

  DECLARE_FUNCTION_PARAM("maxsteps",wxT("maximum hayami kernel steps"),wxT("-"));
  DECLARE_FUNCTION_PARAM("meancel",wxT("-"),wxT("-"));  
  DECLARE_FUNCTION_PARAM("meansigma",wxT("-"),wxT("-"));  

  // default values
  m_MaxSteps = 100;    
  m_MeanCelerity = 0.49;    
  m_MeanSigma = 500;
  m_MeanSlope = 0;    
  m_MeanManning = 0;        
  m_CalibrationStep = 0.01;
}


// =====================================================================
// =====================================================================


HayamiRSFunction::~HayamiRSFunction()
{

}


// =====================================================================
// =====================================================================


bool HayamiRSFunction::initParams(mhydasdk::core::ParamsMap Params)
{
  //if (Params.find(wxT("maxsteps")) != Params.end()) m_MaxSteps = (int)(Params[wxT("maxsteps")]);
  MHYDAS_GetFunctionParam(Params,wxT("maxsteps"),&m_MaxSteps);  
  //if (Params.find(wxT("meancel")) != Params.end()) m_MeanCelerity = Params[wxT("meancel")];      
  MHYDAS_GetFunctionParam(Params,wxT("meancel"),&m_MeanCelerity);
  // if (Params.find(wxT("meansigma")) != Params.end()) m_MeanSigma = Params[wxT("meansigma")];
  MHYDAS_GetFunctionParam(Params,wxT("meansigma"),&m_MeanSigma);
  MHYDAS_GetFunctionParam(Params,wxT("calibstep"),&m_CalibrationStep);
  return true;
}

// =====================================================================
// =====================================================================


bool HayamiRSFunction::prepareData()
{
  // On verifie s'il existe des SU pour recuperer leur debit
   
  m_UseUpSUOutput = false;   
  if (mp_CoreData->getSpatialData()->getSUsCollection()->size() > 0)
  {
    DECLARE_SU_USED_VAR("qoutput");    
    m_UseUpSUOutput = true;
  } 

  return true;
}

// =====================================================================
// =====================================================================


bool HayamiRSFunction::checkConsistency()
{

  return true;
}


// =====================================================================
// =====================================================================


bool HayamiRSFunction::initializeRun(mhydasdk::base::SimulationInfo* SimInfo)
{
  mhydasdk::core::ReachSegment* RS;
  float Cel, Sigma;
  int ID;
  float TmpValue;
  DECLARE_RS_ORDERED_LOOP;
 
 
  BEGIN_RS_ORDERED_LOOP(RS)
    ID = RS->getID();  
    
    m_Input[ID] = new mhydasdk::core::VectorOfDouble();
    m_HeightDischarge[ID] = new mhydasdk::core::VectorOfDouble();
    m_CurrentInputSum[ID] = 0;
           
    m_MeanSlope = m_MeanSlope + RS->getUsrSlope();
    MHYDAS_GetDistributedProperty(RS,wxT("nmanning"),&TmpValue);
    m_MeanManning = m_MeanManning + TmpValue;
    //m_MeanManning = m_MeanManning + RS->getProperties()->find(wxT("nmanning"))->second;    
  END_LOOP

  m_MeanSlope = m_MeanSlope / mp_CoreData->getSpatialData()->getRSsCollection()->size();
  m_MeanManning = m_MeanManning / mp_CoreData->getSpatialData()->getRSsCollection()->size(); 

  BEGIN_RS_ORDERED_LOOP(RS)
    MHYDAS_GetDistributedProperty(RS,wxT("nmanning"),&TmpValue);
//    Cel = m_MeanCelerity * (m_MeanManning / RS->getProperties()->find(wxT("nmanning"))->second) * (sqrt((RS->getUsrSlope() / m_MeanSlope)));
//    Sigma = m_MeanSigma * (RS->getProperties()->find(wxT("nmanning"))->second / m_MeanManning) * (m_MeanSlope / RS->getUsrSlope());      
    Cel = m_MeanCelerity * (m_MeanManning / TmpValue) * (sqrt((RS->getUsrSlope() / m_MeanSlope)));
    Sigma = m_MeanSigma * (TmpValue / m_MeanManning) * (m_MeanSlope / RS->getUsrSlope());      
    m_RSKernel[RS->getID()] = ComputeHayamiKernel(Cel, Sigma,RS->getUsrLength(),m_MaxSteps,SimInfo->getTimeStep());        
  END_LOOP

  
  // calcul de la relation hauteur débit
  
  float HydrauRadius, Speed, Q, Section, CurrentHeight;
  int i, StepsNbr;
  
  BEGIN_RS_ORDERED_LOOP(RS)

    MHYDAS_GetDistributedProperty(RS,wxT("nmanning"),&TmpValue);    
    
    StepsNbr = int(ceil(RS->getUsrHeight() / m_CalibrationStep));
    for (i=0;i<StepsNbr;i++)
    {
      CurrentHeight = i * m_CalibrationStep;
      
      Section = RS->getUsrWidth() * CurrentHeight;
      HydrauRadius = Section / (2 *CurrentHeight + RS->getUsrWidth());
      Speed = (1/TmpValue) * pow(HydrauRadius,2/3) * sqrt(RS->getUsrSlope());   
      Q = Speed * Section;
    
      m_HeightDischarge[RS->getID()]->push_back(Q);    
    }
        
    
  END_LOOP
  
  
  return true;
}



// =====================================================================
// =====================================================================


bool HayamiRSFunction::runStep(mhydasdk::base::SimulationStatus* SimStatus)
{
  int ID;
  int CurrentStep;
  int TimeStep;
  int i;
  float UpSrcSUsOutputsSum;  
  float UpLatSUsOutputsSum;  
  float UpRSsOutputsSum;  
  float QOutput;
  float QInput;
  float TmpValue;

  
  mhydasdk::core::ReachSegment* RS;
  mhydasdk::core::ReachSegment* UpRS;
  mhydasdk::core::SurfaceUnit* UpSU;

  list<mhydasdk::core::SurfaceUnit*>::iterator UpSUiter;
  list<mhydasdk::core::SurfaceUnit*>* UpSUsList;
  list<mhydasdk::core::ReachSegment*>::iterator UpRSiter;
  list<mhydasdk::core::ReachSegment*>* UpRSsList;  
  

  TimeStep = SimStatus->getTimeStep();
  CurrentStep = SimStatus->getCurrentStep();
  
  DECLARE_RS_ORDERED_LOOP;
  BEGIN_RS_ORDERED_LOOP(RS)

    ID = RS->getID();

    QOutput = 0;
    
    // 1.a calcul du debit provenant des SU sources qui se jettent dans les noeuds sources    
    
    UpSrcSUsOutputsSum = 0;
    if (m_UseUpSUOutput)
    {      
      UpSUsList = RS->getSrcUpstreamSUs();
      
      for(UpSUiter=UpSUsList->begin(); UpSUiter != UpSUsList->end(); UpSUiter++)
      {                
        UpSU = *UpSUiter;
        MHYDAS_GetDistributedVarValue(UpSU,wxT("qoutput"),CurrentStep,&TmpValue);
        UpSrcSUsOutputsSum = UpSrcSUsOutputsSum + TmpValue; // / UpSU->getUsrArea();
      }  
    }
  

    // 1.b calcul du debit provenant des SU laterales

    UpLatSUsOutputsSum = 0;
    if (m_UseUpSUOutput)
    {      
      UpSUsList = RS->getLatUpstreamSUs();
      
      for(UpSUiter=UpSUsList->begin(); UpSUiter != UpSUsList->end(); UpSUiter++)
      {                
        UpSU = *UpSUiter;
        
        MHYDAS_GetDistributedVarValue(UpSU,wxT("qoutput"),CurrentStep,&TmpValue);        
        UpLatSUsOutputsSum = UpLatSUsOutputsSum + TmpValue;// / UpSU->getUsrArea();                
        
      }  
    }


    // 2.a calcul des debits provenant des RS amont
    
    UpRSsOutputsSum = 0;

    UpRSsList = RS->getUpstreamReaches();
      
    for(UpRSiter=UpRSsList->begin(); UpRSiter != UpRSsList->end(); UpRSiter++) \
    {                
      UpRS = *UpRSiter;
      MHYDAS_GetDistributedVarValue(UpRS,wxT("qoutput"),CurrentStep,&TmpValue);
      UpRSsOutputsSum = UpRSsOutputsSum + TmpValue;                
    }    
    

//    std::cerr << UpSrcSUsOutputsSum << " / " << UpLatSUsOutputsSum << " / " << UpRSsOutputsSum << std::endl;
    
    // 2.b propagation via Hayami
        
       
    QInput = UpRSsOutputsSum + UpSrcSUsOutputsSum + UpLatSUsOutputsSum; 
    m_CurrentInputSum[ID] = m_CurrentInputSum[ID] + QInput;
    m_Input[ID]->push_back(QInput);
    
    QOutput = 0;
    if (m_CurrentInputSum[ID] > 0)
    {    
      QOutput = DoHayamiPropagation(m_RSKernel[ID], CurrentStep, m_Input[ID], m_MaxSteps, TimeStep);
    }  

    QOutput = QOutput + UpLatSUsOutputsSum;

        
    MHYDAS_AppendDistributedVarValue(RS,wxT("qoutput"),QOutput);

    //if (!computeWaterHeightFromDischarge(ID,QOutput,&TmpValue)) std::cerr << "ça dépasse ID: " << ID <<std::endl; 
    if (!computeWaterHeightFromDischarge(ID,QOutput,&TmpValue)) 
      mp_ExecMsgs->addWarning(wxT("hayamirs"),SimStatus->getCurrentStep(),wxT("overflow on RS") + wxString::Format(wxT("%d"),ID));
    
    MHYDAS_AppendDistributedVarValue(RS,wxT("waterheight"),TmpValue);

  END_LOOP

  return true;
}


// =====================================================================
// =====================================================================


bool HayamiRSFunction::finalizeRun(mhydasdk::base::SimulationInfo* SimInfo)
{

  return true;
}

// =====================================================================
// =====================================================================

bool HayamiRSFunction::computeWaterHeightFromDischarge(int ID, float Discharge, float *Height)
{
  
  if (Discharge < 0) return false;
  if (Discharge == 0) Height = 0;
  else
  {
   
    int i;
    float Q1, Q2, H1, H2;
    
    mhydasdk::core::VectorOfDouble* HeightDischarge = m_HeightDischarge[ID]; 

   
    // on determine par boucle le premier débit de la relation H/D supérieur au débit recherché
    i = 1;  
   
    while (HeightDischarge->at(i) < Discharge)
    {
      i++;
      if (i == HeightDischarge->size()) return false;
            
    }

              
    Q1 = HeightDischarge->at(i-1);
    Q2 = HeightDischarge->at(i);

    H1 = (i-1) * m_CalibrationStep;
    H2 = i * m_CalibrationStep; 


    // risque de division par 0 si Q1 == Q2 !! à revoir, comment fait-on?
    *Height = H1 + ((Discharge-Q1) * (H2-H1) / (Q2-Q1));
    
      
  }
  
  return true;
  
}

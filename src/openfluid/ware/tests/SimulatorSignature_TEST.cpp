/*

  This file is part of OpenFLUID software
  Copyright(c) 2007, INRA - Montpellier SupAgro


 == GNU General Public License Usage ==

  OpenFLUID is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  OpenFLUID is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with OpenFLUID. If not, see <http://www.gnu.org/licenses/>.


 == Other Usage ==

  Other Usage means a use of OpenFLUID that is inconsistent with the GPL
  license, and requires a written agreement between You and INRA.
  Licensees for Other Usage of OpenFLUID may use this file in accordance
  with the terms contained in the written agreement between You and INRA.
  
*/



/**
  \file SimulatorSignature_TEST.cpp
  \brief Implements ...

  \author Jean-Christophe FABRE <fabrejc@supagro.inra.fr>
 */

#define BOOST_TEST_MAIN
#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE unittest_simsignature
#include <boost/test/unit_test.hpp>
#include <boost/test/auto_unit_test.hpp>

#include <openfluid/ware/SimulatorSignature.hpp>


// =====================================================================
// =====================================================================


BOOST_AUTO_TEST_CASE(check_construction)
{
  openfluid::ware::SimulatorSignature Signature;
  openfluid::ware::SignatureHandledData SignatureData;
  openfluid::ware::SignatureHandledDataItem SignatureDataItem;

  BOOST_REQUIRE_EQUAL(Signature.TimeScheduling.Type,openfluid::ware::SignatureTimeScheduling::UNDEFINED);
  BOOST_REQUIRE_EQUAL(Signature.TimeScheduling.Min,0);
  BOOST_REQUIRE_EQUAL(Signature.TimeScheduling.Max,0);
}

// =====================================================================
// =====================================================================

BOOST_AUTO_TEST_CASE(check_operations)
{
  openfluid::ware::SimulatorSignature* Signature;

  Signature = new openfluid::ware::SimulatorSignature();

  DECLARE_NAME("name of the test");
  DECLARE_AUTHOR("John Doe","john.doe@foo.bar.org");
  DECLARE_DESCRIPTION("this is the description");
  DECLARE_METHOD("method");
  DECLARE_DOMAIN("domain");
  DECLARE_VERSION("4.7");
  DECLARE_STATUS(openfluid::ware::BETA);

  DECLARE_SIMULATOR_PARAM("param1","this is param1","m/s");
  DECLARE_SIMULATOR_PARAM("param2","this is param2","m3");

  DECLARE_REQUIRED_ATTRIBUTE("attr1","UnitClassA","this is attr1","goals/period");
  DECLARE_REQUIRED_ATTRIBUTE("attr2","UnitClassB","this is attr2","");

  DECLARE_USED_ATTRIBUTE("attr3","UnitClassA","this is attr3","?");

  DECLARE_PRODUCED_VAR("pvar1","UnitClassA","this is pvar1","");
  DECLARE_PRODUCED_VAR("pvar2","UnitClassA","this is pvar2","m");
  DECLARE_PRODUCED_VAR("pvar1","UnitClassB","this is pvar1","?");

  DECLARE_UPDATED_VAR("pvar1","UnitClassA","this is pvar1 updated","");

  DECLARE_REQUIRED_VAR("pvar1","UnitClassA","this is rvar1","");
  DECLARE_REQUIRED_VAR("pvar2","UnitClassA","this is rvar2","m");
  DECLARE_REQUIRED_VAR("pvar1","UnitClassB","this is rvar3","?");

  DECLARE_USED_VAR("uvar1","UnitClassA","this is uvar1","s");
  DECLARE_USED_VAR("uvar2","UnitClassA","this is uvar2","s-1");

  DECLARE_USED_EVENTS("UnitClassA");
  DECLARE_USED_EVENTS("UnitClassB");

  DECLARE_REQUIRED_EXTRAFILE("reqfile.dat");
  DECLARE_USED_EXTRAFILE("usedfile.dat");

  DECLARE_SCHEDULING_RANGE(10,30);

  // ----------------------------------------------------------

  BOOST_REQUIRE_EQUAL(Signature->Name,"name of the test");
  BOOST_REQUIRE_EQUAL(Signature->Authors.front().first,"John Doe");
  BOOST_REQUIRE_EQUAL(Signature->Authors.front().second,"john.doe@foo.bar.org");
  BOOST_REQUIRE_EQUAL(Signature->Domain,"domain");
  BOOST_REQUIRE_EQUAL(Signature->Method,"method");
  BOOST_REQUIRE_EQUAL(Signature->Description,"this is the description");
  BOOST_REQUIRE_EQUAL(Signature->Version,"4.7");
  BOOST_REQUIRE_EQUAL(Signature->Status,openfluid::ware::BETA);


  BOOST_REQUIRE_EQUAL(Signature->TimeScheduling.Type,openfluid::ware::SignatureTimeScheduling::RANGE);
  BOOST_REQUIRE_EQUAL(Signature->TimeScheduling.Min,10);
  BOOST_REQUIRE_EQUAL(Signature->TimeScheduling.Max,30);

  BOOST_REQUIRE_EQUAL(Signature->HandledData.SimulatorParams[1].DataName,"param2");
  BOOST_REQUIRE_EQUAL(Signature->HandledData.SimulatorParams[1].Description,"this is param2");
  BOOST_REQUIRE_EQUAL(Signature->HandledData.SimulatorParams[1].DataUnit,"m3");

  BOOST_REQUIRE_EQUAL(Signature->HandledData.RequiredAttribute.size(),2);

  BOOST_REQUIRE_EQUAL(Signature->HandledData.UsedAttribute.size(),1);

  BOOST_REQUIRE_EQUAL(Signature->HandledData.ProducedVars.size(),3);
  BOOST_REQUIRE_EQUAL(Signature->HandledData.ProducedVars[1].DataName,"pvar2");
  BOOST_REQUIRE_EQUAL(Signature->HandledData.ProducedVars[1].UnitClass,"UnitClassA");
  BOOST_REQUIRE_EQUAL(Signature->HandledData.ProducedVars[2].UnitClass,"UnitClassB");

  BOOST_REQUIRE_EQUAL(Signature->HandledData.RequiredVars.size(),3);
  BOOST_REQUIRE_EQUAL(Signature->HandledData.RequiredVars[1].DataName,"pvar2");
  BOOST_REQUIRE_EQUAL(Signature->HandledData.RequiredVars[1].UnitClass,"UnitClassA");
  BOOST_REQUIRE_EQUAL(Signature->HandledData.RequiredVars[2].UnitClass,"UnitClassB");

  BOOST_REQUIRE_EQUAL(Signature->HandledData.UpdatedVars.size(),1);

  BOOST_REQUIRE_EQUAL(Signature->HandledData.UsedVars.size(),2);

  BOOST_REQUIRE_EQUAL(Signature->HandledData.UsedEventsOnUnits.size(),2);

  BOOST_REQUIRE_EQUAL(Signature->HandledData.RequiredExtraFiles.size(),1);

  BOOST_REQUIRE_EQUAL(Signature->HandledData.UsedExtraFiles.size(),1);


  // ----------------------------------------------------------

  DECLARE_SCHEDULING_DEFAULT;
  BOOST_REQUIRE_EQUAL(Signature->TimeScheduling.Type,openfluid::ware::SignatureTimeScheduling::DEFAULT);
  BOOST_REQUIRE_EQUAL(Signature->TimeScheduling.Min,0);
  BOOST_REQUIRE_EQUAL(Signature->TimeScheduling.Max,0);


  DECLARE_SCHEDULING_FIXED(51);
  BOOST_REQUIRE_EQUAL(Signature->TimeScheduling.Type,openfluid::ware::SignatureTimeScheduling::FIXED);
  BOOST_REQUIRE_EQUAL(Signature->TimeScheduling.Min,51);
  BOOST_REQUIRE_EQUAL(Signature->TimeScheduling.Max,51);

  DECLARE_SCHEDULING_UNDEFINED;
  BOOST_REQUIRE_EQUAL(Signature->TimeScheduling.Type,openfluid::ware::SignatureTimeScheduling::UNDEFINED);
  BOOST_REQUIRE_EQUAL(Signature->TimeScheduling.Min,0);
  BOOST_REQUIRE_EQUAL(Signature->TimeScheduling.Max,0);

}

// =====================================================================
// =====================================================================


BOOST_AUTO_TEST_CASE(check_GetVariableNameAndType)
{
  std::string ParamName;
  openfluid::core::Value::Type ParamType;

  BOOST_CHECK_EQUAL(openfluid::ware::SignatureHandledTypedDataItem::getVariableNameAndType("noneparam",ParamName,ParamType),true);
  BOOST_CHECK_EQUAL(ParamName,"noneparam");
  BOOST_CHECK_EQUAL(ParamType,openfluid::core::Value::NONE);

  BOOST_CHECK_EQUAL(openfluid::ware::SignatureHandledTypedDataItem::getVariableNameAndType("none.param",ParamName,ParamType),true);
  BOOST_CHECK_EQUAL(ParamName,"none.param");
  BOOST_CHECK_EQUAL(ParamType,openfluid::core::Value::NONE);

  BOOST_CHECK_EQUAL(openfluid::ware::SignatureHandledTypedDataItem::getVariableNameAndType("none_param",ParamName,ParamType),true);
  BOOST_CHECK_EQUAL(ParamName,"none_param");
  BOOST_CHECK_EQUAL(ParamType,openfluid::core::Value::NONE);

  BOOST_CHECK_EQUAL(openfluid::ware::SignatureHandledTypedDataItem::getVariableNameAndType("none-param",ParamName,ParamType),true);
  BOOST_CHECK_EQUAL(ParamName,"none-param");
  BOOST_CHECK_EQUAL(ParamType,openfluid::core::Value::NONE);

  BOOST_CHECK_EQUAL(openfluid::ware::SignatureHandledTypedDataItem::getVariableNameAndType("oldvectparam[]",ParamName,ParamType),true);
  BOOST_CHECK_EQUAL(ParamName,"oldvectparam");
  BOOST_CHECK_EQUAL(ParamType,openfluid::core::Value::VECTOR);

  BOOST_CHECK_EQUAL(openfluid::ware::SignatureHandledTypedDataItem::getVariableNameAndType("oldvect.param[]",ParamName,ParamType),true);
  BOOST_CHECK_EQUAL(ParamName,"oldvect.param");
  BOOST_CHECK_EQUAL(ParamType,openfluid::core::Value::VECTOR);

  BOOST_CHECK_EQUAL(openfluid::ware::SignatureHandledTypedDataItem::getVariableNameAndType("oldvect_param[]",ParamName,ParamType),true);
  BOOST_CHECK_EQUAL(ParamName,"oldvect_param");
  BOOST_CHECK_EQUAL(ParamType,openfluid::core::Value::VECTOR);

  BOOST_CHECK_EQUAL(openfluid::ware::SignatureHandledTypedDataItem::getVariableNameAndType("oldvect-param[]",ParamName,ParamType),true);
  BOOST_CHECK_EQUAL(ParamName,"oldvect-param");
  BOOST_CHECK_EQUAL(ParamType,openfluid::core::Value::VECTOR);

  BOOST_CHECK_EQUAL(openfluid::ware::SignatureHandledTypedDataItem::getVariableNameAndType("vectparam[vector]",ParamName,ParamType),true);
  BOOST_CHECK_EQUAL(ParamName,"vectparam");
  BOOST_CHECK_EQUAL(ParamType,openfluid::core::Value::VECTOR);

  BOOST_CHECK_EQUAL(openfluid::ware::SignatureHandledTypedDataItem::getVariableNameAndType("vect.param[vector]",ParamName,ParamType),true);
  BOOST_CHECK_EQUAL(ParamName,"vect.param");
  BOOST_CHECK_EQUAL(ParamType,openfluid::core::Value::VECTOR);

  BOOST_CHECK_EQUAL(openfluid::ware::SignatureHandledTypedDataItem::getVariableNameAndType("vect_param[vector]",ParamName,ParamType),true);
  BOOST_CHECK_EQUAL(ParamName,"vect_param");
  BOOST_CHECK_EQUAL(ParamType,openfluid::core::Value::VECTOR);

  BOOST_CHECK_EQUAL(openfluid::ware::SignatureHandledTypedDataItem::getVariableNameAndType("vect-param[vector]",ParamName,ParamType),true);
  BOOST_CHECK_EQUAL(ParamName,"vect-param");
  BOOST_CHECK_EQUAL(ParamType,openfluid::core::Value::VECTOR);

  BOOST_CHECK_EQUAL(openfluid::ware::SignatureHandledTypedDataItem::getVariableNameAndType("doubleparam[double]",ParamName,ParamType),true);
  BOOST_CHECK_EQUAL(ParamName,"doubleparam");
  BOOST_CHECK_EQUAL(ParamType,openfluid::core::Value::DOUBLE);

  BOOST_CHECK_EQUAL(openfluid::ware::SignatureHandledTypedDataItem::getVariableNameAndType("intparam[integer]",ParamName,ParamType),true);
  BOOST_CHECK_EQUAL(ParamName,"intparam");
  BOOST_CHECK_EQUAL(ParamType,openfluid::core::Value::INTEGER);

  BOOST_CHECK_EQUAL(openfluid::ware::SignatureHandledTypedDataItem::getVariableNameAndType("boolparam[boolean]",ParamName,ParamType),true);
  BOOST_CHECK_EQUAL(ParamName,"boolparam");
  BOOST_CHECK_EQUAL(ParamType,openfluid::core::Value::BOOLEAN);

  BOOST_CHECK_EQUAL(openfluid::ware::SignatureHandledTypedDataItem::getVariableNameAndType("matrixparam[matrix]",ParamName,ParamType),true);
  BOOST_CHECK_EQUAL(ParamName,"matrixparam");
  BOOST_CHECK_EQUAL(ParamType,openfluid::core::Value::MATRIX);

  BOOST_CHECK_EQUAL(openfluid::ware::SignatureHandledTypedDataItem::getVariableNameAndType("mapparam[map]",ParamName,ParamType),true);
  BOOST_CHECK_EQUAL(ParamName,"mapparam");
  BOOST_CHECK_EQUAL(ParamType,openfluid::core::Value::MAP);

  BOOST_CHECK_EQUAL(openfluid::ware::SignatureHandledTypedDataItem::getVariableNameAndType("stringparam[string]",ParamName,ParamType),true);
  BOOST_CHECK_EQUAL(ParamName,"stringparam");
  BOOST_CHECK_EQUAL(ParamType,openfluid::core::Value::STRING);

  BOOST_CHECK_EQUAL(openfluid::ware::SignatureHandledTypedDataItem::getVariableNameAndType("badparam[STRING]",ParamName,ParamType),false);

  BOOST_CHECK_EQUAL(openfluid::ware::SignatureHandledTypedDataItem::getVariableNameAndType("badparam[badtype]",ParamName,ParamType),false);

  BOOST_CHECK_EQUAL(openfluid::ware::SignatureHandledTypedDataItem::getVariableNameAndType("badparam[",ParamName,ParamType),false);

  BOOST_CHECK_EQUAL(openfluid::ware::SignatureHandledTypedDataItem::getVariableNameAndType("badparam]",ParamName,ParamType),false);

  BOOST_CHECK_EQUAL(openfluid::ware::SignatureHandledTypedDataItem::getVariableNameAndType("badparam[[]",ParamName,ParamType),false);

  BOOST_CHECK_EQUAL(openfluid::ware::SignatureHandledTypedDataItem::getVariableNameAndType("badparam[string",ParamName,ParamType),false);
}


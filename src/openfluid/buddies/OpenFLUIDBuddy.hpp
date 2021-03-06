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
  @file OpenFLUIDBuddy.hpp

  @author Jean-Christophe FABRE <jean-christophe.fabre@inra.fr>
 */


#ifndef __OPENFLUID_BUDDIES_OPENFLUIDBUDDY_HPP__
#define __OPENFLUID_BUDDIES_OPENFLUIDBUDDY_HPP__


#include <string>
#include <map>

#include <openfluid/dllexport.hpp>
#include <openfluid/buddies/BuddiesListener.hpp>


namespace openfluid { namespace buddies {


class OPENFLUID_API OpenFLUIDBuddy
{
  protected:

    std::map<std::string,std::string> m_Options;

    std::map<std::string,std::string> m_RequiredOptionsHelp;
    std::map<std::string,std::string> m_OtherOptionsHelp;

    void setOptionIfNotSet(const std::string& OptionName, const std::string& OptionValue);

    std::string getYesNoFromOneZero(const std::string& VStr);

    openfluid::buddies::BuddiesListener* mp_Listener;


  public:

    OpenFLUIDBuddy(openfluid::buddies::BuddiesListener* Listener);

    virtual ~OpenFLUIDBuddy();

    bool parseOptions(const std::string& OptsStr);

    void streamOptions(std::ostream& OStream);

    virtual bool run() = 0;

    void invokeHelp();
};


} } //namespaces

#endif /* __OPENFLUID_BUDDIES_OPENFLUIDBUDDY_HPP__ */

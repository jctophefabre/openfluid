/*
 This file is part of OpenFLUID software
 Copyright (c) 2007-2010 INRA-Montpellier SupAgro


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
 along with OpenFLUID.  If not, see <http://www.gnu.org/licenses/>.

 In addition, as a special exception, INRA gives You the additional right
 to dynamically link the code of OpenFLUID with code not covered
 under the GNU General Public License ("Non-GPL Code") and to distribute
 linked combinations including the two, subject to the limitations in this
 paragraph. Non-GPL Code permitted under this exception must only link to
 the code of OpenFLUID dynamically through the OpenFLUID libraries
 interfaces, and only for building OpenFLUID plugins. The files of
 Non-GPL Code may be link to the OpenFLUID libraries without causing the
 resulting work to be covered by the GNU General Public License. You must
 obey the GNU General Public License in all respects for all of the
 OpenFLUID code and other code used in conjunction with OpenFLUID
 except the Non-GPL Code covered by this exception. If you modify
 this OpenFLUID, you may extend this exception to your version of the file,
 but you are not obligated to do so. If you do not wish to provide this
 exception without modification, you must delete this exception statement
 from your version and license this OpenFLUID solely under the GPL without
 exception.


 == Other Usage ==

 Other Usage means a use of OpenFLUID that is inconsistent with the GPL
 license, and requires a written agreement between You and INRA.
 Licensees for Other Usage of OpenFLUID may use this file in accordance
 with the terms contained in the written agreement between You and INRA.
 */

/**
 \file EngineProject.hpp
 \brief Header of ...

 \author Aline LIBRES <libres@supagro.inra.fr>
 */

#ifndef __ENGINEPROJECT_HPP__
#define __ENGINEPROJECT_HPP__

#include <cstddef>
#include <cstdlib>
#include <sigc++/sigc++.h>

#include <glibmm/ustring.h>

#include <openfluid/core/DateTime.hpp>
#include <openfluid/machine/Engine.hpp>
#include <openfluid/fluidx/CoupledModelDescriptor.hpp>

namespace openfluid {
namespace base {
class RuntimeEnvironment;
}
namespace core {
class Datastore;
}
namespace base {
class IOListener;
}
namespace machine {
class MachineListener;
class MonitoringInstance;
}
namespace fluidx {
class RunDescriptor;
class FluidXDescriptor;
class AdvancedFluidXDescriptor;
}
}

class ProjectChecker;

class EngineProject
{
  private:

    bool m_WithProjectManager;

    openfluid::fluidx::AdvancedFluidXDescriptor* mp_AdvancedDesc;

    openfluid::base::IOListener* mp_IOListener;

    ProjectChecker* mp_Checker;

    sigc::signal<void> m_signal_RunStarted;

    sigc::signal<void> m_signal_RunStopped;

    sigc::signal<void> m_signal_SaveHappened;

    void setDefaultRunDesc();

    void checkAndSetDefaultRunValues();

    void deleteEngineObjects();

    void whenSimulationStarted();

    void whenSimulationStopped();

    void checkAndAdaptModel();

    void checkAndAdaptMonitoring();

    bool m_HasChangesAtStart;

  protected:

    openfluid::fluidx::FluidXDescriptor* mp_FXDesc;

    openfluid::core::DateTime m_DefaultBeginDT;

    int m_DefaultDeltaT;

  public:

    EngineProject(Glib::ustring FolderIn = "", bool WithProjectManager = false);

    sigc::signal<void> signal_RunStarted();
    sigc::signal<void> signal_RunStopped();

    sigc::signal<void> signal_SaveHappened();

    bool hasChangesAtStart();

    void run();

    void save();

    const ProjectChecker& check(bool& GlobalState);

    openfluid::fluidx::AdvancedFluidXDescriptor& getAdvancedDesc();

    ~EngineProject();
};

#endif /* __ENGINEPROJECT_HPP__ */

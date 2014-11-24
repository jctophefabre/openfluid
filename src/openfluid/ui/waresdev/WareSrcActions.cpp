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
 \file WareSrcActions.cpp
 \brief Implements ...

 \author Aline LIBRES <aline.libres@gmail.com>
 */

#include <openfluid/ui/waresdev/WareSrcActions.hpp>

#include <openfluid/base/ApplicationException.hpp>

namespace openfluid { namespace ui { namespace waresdev {

WareSrcActions* WareSrcActions::mp_Instance = 0;

// =====================================================================
// =====================================================================


WareSrcActions::WareSrcActions()
{
  m_Actions["NewSimulator"] = new QAction(tr("Simulator..."), this);
  m_Actions["NewObserver"] = new QAction(tr("Observer..."), this);
  m_Actions["NewExtension"] = new QAction(tr("Builder extension..."), this);

  m_Actions["OpenSimulator"] = new QAction(tr("Simulator..."), this);
  m_Actions["OpenObserver"] = new QAction(tr("Observer..."), this);
  m_Actions["OpenExtension"] = new QAction(tr("Builder extension..."), this);

  m_Actions["DeleteWare"] = new QAction(tr("Delete ware"), this);

  m_Actions["NewFile"] = new QAction(QIcon(":/ui/common/icons/file-new.png"),
                                     tr("New..."), this);
  m_Actions["OpenFile"] = new QAction(QIcon(":/ui/common/icons/file-open.png"),
                                      tr("Open..."), this);
  m_Actions["SaveFile"] = new QAction(QIcon(":/ui/common/icons/file-save.png"),
                                      tr("Save"), this);
  m_Actions["SaveAsFile"] = new QAction(
      QIcon(":/ui/common/icons/file-save-as.png"), tr("Save as..."), this);
  m_Actions["CloseFile"] = new QAction(
      QIcon(":/ui/common/icons/file-close.png"), tr("Close"), this);
  m_Actions["DeleteFile"] = new QAction(tr("Delete"), this);
}


// =====================================================================
// =====================================================================


WareSrcActions::~WareSrcActions()
{

}


// =====================================================================
// =====================================================================


WareSrcActions* WareSrcActions::getInstance()
{
  if (!mp_Instance)
    mp_Instance = new WareSrcActions();

  return mp_Instance;
}


// =====================================================================
// =====================================================================


QAction* WareSrcActions::getAction(const QString& ActionName)
{
  if (m_Actions.contains(ActionName))
    return m_Actions.value(ActionName);

  throw openfluid::base::ApplicationException(
      "openfluid-devstudio", "WareSrcActions::getAction",
      "Action \"" + ActionName.toStdString() + "\" does'nt exist.");
}


} } }  // namespaces
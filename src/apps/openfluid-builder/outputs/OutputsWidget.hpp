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
  @file OutputsWidget.hpp

  @author Jean-Christophe FABRE <jean-christophe.fabre@inra.fr>
*/


#ifndef __OPENFLUID_BUILDERAPP_OUTPUTSWIDGET_HPP__
#define __OPENFLUID_BUILDERAPP_OUTPUTSWIDGET_HPP__


#include <QFileSystemModel>

#include "WorkspaceWidget.hpp"


namespace Ui
{
  class OutputsWidget;
}


class OutputsWidget : public WorkspaceWidget
{
  Q_OBJECT;

  private:

    Ui::OutputsWidget* ui;

    QFileSystemModel* mp_FSModel;

    static bool removeDirectory(QDir Dir);


  private slots:

    void clearOutputDir();

    void tryToOpenFile(const QModelIndex& Index);

    void tryToExploreOutputDir();

    void openLogExplorer();


  public slots:

    void refreshOutputDir() const;


  public:

    OutputsWidget(QWidget* Parent, openfluid::fluidx::FluidXDescriptor& FXDesc);

    virtual ~OutputsWidget();

};


#endif /* __OPENFLUID_BUILDERAPP_OUTPUTSWIDGET_HPP__ */

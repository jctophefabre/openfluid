/***copyright>=========================================================

  OpenFLUID - Software environment for modelling Fluxes In Landscapes

  This file is a part of OpenFLUID software
  http://www.umr-lisah.fr/openfluid
  Copyright (c) INRA
  See the file "copyright" for the full license governing this code.

=========================================================<copyright***/


/**
  \file ModelInstance.h
  \brief Header of ...

  \author Jean-Christophe FABRE <fabrejc@supagro.inra.fr>
 */


#ifndef __MODELINSTANCE_H__
#define __MODELINSTANCE_H__


#include "openfluid-core.h"
#include "openfluid-base.h"
#include "ModelItemInstance.h"

class ModelInstance
{
  private:

    std::list<ModelItemInstance*> m_ModelItems;

  public:

    ModelInstance();

    ~ModelInstance();

    void appendItem(ModelItemInstance* ItemInstance);

    void clear();

    void deleteItemsAndClear();

    unsigned int getItemsCount() const { return m_ModelItems.size(); };

};

#endif /* __MODELINSTANCE_H__ */
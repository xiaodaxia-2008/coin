/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2008 by Kongsberg SIM.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Kongsberg SIM about acquiring
 *  a Coin Professional Edition License.
 *
 *  See http://www.coin3d.org/ for more information.
 *
 *  Kongsberg SIM, Postboks 1283, Pirsenteret, 7462 Trondheim, NORWAY.
 *  http://www.sim.no/  sales@sim.no  coin-support@coin3d.org
 *
\**************************************************************************/

#include <Inventor/scxml/ScXMLOnExit.h>

#include <assert.h>
#include <algorithm>
#include <vector>

#include <Inventor/scxml/ScXML.h>
#include <Inventor/scxml/ScXMLInvoke.h>

#include "scxml/ScXMLCommonP.h"

// *************************************************************************

/*!
  \class ScXMLOnExit ScXMLOnExit.h Inventor/scxml/ScXMLOnExit.h
  \brief Implementation of the &lt;onexit&gt; SCXML element.

  \since Coin 3.0
  \ingroup scxml
*/

class ScXMLOnExitP {
public:
  std::vector<ScXMLInvoke *> invokelist;

};

#define PRIVATE(obj) ((obj)->pimpl)

SCXML_OBJECT_SOURCE(ScXMLOnExit);

void
ScXMLOnExit::initClass(void)
{
  SCXML_OBJECT_INIT_CLASS(ScXMLOnExit, ScXMLObject, SCXML_DEFAULT_NS, "onexit");
}

ScXMLOnExit::ScXMLOnExit(void)
{
}

ScXMLOnExit::~ScXMLOnExit(void)
{
  {
    std::vector<ScXMLInvoke *>::iterator invokeit =
      PRIVATE(this)->invokelist.begin();
    while (invokeit != PRIVATE(this)->invokelist.end()) {
      delete *invokeit;
      ++invokeit;
    }
    PRIVATE(this)->invokelist.clear();
  }
}

// *************************************************************************
// executable content

SCXML_LIST_OBJECT_API_IMPL(ScXMLOnExit, ScXMLInvoke, PRIVATE(this)->invokelist, Invoke, Invokes);

void
ScXMLOnExit::invoke(ScXMLStateMachine * statemachine)
{
  std::vector<ScXMLInvoke *>::const_iterator it =
    PRIVATE(this)->invokelist.begin();
  while (it != PRIVATE(this)->invokelist.end()) {
    (*it)->invoke(statemachine);
    ++it;
  }
}

#undef PRIVATE

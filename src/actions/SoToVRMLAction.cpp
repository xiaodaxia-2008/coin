/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2001 by Systems in Motion.  All rights reserved.
 *  
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  version 2 as published by the Free Software Foundation.  See the
 *  file LICENSE.GPL at the root directory of this source distribution
 *  for more details.
 *
 *  If you desire to use Coin with software that is incompatible
 *  licensewise with the GPL, and / or you would like to take
 *  advantage of the additional benefits with regard to our support
 *  services, please contact Systems in Motion about acquiring a Coin
 *  Professional Edition License.  See <URL:http://www.coin3d.org> for
 *  more information.
 *
 *  Systems in Motion, Prof Brochs gate 6, 7030 Trondheim, NORWAY
 *  <URL:http://www.sim.no>, <mailto:support@sim.no>
 *
\**************************************************************************/

/*!
  \class SoToVRMLAction Inventor/include/SoToVRMLAction.h
  \brief The SoToVRMLAction class builds a new scene graph using only
  VRML 1.0 nodes.
*/

#include <Inventor/SbName.h>
#include <Inventor/actions/SoToVRMLAction.h>
#include <coindefs.h> // COIN_STUB()


SO_ACTION_SOURCE(SoToVRMLAction);

// Overridden from parent class.
void
SoToVRMLAction::initClass(void)
{
  SO_ACTION_INIT_CLASS(SoToVRMLAction, SoAction);
}


/*!
  A constructor.
*/

SoToVRMLAction::SoToVRMLAction(void)
{
  COIN_STUB();
}

/*!
  The destructor.
*/

SoToVRMLAction::~SoToVRMLAction(void)
{
  // FIXME: implement.
}

/*!
  This method is called before the traversal is begun.
*/

void
SoToVRMLAction::beginTraversal(SoNode * /* node */)
{
  COIN_STUB();
}

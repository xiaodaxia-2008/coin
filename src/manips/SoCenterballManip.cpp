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

#include <Inventor/manips/SoCenterballManip.h>
#include <Inventor/nodes/SoSubNodeP.h>
#include <Inventor/draggers/SoCenterballDragger.h>
#include <Inventor/nodes/SoSurroundScale.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <coindefs.h>

SO_NODE_SOURCE(SoCenterballManip);


// doc in super
void
SoCenterballManip::initClass(void)
{
  SO_NODE_INTERNAL_INIT_CLASS(SoCenterballManip);
}

SoCenterballManip::SoCenterballManip(void)
{
  SO_NODE_INTERNAL_CONSTRUCTOR(SoCenterballManip);

  SoCenterballDragger * dragger = new SoCenterballDragger;
  this->setDragger(dragger);

  SoSurroundScale * ss = (SoSurroundScale*) dragger->getPart("surroundScale", TRUE);
  ss->numNodesUpToContainer = 4;
  ss->numNodesUpToReset = 3;

  // we don't need to use specific callbacks for this manipulator.
  // it's ok to use the functionality provided by the superclass:
  // SoTransformManip.  we'll keep the callback to be API-compatible,
  // and to make it possible to add new code if we at some point find
  // find that it's still needed; without breaking the ABI.
}


SoCenterballManip::~SoCenterballManip()
{
}

void
SoCenterballManip::setDragger(SoDragger * newDragger)
{
  inherited::setDragger(newDragger);
}

void
SoCenterballManip::fieldSensorCB(void * f, SoSensor * s)
{
  // this function should never be called, but just-in-case
  // we call the superclass method.
  inherited::fieldSensorCB(f, s);
}

void
SoCenterballManip::valueChangedCB(void * f, SoDragger * d)
{
  // this function should never be called, but just-in-case
  // we call the superclass method.
  inherited::valueChangedCB(f, d);
}

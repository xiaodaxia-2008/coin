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
  \class SoAnnotation SoAnnotation.h Inventor/nodes/SoAnnotation.h
  \brief The SoAnnotation node draws all its children geometry on top of other geometry.
  \ingroup nodes

  FIXME: write class doc
*/

// FIXME: consider adding a lazy GL depth buffer element.

#include <Inventor/nodes/SoAnnotation.h>
#include <Inventor/nodes/SoSubNodeP.h>
#include <Inventor/elements/SoCacheElement.h>

#include <Inventor/actions/SoGLRenderAction.h>
#if HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H
#include <Inventor/system/gl.h>


SO_NODE_SOURCE(SoAnnotation);


/*!
  Constructor.
*/
SoAnnotation::SoAnnotation()
{
  SO_NODE_INTERNAL_CONSTRUCTOR(SoAnnotation);
}

/*!
  Destructor.
*/
SoAnnotation::~SoAnnotation()
{
}

// doc in super
void
SoAnnotation::initClass(void)
{
  SO_NODE_INTERNAL_INIT_CLASS(SoAnnotation);
}

/*!
  FIXME: write function documentation
*/
void
SoAnnotation::GLRender(SoGLRenderAction * action)
{
  switch (action->getCurPathCode()) {
  case SoAction::NO_PATH:
  case SoAction::BELOW_PATH:
    this->GLRenderBelowPath(action);
    break;
  case SoAction::OFF_PATH:
    // do nothing. Separator will reset state.
    break;
  case SoAction::IN_PATH:
    this->GLRenderInPath(action);
    break;
  }
}

/*!
  FIXME: write doc
*/
void
SoAnnotation::GLRenderBelowPath(SoGLRenderAction * action)
{
  if (action->isRenderingDelayedPaths()) {
    SbBool zbenabled = glIsEnabled(GL_DEPTH_TEST);
    if (zbenabled) glDisable(GL_DEPTH_TEST);
    inherited::GLRenderBelowPath(action);
    if (zbenabled) glEnable(GL_DEPTH_TEST);
  }
  else {
    SoCacheElement::invalidate(action->getState());
    action->addDelayedPath(action->getCurPath()->copy());
  }
}

/*!
  FIXME: write doc
*/
void
SoAnnotation::GLRenderInPath(SoGLRenderAction * action)
{
  if (action->isRenderingDelayedPaths()) {
    SbBool zbenabled = glIsEnabled(GL_DEPTH_TEST);
    if (zbenabled) glDisable(GL_DEPTH_TEST);
    inherited::GLRenderInPath(action);
    if (zbenabled) glEnable(GL_DEPTH_TEST);
  }
  else {
    SoCacheElement::invalidate(action->getState());
    action->addDelayedPath(action->getCurPath()->copy());
  }
}

/*!
  FIXME: write doc
*/
void
SoAnnotation::GLRenderOffPath(SoGLRenderAction *)
{
  // should never render, this is a separator node
}

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
  \class SoLevelOfDetail SoLevelOfDetail.h Inventor/nodes/SoLevelOfDetail.h
  \brief The SoLevelOfDetail class is used to choose a child based on projected size.
  \ingroup nodes

  FIXME: write class doc
*/


#include <Inventor/nodes/SoLevelOfDetail.h>
#include <Inventor/nodes/SoSubNodeP.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/elements/SoComplexityElement.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/misc/SoState.h>
#include <Inventor/misc/SoChildList.h>
#include <stdlib.h>

static SoGetBoundingBoxAction * bboxAction = NULL;

static void
SoLevelOfDetail_cleanup_func(void)
{
  delete bboxAction;
  bboxAction = NULL;
}

/*!
  \var SoMFFloat SoLevelOfDetail::screenArea
  The screen areas for each child.
*/

// *************************************************************************

SO_NODE_SOURCE(SoLevelOfDetail);

/*!
  Default constructor.
*/
SoLevelOfDetail::SoLevelOfDetail(void)
{
  this->commonConstructor();
}

/*!
  Specify the expected number of children this node will have, to make
  it possible to do more efficient resource allocation.
*/
SoLevelOfDetail::SoLevelOfDetail(int numchildren)
  : inherited(numchildren)
{
  this->commonConstructor();
}

// private
void
SoLevelOfDetail::commonConstructor(void)
{
  SO_NODE_INTERNAL_CONSTRUCTOR(SoLevelOfDetail);

  SO_NODE_ADD_FIELD(screenArea, (0));
}

/*!
  Destructor.
*/
SoLevelOfDetail::~SoLevelOfDetail()
{
}

// doc in parent
void
SoLevelOfDetail::initClass(void)
{
  SO_NODE_INTERNAL_INIT_CLASS(SoLevelOfDetail);
}

// doc in parent
void
SoLevelOfDetail::doAction(SoAction *action)
{
  switch (action->getCurPathCode()) {
  case SoAction::IN_PATH:
    inherited::doAction(action); // normal path traversal
    return;
  case SoAction::OFF_PATH:
    return; // this is a separator node, return.
  case SoAction::BELOW_PATH:
  case SoAction::NO_PATH:
    break; // go on
  default:
    assert(0 && "unknown path code");
    return;
  }

  // for some strange reason, gcc (egcs-2.91.66) won't accept the code
  // below inside a case (yes, I did use brackets).
  // That's the reason for the strange switch/case above. pederb 19991116

  SoState * state = action->getState();
  int n = this->getNumChildren();
  if (n == 0) return;
  float complexity = SoComplexityElement::get(state);

  // quick test to see if we should just traverse last child
  if ((SoComplexityTypeElement::get(state) ==
       SoComplexityTypeElement::BOUNDING_BOX) ||
      (complexity == 0.0f) ||
      (n == 1) ||
      (this->screenArea.getNum() == 0)) {
    state->push();
    this->getChildren()->traverse(action, n-1);
    state->pop();
    return;
  }
  if (!bboxAction) {
    SbViewportRegion dummy;
    bboxAction = new SoGetBoundingBoxAction(dummy);
    (void)atexit(SoLevelOfDetail_cleanup_func);
  }
  bboxAction->setViewportRegion(SoViewportRegionElement::get(state));
  bboxAction->apply(this); // find bbox of all children
  SbVec2s size;
  SbBox3f bbox = bboxAction->getBoundingBox();
  SoShape::getScreenSize(state, bbox, size);

  float area = float(size[0])*float(size[1])*complexity;

  // in case there are too few screenArea values
  n = SbMin(n, this->screenArea.getNum());

  for (int i = 0; i < n; i++) {
    if (area > this->screenArea[i]) {
      state->push();
      this->getChildren()->traverse(action, i);
      state->pop();
      return;
    }
  }
  // if we get here, the last child should be traversed
  state->push();
  this->getChildren()->traverse(action, this->getNumChildren()-1);
  state->pop();
}

// doc in parent
void
SoLevelOfDetail::callback(SoCallbackAction *action)
{
  SoLevelOfDetail::doAction((SoAction*)action);
}

// doc in parent
void
SoLevelOfDetail::GLRender(SoGLRenderAction *action)
{
  SoLevelOfDetail::doAction((SoAction*)action);
}

// doc in parent
void
SoLevelOfDetail::rayPick(SoRayPickAction *action)
{
  SoLevelOfDetail::doAction((SoAction*)action);
}

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
  \class SoComposeRotation SoCompose.h Inventor/engines/SoCompose.h
  \brief The SoComposeRotation class is used to compose rotations from angle and axis.
  \ingroup engines
*/

#include <Inventor/engines/SoComposeRotation.h>
#include <Inventor/lists/SoEngineOutputList.h>
#include <Inventor/fields/SoMFRotation.h>
#include <Inventor/engines/SoSubEngineP.h>

SO_ENGINE_SOURCE(SoComposeRotation);

/*!
  \var SoMFVec3f SoComposeRotation::axis
  Set of axis vectors for the output rotations.
*/
/*!
  \var SoMFFloat SoComposeRotation::angle
  Set of scalar rotation values for the output rotations.
*/
/*!
  \var SoEngineOutput SoComposeRotation::rotation

  (SoMFRotation) Rotations generated from the angle and axis input
  fields.
*/


#ifndef DOXYGEN_SKIP_THIS // No need to document these.

SoComposeRotation::SoComposeRotation()
{
  SO_ENGINE_INTERNAL_CONSTRUCTOR(SoComposeRotation);

  SO_ENGINE_ADD_INPUT(axis,(0.0f,0.0f,0.0f));
  SO_ENGINE_ADD_INPUT(angle,(0.0f));

  SO_ENGINE_ADD_OUTPUT(rotation,SoMFRotation);
}

// overloaded from parent
void
SoComposeRotation::initClass()
{
  SO_ENGINE_INTERNAL_INIT_CLASS(SoComposeRotation);
}

//
// private members
//
SoComposeRotation::~SoComposeRotation()
{
}

// overloaded from parent
void
SoComposeRotation::evaluate()
{
  int numAxis=axis.getNum();
  int numAngle=angle.getNum();

  int numOut=numAxis>numAngle?numAxis:numAngle;

  SO_ENGINE_OUTPUT(rotation,SoMFRotation,setNum(numOut));

  int i;

  float angleVal;
  for (i=0;i<numOut;i++) {
    const SbVec3f axisVal=i<numAxis?axis[i]:axis[numAxis-1];
    angleVal=i<numAngle?angle[i]:angle[numAngle-1];

    SO_ENGINE_OUTPUT(rotation,SoMFRotation,set1Value(i,axisVal,angleVal));
  }
}

#endif // !DOXYGEN_SKIP_THIS

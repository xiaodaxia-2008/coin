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
  \class SoDecomposeVec3f SoCompose.h Inventor/engines/SoCompose.h
  \brief The SoDecomposeVec3f class is used to decompose 3D vectors into three floats.
  \ingroup engines
*/

#include <Inventor/engines/SoDecomposeVec3f.h>
#include <Inventor/lists/SoEngineOutputList.h>
#include <Inventor/engines/SoSubEngineP.h>

SO_ENGINE_SOURCE(SoDecomposeVec3f);

/*!
  \var SoMFVec3f SoDecomposeVec3f::vector
  Set of input vectors to be decomposed into their coordinate
  elements.
*/
/*!
  \var SoEngineOutput SoDecomposeVec3f::x
  (SoMFFloat) First coordinates of the input vectors.
*/
/*!
  \var SoEngineOutput SoDecomposeVec3f::y
  (SoMFFloat) Second coordinates of the input vectors.
*/
/*!
  \var SoEngineOutput SoDecomposeVec3f::z
  (SoMFFloat) Third coordinates of the input vectors.
*/


#ifndef DOXYGEN_SKIP_THIS // No need to document these.

SoDecomposeVec3f::SoDecomposeVec3f()
{
  SO_ENGINE_INTERNAL_CONSTRUCTOR(SoDecomposeVec3f);

  SO_ENGINE_ADD_INPUT(vector,(0,0,0));

  SO_ENGINE_ADD_OUTPUT(x,SoMFFloat);
  SO_ENGINE_ADD_OUTPUT(y,SoMFFloat);
  SO_ENGINE_ADD_OUTPUT(z,SoMFFloat);
}

// overloaded from parent
void
SoDecomposeVec3f::initClass()
{
  SO_ENGINE_INTERNAL_INIT_CLASS(SoDecomposeVec3f);
}

//
// private members
//
SoDecomposeVec3f::~SoDecomposeVec3f()
{
}

// overloaded from parent
void
SoDecomposeVec3f::evaluate()
{
  int num = this->vector.getNum();

  SO_ENGINE_OUTPUT(x,SoMFFloat,setNum(num));
  SO_ENGINE_OUTPUT(y,SoMFFloat,setNum(num));
  SO_ENGINE_OUTPUT(z,SoMFFloat,setNum(num));

  int i;
  for (i = 0; i < num; i++) {
    SO_ENGINE_OUTPUT(x,SoMFFloat,set1Value(i,vector[i][0]));
    SO_ENGINE_OUTPUT(y,SoMFFloat,set1Value(i,vector[i][1]));
    SO_ENGINE_OUTPUT(z,SoMFFloat,set1Value(i,vector[i][2]));
  }
}

#endif // !DOXYGEN_SKIP_THIS

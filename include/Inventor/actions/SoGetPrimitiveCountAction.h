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

#ifndef COIN_SOGETPRIMITIVECOUNTACTION_H
#define COIN_SOGETPRIMITIVECOUNTACTION_H

#include <Inventor/actions/SoAction.h>
#include <Inventor/actions/SoSubAction.h>
#include <Inventor/elements/SoDecimationTypeElement.h>


class COIN_DLL_API SoGetPrimitiveCountAction : public SoAction {
  typedef SoAction inherited;

  SO_ACTION_HEADER(SoGetPrimitiveCountAction);

public:
  SoGetPrimitiveCountAction(void);
  virtual ~SoGetPrimitiveCountAction();

  static void initClass(void);

  int getTriangleCount(void) const;
  int getLineCount(void) const;
  int getPointCount(void) const;
  int getTextCount(void) const;
  int getImageCount(void) const;
  SbBool containsNoPrimitives(void);
  SbBool containsNonTriangleShapes(void);

  SbBool is3DTextCountedAsTriangles(void);
  void setCount3DTextAsTriangles(const SbBool flag);

  SbBool canApproximateCount(void);
  void setCanApproximate(const SbBool flag);

  void setDecimationValue(SoDecimationTypeElement::Type type,
                          float percentage = 1.0);
  SoDecimationTypeElement::Type getDecimationType(void);
  float getDecimationPercentage(void);

  void addNumTriangles(const int num);
  void addNumLines(const int num);
  void addNumPoints(const int num);
  void addNumText(const int num);
  void addNumImage(const int num);
  void incNumTriangles(void);
  void incNumLines(void);
  void incNumPoints(void);
  void incNumText(void);
  void incNumImage(void);

protected:
  virtual void beginTraversal(SoNode * node);

private:
  int numtris;
  int numlines;
  int numpoints;
  int numtexts;
  int numimages;

  SbBool textastris;
  SbBool approx;
  SbBool nonvertexastris;
  SoDecimationTypeElement::Type decimationtype;
  float decimationpercentage;
};

#endif // !COIN_SOGETPRIMITIVECOUNTACTION_H

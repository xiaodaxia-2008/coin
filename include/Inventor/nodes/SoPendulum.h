/**************************************************************************\
 *
 *  Copyright (C) 1998-2000 by Systems in Motion.  All rights reserved.
 *
 *  This file is part of the Coin library.
 *
 *  This file may be distributed under the terms of the Q Public License
 *  as defined by Troll Tech AS of Norway and appearing in the file
 *  LICENSE.QPL included in the packaging of this file.
 *
 *  If you want to use Coin in applications not covered by licenses
 *  compatible with the QPL, you can contact SIM to aquire a
 *  Professional Edition license for Coin.
 *
 *  Systems in Motion AS, Prof. Brochs gate 6, N-7030 Trondheim, NORWAY
 *  http://www.sim.no/ sales@sim.no Voice: +47 22114160 Fax: +47 67172912
 *
\**************************************************************************/

#ifndef COIN_SOPENDULUM_H
#define COIN_SOPENDULUM_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/nodes/SoRotation.h>
#include <Inventor/fields/SoSFRotation.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFBool.h>

class SoElapsedTime;
class SoCalculator;
class SoInterpolateRotation;

class SoPendulum : public SoRotation {
  typedef SoRotation inherited;

  SO_NODE_HEADER(SoPendulum);

public:
  static void initClass(void);
  SoPendulum(void);

  SoSFRotation rotation0;
  SoSFRotation rotation1;
  SoSFFloat speed;
  SoSFBool on;

protected:
  virtual ~SoPendulum();

private:
  SoInterpolateRotation *interpolator;
  SoCalculator *calculator;
  SoElapsedTime *timer;
};

#endif // !COIN_SOPENDULUM_H

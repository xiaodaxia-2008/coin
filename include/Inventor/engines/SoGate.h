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

#ifndef COIN_SOGATE_H
#define COIN_SOGATE_H

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoMField.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFTrigger.h>

class SoEngineOutput;


class COIN_DLL_API SoGate : public SoEngine {
  typedef SoEngine inherited;

  SO_ENGINE_HEADER(SoGate);

public:
  static void initClass(void);
  SoGate(SoType type);

  SoSFBool enable;
  SoSFTrigger trigger;
  SoMField * input;

  SoEngineOutput * output;

protected:
  virtual void inputChanged(SoField * which);

private:
  SoGate(void);
  ~SoGate();

  virtual void evaluate(void);

  virtual SbBool readInstance(SoInput * in, unsigned short flags);
  virtual void writeInstance(SoOutput * out);

  SbBool initialize(const SoType inputfieldtype);

  virtual void copyContents(const SoFieldContainer * from,
                            SbBool copyconnections);

  // SoGate instances uses a dynamic set of inputs and outputs, as
  // they are not common for all instances of the class (like for most
  // of the other engines).
  SoFieldData * dynamicinput;
  SoEngineOutputData * dynamicoutput;

  // Avoid a g++/egcs warning due to the private default constructor.
  friend class dummy;
};

#endif // !COIN_SOGATE_H

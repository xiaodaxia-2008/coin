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

#ifndef COIN_SOPICKSTYLEELEMENT_H
#define COIN_SOPICKSTYLEELEMENT_H

#include <Inventor/elements/SoInt32Element.h>


class COIN_DLL_API SoPickStyleElement : public SoInt32Element {
  typedef SoInt32Element inherited;

  SO_ELEMENT_HEADER(SoPickStyleElement);
public:
  static void initClass(void);
protected:
  virtual ~SoPickStyleElement();

public:
  enum Style {
    SHAPE,
    BOUNDING_BOX,
    UNPICKABLE
  };

  virtual void init(SoState * state);
  static void set(SoState * const state, SoNode * const node,
                  const int32_t style);
  static void set(SoState * const state, const Style style);
  static Style get(SoState * const state);
  static Style getDefault();
};

#endif // !COIN_SOPICKSTYLEELEMENT_H

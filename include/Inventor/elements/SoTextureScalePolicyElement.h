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

#ifndef COIN_SOTEXTURESCALEPOLICYELEMENT_H
#define COIN_SOTEXTURESCALEPOLICYELEMENT_H

#include <Inventor/elements/SoInt32Element.h>


class COIN_DLL_API SoTextureScalePolicyElement : public SoInt32Element {
  typedef SoInt32Element inherited;
  
  SO_ELEMENT_HEADER(SoTextureScalePolicyElement);

public:
  static void initClass(void);
protected:
  virtual ~SoTextureScalePolicyElement();

public:
  enum Policy {    
    USE_TEXTURE_QUALITY,
    SCALE_DOWN,
    SCALE_UP,
    DONT_SCALE
  };

  virtual void init(SoState * state);
  
  static  void set(SoState * const state, SoNode * const node,
                   const Policy policy);
  static  void set(SoState * const state, const Policy policy);
  static Policy get(SoState * const state);
  static Policy getDefault(void);

};

#endif // !COIN_SOTEXTURESCALEPOLICYELEMENT_H

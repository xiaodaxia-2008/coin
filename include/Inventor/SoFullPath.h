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

#ifndef COIN_SOFULLPATH_H
#define COIN_SOFULLPATH_H

#include <Inventor/SoPath.h>


class COIN_DLL_API SoFullPath : public SoPath {
  typedef SoPath inherited;
  friend class SoTempPath;

private:
  SoFullPath(const int approxLength);
  virtual ~SoFullPath(void);

public:
  void pop(void);
  SoNode * getTail(void) const;
  SoNode * getNodeFromTail(const int index) const;
  int getIndexFromTail(const int index) const;
  int getLength(void) const;
};

// inline methods

inline void
SoFullPath::pop(void)
{
  this->truncate(this->nodes.getLength() - 1);
}

#endif // !COIN_SOFULLPATH_H

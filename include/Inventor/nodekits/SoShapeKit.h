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

#ifndef COIN_SOSHAPEKIT_H
#define COIN_SOSHAPEKIT_H

#include <Inventor/nodekits/SoSeparatorKit.h>


class COIN_DLL_API SoShapeKit : public SoSeparatorKit {
  typedef SoSeparatorKit inherited;

  SO_KIT_HEADER(SoShapeKit);

  SO_KIT_CATALOG_ENTRY_HEADER(coordinate3);
  SO_KIT_CATALOG_ENTRY_HEADER(coordinate4);
  SO_KIT_CATALOG_ENTRY_HEADER(localTransform);
  SO_KIT_CATALOG_ENTRY_HEADER(materialBinding);
  SO_KIT_CATALOG_ENTRY_HEADER(normal);
  SO_KIT_CATALOG_ENTRY_HEADER(normalBinding);
  SO_KIT_CATALOG_ENTRY_HEADER(profileCoordinate2);
  SO_KIT_CATALOG_ENTRY_HEADER(profileCoordinate3);
  SO_KIT_CATALOG_ENTRY_HEADER(profileList);
  SO_KIT_CATALOG_ENTRY_HEADER(shape);
  SO_KIT_CATALOG_ENTRY_HEADER(shapeHints);
  SO_KIT_CATALOG_ENTRY_HEADER(shapeSeparator);
  SO_KIT_CATALOG_ENTRY_HEADER(textureCoordinate2);
  SO_KIT_CATALOG_ENTRY_HEADER(textureCoordinateBinding);
  SO_KIT_CATALOG_ENTRY_HEADER(textureCoordinateFunction);

public:
  SoShapeKit(void);

  static void initClass(void);

protected:
  virtual ~SoShapeKit();

  virtual void setDefaultOnNonWritingFields(void);
};

#endif // !COIN_SOSHAPEKIT_H

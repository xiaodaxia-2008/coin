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

#ifndef COIN_SOCONVEXDATACACHE_H
#define COIN_SOCONVEXDATACACHE_H

#include <Inventor/caches/SoCache.h>
#include <Inventor/system/inttypes.h>
#include <Inventor/lists/SbList.h>

class SbVec3f;
class SoCoordinateElement;
class SbMatrix;

class COIN_DLL_API SoConvexDataCache : public SoCache {
  typedef SoCache inherited;
public:
  SoConvexDataCache(SoState * const state);
  ~SoConvexDataCache();

  enum Binding {
    // do not change these values. We rely on them matching
    // values in SoIndededFaceSet.h and SoGL.cpp...
    NONE = 0,
    PER_FACE,
    PER_FACE_INDEXED,
    PER_VERTEX,
    PER_VERTEX_INDEXED
  };

  void generate(const SoCoordinateElement* const coords,
                const SbMatrix & matrix,
                const int32_t *coordindices,
                const int numcoordindices,
                const int32_t *matindices, const int32_t *normindices,
                const int32_t *texindices,
                const Binding matbinding, const Binding normbinding,
                const Binding texbinding);

  const int32_t *getCoordIndices() const;
  int getNumCoordIndices() const;
  const int32_t *getMaterialIndices() const;
  int getNumMaterialIndices() const;
  const int32_t *getNormalIndices() const;
  int getNumNormalIndices() const;
  const int32_t *getTexIndices() const;
  int getNumTexIndices() const;

private:
  SbList <int32_t> coordIndices;
  SbList <int32_t> normalIndices;
  SbList <int32_t> materialIndices;
  SbList <int32_t> texIndices;
};

#endif // !COIN_SOCONVEXDATACACHE_H

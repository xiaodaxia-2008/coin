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

#ifndef COIN_SOSEPARATOR_H
#define COIN_SOSEPARATOR_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/nodes/SoGroup.h>

class SoState;

class COIN_DLL_API SoSeparator : public SoGroup {
  typedef SoGroup inherited;

  SO_NODE_HEADER(SoSeparator);

public:
  static void initClass(void);
  SoSeparator(void);
  SoSeparator(const int nchildren);

  enum CacheEnabled {
    OFF, ON, AUTO
  };

  SoSFEnum renderCaching;
  SoSFEnum boundingBoxCaching;
  SoSFEnum renderCulling;
  SoSFEnum pickCulling;


  virtual void doAction(SoAction * action);
  virtual void GLRender(SoGLRenderAction * action);
  virtual void GLRenderBelowPath(SoGLRenderAction * action);
  virtual void GLRenderInPath(SoGLRenderAction * action);
  virtual void GLRenderOffPath(SoGLRenderAction * action);
  virtual void callback(SoCallbackAction * action);
  virtual void getBoundingBox(SoGetBoundingBoxAction * action);
  virtual void getMatrix(SoGetMatrixAction * action);
  virtual void handleEvent(SoHandleEventAction * action);
  virtual void rayPick(SoRayPickAction * action);
  virtual void search(SoSearchAction * action);
  virtual void getPrimitiveCount(SoGetPrimitiveCountAction * action);

  virtual void notify(SoNotList * nl);

  static void setNumRenderCaches(const int howmany);
  static int getNumRenderCaches(void);
  virtual SbBool affectsState(void) const;


protected:
  virtual ~SoSeparator();

  virtual SbBool cullTest(SoState * state);
  virtual SbBool cullTest(SoGLRenderAction * action, int & cullresults);
  virtual SbBool readInstance(SoInput * in, unsigned short flags);


private:
  void commonConstructor(void);
  SbBool cullTestNoPush(SoState * state);
  
  class SoBoundingBoxCache * bboxcache;
  class SoGLCacheList * glcachelist;
  static int numrendercaches;
};

#endif // !COIN_SOSEPARATOR_H

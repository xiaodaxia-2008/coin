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

#ifndef COIN_SOWINDOWELEMENT_H
#define COIN_SOWINDOWELEMENT_H

#include <Inventor/elements/SoSubElement.h>

// FIXME: ugly -- this pucks up system-independence within the base
// Coin library. What is this element used for anyway? 19990808 mortene.
#if defined(_WIN32) || defined(__BEOS__)
typedef void * Window;
typedef void * GLXContext;
typedef void Display;
#else // ! _WIN32 && ! __BEOS__
#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#endif // _WIN32 || __BEOS__

class SoGLRenderAction;


class COIN_DLL_EXPORT SoWindowElement : public SoElement {
  typedef SoElement inherited;

  SO_ELEMENT_HEADER(SoWindowElement);
public:
  static void initClass(void);
protected:
  virtual ~SoWindowElement();

public:
  virtual void init(SoState * state);

  virtual void push(SoState * state);
  virtual void pop(SoState * state, const SoElement * prevTopElement);

  virtual SbBool matches(const SoElement * element) const;
  virtual SoElement * copyMatchInfo(void) const;

  static  void set(SoState * const state, const Window & window,
                   const GLXContext & context, Display * const display,
                   SoGLRenderAction * const action);
  static  void get(SoState * const state, Window & window,
                   GLXContext & context, Display * & display,
                   SoGLRenderAction * & action);

protected:
  Window window;
  GLXContext context;
  Display * display;
  SoGLRenderAction * glRenderAction;

};

#endif // !COIN_SOWINDOWELEMENT_H

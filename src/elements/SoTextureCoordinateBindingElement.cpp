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

/*!
  \class SoTextureCoordinateBindingElement Inventor/elements/SoTextureCoordinateBindingElement.h
  \brief The SoTextureCoordinateBindingElement class is yet to be documented.
  \ingroup elements

  FIXME: write doc.
*/

#include <Inventor/elements/SoTextureCoordinateBindingElement.h>


#include <assert.h>

/*!
  \fn SoTextureCoordinateBindingElement::Binding

  FIXME: write doc.
*/

SO_ELEMENT_SOURCE(SoTextureCoordinateBindingElement);

/*!
  This static method initializes static data for the
  SoTextureCoordinateBindingElement class.
*/

void
SoTextureCoordinateBindingElement::initClass(void)
{
  SO_ELEMENT_INIT_CLASS(SoTextureCoordinateBindingElement, inherited);
}

/*!
  The destructor.
*/

SoTextureCoordinateBindingElement::~SoTextureCoordinateBindingElement(void)
{
}

//! FIXME: write doc.

void
SoTextureCoordinateBindingElement::set(SoState * const state,
                                       SoNode * const node,
                                       const Binding binding)
{
  assert(binding == PER_VERTEX || binding == PER_VERTEX_INDEXED);
  SoInt32Element::set(classStackIndex, state, node, binding);
}

//! FIXME: write doc.

void
SoTextureCoordinateBindingElement::init(SoState * state)
{
  inherited::init(state);
  this->data = SoTextureCoordinateBindingElement::getDefault();
}

//! FIXME: write doc.

//$ EXPORT INLINE
void
SoTextureCoordinateBindingElement::set(SoState * const state,
                                       const Binding binding)
{
  set(state, NULL, binding);
}

//! FIXME: write doc.

//$ EXPORT INLINE
SoTextureCoordinateBindingElement::Binding
SoTextureCoordinateBindingElement::get(SoState * const state)
{
  return (Binding)SoInt32Element::get(classStackIndex, state);
}

//! FIXME: write doc.

//$ EXPORT INLINE
SoTextureCoordinateBindingElement::Binding
SoTextureCoordinateBindingElement::getDefault()
{
  return PER_VERTEX_INDEXED;
}

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

// Important note: this sourcefile was in full generated by the
// Coin/scripts/templant script from the code in SFNodeEnginePath.tpl.

///////////////////////////////////////////////////////////////////////////


//$ BEGIN TEMPLATE SFNodeEnginePath(ENGINE, Engine, engine)

/*!
  \class SoSFEngine SoSFEngine.h Inventor/fields/SoSFEngine.h
  \brief The SoSFEngine class is a container for a single engine.
  \ingroup fields

  This field container stores a pointer to a Coin engine. It takes care
  of the necessary functionality for handling copy, import and export
  operations.

  Note that the engine pointer stored in a field instance of this type
  may be a \c NULL pointer.

  \sa SoEngine, SoMFEngine

*/

// Type-specific define to be able to do #ifdef tests on type.  (Note:
// used to check the header file wrapper define, but that doesn't work
// with --enable-compact build.)
#define COIN_INTERNAL_ENGINE

#include <Inventor/fields/SoSFEngine.h>
#include <Inventor/fields/SoSubFieldP.h>

#include <Inventor/SoInput.h>
#include <Inventor/SoOutput.h>
#include <Inventor/actions/SoWriteAction.h>
#include <Inventor/errors/SoReadError.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/engines/SoEngine.h>
#if COIN_DEBUG
#include <Inventor/errors/SoDebugError.h>
#endif // COIN_DEBUG


// Can't use SO_SFIELD_SOURCE() because we need to modify setValue()
// to ref and unref the passed engine.
SO_SFIELD_REQUIRED_SOURCE(SoSFEngine);


// Override from parent class.
void
SoSFEngine::initClass(void)
{
  SO_SFIELD_INTERNAL_INIT_CLASS(SoSFEngine);
}

// (Declarations hidden in SO_[S|M]FIELD_HEADER macro in header file,
// so don't use Doxygen commenting.)
#ifndef DOXYGEN_SKIP_THIS

/* Constructor, sets initial engine pointer to a \c NULL pointer. */
SoSFEngine::SoSFEngine(void)
{
  this->value = NULL;
#ifdef COIN_INTERNAL_PATH
  this->head = NULL;
#endif // COIN_INTERNAL_PATH
}

/* Destructor, dereferences the current engine pointer if necessary. */
SoSFEngine::~SoSFEngine(void)
{
  this->enableNotify(FALSE);
  this->setValue(NULL);
}

#endif // DOXYGEN_SKIP_THIS


// No need to document readValue() and writeValue() here, as the
// necessary information is provided by the documentation of the
// parent classes.
#ifndef DOXYGEN_SKIP_THIS

// Store the \a newval engine pointer in this field. If \a newval is not
// \c NULL, will add 1 to the reference count of the engine.
void
SoSFEngine::setValue(SoEngine * newval)
{
  // Don't use getValue() to find oldptr, since this might trigger a
  // recursive evaluation call if the field is connected.
  SoEngine * oldptr = this->value;
  if (oldptr == newval) return;

  if (oldptr) {
    oldptr->removeAuditor(this, SoNotRec::FIELD);
    oldptr->unref();
#ifdef COIN_INTERNAL_PATH
    SoNode * h = oldptr->getHead();
    // The path should be audited by us at all times. So don't use
    // SoSFPath to wrap SoTempPath or SoLightPath, for instance.
    assert(h==this->head && "Path head changed without notification!");
    if (h) {
      h->removeAuditor(this, SoNotRec::FIELD);
      h->unref();
    }
#endif // COIN_INTERNAL_PATH
  }

  if (newval) {
    newval->addAuditor(this, SoNotRec::FIELD);
    newval->ref();
#ifdef COIN_INTERNAL_PATH
    this->head = newval->getHead();
    if (this->head) {
      this->head->addAuditor(this, SoNotRec::FIELD);
      this->head->ref();
    }
#endif // COIN_INTERNAL_PATH
  }

  this->value = newval;
  this->valueChanged();
}

// Compares to see if the \a field points to the same engine as this
// field does, and returns \c TRUE if this is the case.
//
// Be aware that this method does \e not check for engine/subgraph
// equality if the pointers are not the same, so \c FALSE is returned
// even though the contents of the engine/subgraph are equal.
SbBool
SoSFEngine::operator==(const SoSFEngine & field) const
{
  return (this->getValue() == field.getValue());
}

// Import engine.
SbBool
SoSFEngine::readValue(SoInput * in)
{
  SoBase * baseptr;
  if (!SoBase::read(in, baseptr, SoEngine::getClassTypeId())) return FALSE;

  if (in->eof()) {
    SoReadError::post(in, "Premature end of file");
    return FALSE;
  }

  this->setValue((SoEngine *)baseptr);
  return TRUE;
}

// Export engine.
void
SoSFEngine::writeValue(SoOutput * out) const
{
  SoBase * base = this->getValue();
  if (base) {
    if (base->isOfType(SoNode::getClassTypeId())) {
      SoWriteAction wa(out);
      wa.continueToApply((SoNode *)base);
    }
    else if (base->isOfType(SoPath::getClassTypeId())) {
      SoWriteAction wa(out);
      wa.continueToApply((SoPath *)base);
    }
    else if (base->isOfType(SoEngine::getClassTypeId())) {
      ((SoEngine *)base)->writeInstance(out);
    }
    else {
      assert(0 && "strange internal error");
    }
  }
  else {
    // This actually works for both ASCII and binary formats.
    out->write("NULL");
  }
}

#endif // DOXYGEN_SKIP_THIS


// Overridden from parent to propagate write reference counting to
// engine.
void
SoSFEngine::countWriteRefs(SoOutput * out) const
{
  inherited::countWriteRefs(out);

  SoEngine * n = this->getValue();
  // Set the "from field" flag as FALSE, as that flag is meant to be
  // used for references through field-to-field connections.
  if (n) n->addWriteReference(out, FALSE);
#ifdef COIN_INTERNAL_PATH
  if (n && n->getHead()) n->getHead()->addWriteReference(out, FALSE);
#endif // COIN_INTERNAL_PATH
}

// Override from parent to update our engine pointer reference.
void
SoSFEngine::fixCopy(SbBool copyconnections)
{
  SoEngine * n = this->getValue();
  if (!n) return;

  // There's only been a bitwise copy of the pointer; no auditing has
  // been set up, no increase in the reference count. So we do that by
  // setting the value to NULL and then re-setting with setValue().
  this->value = NULL;

#if defined(COIN_INTERNAL_NODE) || defined(COIN_INTERNAL_ENGINE)
  SoFieldContainer * fc = SoFieldContainer::findCopy(n, copyconnections);
  this->setValue((SoEngine *)fc);
#endif // COIN_INTERNAL_NODE || COIN_INTERNAL_ENGINE

#ifdef COIN_INTERNAL_PATH
  this->setValue(n->copy());
#endif // COIN_INTERNAL_PATH
}

// Override from SoField to check engine pointer.
SbBool
SoSFEngine::referencesCopy(void) const
{
  if (inherited::referencesCopy()) return TRUE;

  SoBase * n = this->getValue();
  if (!n) return FALSE;

  if (n->isOfType(SoNode::getClassTypeId()) ||
      n->isOfType(SoEngine::getClassTypeId())) {
    if (SoFieldContainer::checkCopy((SoFieldContainer *)n)) return TRUE;
  }
  else if (n->isOfType(SoPath::getClassTypeId())) {
    SoPath * p = (SoPath *)n;
    if (p->getHead() == NULL) return FALSE;
    if (SoFieldContainer::checkCopy(p->getHead())) return TRUE;
  }
  else {
    assert(0 && "strange internal error");
  }

  return FALSE;
}

// Kill the type-specific define.
#undef COIN_INTERNAL_ENGINE
//$ END TEMPLATE SFNodeEnginePath

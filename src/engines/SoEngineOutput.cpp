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
  \class SoEngineOutput SoEngine.h Inventor/engines/SoEngine.h
  \brief The SoEngineOutput class is the output slots in SoEngine instances.
  \ingroup engines

  SoEngineOutput has methods for convenient handling of the
  connections made from SoEngine objects to SoField objects.

  \sa SoEngine, SoField
 */

#include <Inventor/engines/SoEngineOutput.h>
#include <Inventor/engines/SoEngine.h>
#include <Inventor/engines/SoNodeEngine.h>
#include <Inventor/engines/SoOutputData.h>
#include <Inventor/fields/SoField.h>

#if COIN_DEBUG
#include <Inventor/errors/SoDebugError.h>
#endif // COIN_DEBUG

// FIXME: part of the "store-list-in-dict" hack to keep ABI
// compatibility.  20010910 mortene.
static const unsigned long SOENGINEOUTPUT_MAGICNUMBER = 0xdeadbeef;

/*!
  Constructor. The SoEngineOutput will initially not be contained
  within an SoEngine nor will it have any slave fields attached.

  \sa setContainer()
*/
SoEngineOutput::SoEngineOutput(void)
  : notifyflags(1)
{
  this->enabled = TRUE;
  this->container = NULL;

  SbList<SbBool> * fieldnotiflist = new SbList<SbBool>;
  this->notifyflags.enter(SOENGINEOUTPUT_MAGICNUMBER, fieldnotiflist);
}

/*!
  Destructor.
*/
SoEngineOutput::~SoEngineOutput()
{
#if COIN_DEBUG && 0 // debug
  SoDebugError::postInfo("SoEngineOutput::~SoEngineOutput", "start %p", this);
#endif // debug

  // FIXME: the "list-in-dict" hack to keep ABI
  // compatibility. 20010910 mortene.
  void * vval;
  SbBool r = this->notifyflags.find(SOENGINEOUTPUT_MAGICNUMBER, vval);
  assert(r);
  SbList<SbBool> * notiflist = (SbList<SbBool> *)vval;
  delete notiflist;

  // Avoids evaluation from the fields in SoField::disconnect() (which
  // would again lead to problems with the pure virtual
  // SoEngine::evaluate() function during destruction of our
  // container).
  this->enabled = FALSE;

  // Disconnect all fields.
  SoFieldList fl;
  int nr = this->getForwardConnections(fl);
  for (int i=0; i < nr; i++) fl[i]->disconnect(this);

#if COIN_DEBUG && 0 // debug
  SoDebugError::postInfo("SoEngineOutput::~SoEngineOutput", "done %p", this);
#endif // debug
}

/*!
  Returns the type of the engine output.
*/
SoType
SoEngineOutput::getConnectionType(void) const
{
  assert(this->container != NULL);
  const SoEngineOutputData * outputs = 
    this->isNodeEngineOutput() ? 
    this->getNodeContainer()->getOutputData() : 
    this->getContainer()->getOutputData();
  assert(outputs);
  int idx = outputs->getIndex(this->container, this);
  assert(idx >= 0 && "an engine should have at least one output");
  return outputs->getType(idx);
}

/*!
  Adds all slave fields connected to this output to \a fl.  Returns
  the number of slaves.

  \sa addConnection()
  \sa removeConnection()
*/
int
SoEngineOutput::getForwardConnections(SoFieldList & fl) const
{
  int n = this->slaves.getLength();
  for (int i = 0; i < n; i++) fl.append(this->slaves[i]);
  return n;
}

/*!
  Sets the enabled flag. If output is disabled, the fields connected
  to this output will not be changed when the engine is evaluated.

  \sa isEnabled().
*/
void
SoEngineOutput::enable(const SbBool flag)
{
  this->enabled = flag;
  if (flag) this->touchSlaves(NULL, FALSE);
}

/*!
  Returns status of the enabled flag.

  \sa enable().
*/
SbBool
SoEngineOutput::isEnabled(void) const
{
  return this->enabled;
}

/*!  
  Returns the engine containing this output. If the engine
  containing this output is a NodeEngine, this method returns NULL.

  \sa setContainer(), getNodeContainer() 
*/
SoEngine *
SoEngineOutput::getContainer(void) const
{
  if (this->isNodeEngineOutput()) {
#if COIN_DEBUG
    SoDebugError::postWarning("SoEngineOutput::getContainer",
                              "Container is not an Engine");
#endif // COIN_DEBUG
    return NULL;
  }
  return this->container;
}

/*!  

  Returns the node engine containing this output. If the engine
  containing this output is not a NodeEgine, this method returns NULL.

  This method was not part of the Open Inventor 2.1 API, and is an
  extension specific to Coin.

  \since 2001-10-19

  \sa setNodeContainer(), getContainer() 
*/

SoNodeEngine * 
SoEngineOutput::getNodeContainer(void) const
{
  if (!this->isNodeEngineOutput()) {
#if COIN_DEBUG
    SoDebugError::postWarning("SoEngineOutput::getContainer",
                              "Container is not a NodeEngine");
#endif // COIN_DEBUG
    return NULL;
  }
  return (SoNodeEngine*) this->container;
}

/*!
  Returns \e TRUE if the container is a NodeEngine.

  This method was not part of the Open Inventor 2.1 API, and is an
  extension specific to Coin.

  \since 2001-10-19

  \sa getNodeContainer(), getContainer() 
*/
SbBool 
SoEngineOutput::isNodeEngineOutput(void) const
{
  assert(this->container);
  return this->container->getTypeId().isDerivedFrom(SoNodeEngine::getClassTypeId());
}

/*!
  Sets the engine containing this output.

  \sa getContainer()
*/
void
SoEngineOutput::setContainer(SoEngine * engine)
{
  this->container = engine;
}


/*!
  Sets the NodeEngine containing this output.

  This method was not part of the Open Inventor 2.1 API, and is an
  extension specific to Coin.

  \since 2001-10-19

  \sa getNodeContainer()
*/

void 
SoEngineOutput::setNodeContainer(SoNodeEngine * nodeengine)
{
  // FIXME: need a union as member instead of container
  this->container = (SoEngine*) nodeengine;
}

/*!
  Adds \a f to the list of connections from this output.

  Adds 1 to the reference count of the container engine.

  \sa removeConnection(), getForwardConnections()
*/
void
SoEngineOutput::addConnection(SoField * f)
{
  int i = this->slaves.find(f);
#if COIN_DEBUG
  if (i != -1) {
    SoDebugError::postWarning("SoEngineOutput::addConnection",
                              "connection from %p already made", f);
    return;
  }
#endif // COIN_DEBUG
  this->slaves.append(f);
  this->getFieldContainer()->ref();
}

/*!
  Removes \a f from the list of connections from this output.

  Subtracts 1 from the reference count of the container engine. If the
  reference count reaches zero (which will happen if this was the last
  connection and the application programmer did not explicitly \e ref
  the engine), the container engine will be deallocated.

  \sa addConnection(), getForwardConnections()
*/
void
SoEngineOutput::removeConnection(SoField * f)
{
  int i = this->slaves.find(f);
#if COIN_DEBUG
  if (i == -1) {
    SoDebugError::postWarning("SoEngineOutput::removeConnection",
                              "no connection from %p present", f);
    return;
  }
#endif // COIN_DEBUG
  this->slaves.remove(i);
  this->getFieldContainer()->unref();
}

/*!
  Returns the number of fields in the list of connections.

  \sa operator[], addConnection()
*/
int
SoEngineOutput::getNumConnections(void) const
{
  return this->slaves.getLength();
}

/*!
  Returns the field at index \a i in the list of connections.

  \sa getNumConnections()
*/
SoField *
SoEngineOutput::operator[](int i) const
{
  return this->slaves[i];
}

/*!
  Disables notifications on fields connected to this output.  This is
  done before the engine is evaulated, since the fields we are going
  to write into have already been notified.

  \sa doneWriting()
*/
void
SoEngineOutput::prepareToWrite(void) const
{
  // FIXME: the "list-in-dict" hack to keep ABI
  // compatibility. 20010910 mortene.
  void * vval;
  SbBool r = this->notifyflags.find(SOENGINEOUTPUT_MAGICNUMBER, vval);
  assert(r);
  SbList<SbBool> * notiflist = (SbList<SbBool> *)vval;

  notiflist->truncate(0);

  int n = this->slaves.getLength();
  for (int i = 0; i < n; i++) {
    SoField * f = this->slaves[i];
    notiflist->append(f->isNotifyEnabled());
    f->enableNotify(FALSE);
  }
}

/*!
  Restores the notification flags on fields connected to this output
  after evaluating.

  \sa prepareToWrite()
*/
void
SoEngineOutput::doneWriting(void) const
{
  // FIXME: the "list-in-dict" hack to keep ABI
  // compatibility. 20010910 mortene.
  void * vval;
  SbBool r = this->notifyflags.find(SOENGINEOUTPUT_MAGICNUMBER, vval);
  assert(r);
  SbList<SbBool> * notiflist = (SbList<SbBool> *)vval;

  // We should have the exact same set of slave fields now as on entry
  // to prepareToWrite(), as the field writing is supposed be a
  // "closed" operation.  (All notifications on the fields are
  // disabled, so no application code should be able to intervene in
  // SoEngine evaluation.)

  int n = this->slaves.getLength();
  assert(n == notiflist->getLength());

  const SbBool * notifs = notiflist->getArrayPtr();

  for (int i = 0; i < n; i++) {
    this->slaves[i]->enableNotify(notifs[i]);
  }
}

/*!
  Notify the fields attached to this engine output that the output
  value has changed.

  If \a donotify is \c TRUE, propagate the notification to the
  fields. Otherwise just mark the fields "dirty" for re-evalution.

  Note that this method is not part of the original Open Inventor API.
 */
void
SoEngineOutput::touchSlaves(SoNotList * nl, SbBool donotify)
{
  if (this->isEnabled()) {
    int numconnections = this->getNumConnections();
    for (int j = 0; j < numconnections; j++) {
      SoField * field = (*this)[j];
      if (donotify) field->notify(nl);
      else field->setDirty(TRUE);
    }
  }
}

/*!
  Convenience method that returns a field container. This method can
  be used both for NodeEngine and Engine outputs.

  This method was not part of the Open Inventor 2.1 API, and is an
  extension specific to Coin.

  \since 2001-10-19
*/
SoFieldContainer * 
SoEngineOutput::getFieldContainer(void)
{
  return (SoFieldContainer*) this->container;
}

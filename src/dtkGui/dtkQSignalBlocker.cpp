/* dtkQSignalBlocker.h --- 
 * 
 * Author: John Stark
 * Copyright (C) 2011 - John Stark, Inria.
 *     Update #: 1
 */

/* Commentary:
 * This file only provides documentation - the implementation of the class
 * is in the header.
 */

#include "dtkQSignalBlocker.h"

// dtkQSignalBlocker :

/*! \class      dtkQSignalBlocker
 *  \brief      Blocks signals to a given object as long it remains instantiated.
 *
 * The purpose is to increase exception-safety and to ensure that objects are
 * not still unintentionally blocked what ever the return path from a function.
 *
 * object->blockSignals(true) is called when the signalBlocker is created, and
 * object->blockSignals(false) is called when the signalBlocker is destroyed. This
 * ensures that a managed object is always unblocked, whatever the return path.
 *
 * Code example :
 * \code
 *  {
 *    dtkQSignalBlocker blocker( mySlider );
 *    // code which generates signals that mySlider needs to be protected from.
 *  }
 * \endcode
  */

/*! \fn         dtkQSignalBlocker::ObjectType;
    \brief      Access to the managed type, typedef for T.
*/

/*! \fn         dtkQSignalBlocker::dtkQSignalBlocker(QObject * o)
    \brief      Constructor. Immediately calls o->blockSignals(true);
    \param      o : QObject that is blocked.
*/

/*! \fn         dtkQSignalBlocker::~dtkQSignalBlocker()
    \brief      Destructor. Calls o->blockSignals(false);
*/

/*! \fn         dtkSmartPointer::blockSignals( bool v )
    \brief      Allows early unblocking / reblocking
    \param      v : passed to object->blockSignals(v).
*/


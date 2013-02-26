/* dtkObject.cpp --- 
 * 
 * Author: Thibaud Kloczko
 * Created: 2013 Wed Feb 13 21:49:35 (+0100)
 */

/* Commentary: 
 * This file only provides documentation of the pure dtkObject interface.
 */

/* Change log:
 *
 */

// /////////////////////////////////////////////////////////////////
// dtkObject 
// /////////////////////////////////////////////////////////////////

#include "dtkObject.h"

/*! \class      dtkObject
 *  \brief      Interface providing mandatory methods for all dtk subclasses.
 */

/*! \fn         dtkObject::dtkObject(QObject *parent = 0)
    \brief      Constructs an object with parent object parent.
                The parent of an object may be regarded as the object's owner.
                The destructor of a parent object destroys all child objects.
                Setting parent to NULL (ie 0) constructs an object with no parent. 
*/

/*! \fn         dtkObject::~dtkObject(void)
    \brief      Destroys the object, deleting all its child objects.
*/

/*! \fn         dtkObject *dtkObject::clone(void) const
    \brief      Virtual copy constructor avoiding slicing issues. 
                All subclasses must implement this method in order to
                ensure deep copy of the current object whatever the
                level of the class hierarchy it is used.
    \return     A new object that has the same content than the current object.
*/

/*! \fn         QString dtkObject::identifier(void) const
    \brief      Identifies the class of the object.
                All subclasses must implement this method in order to
                provide convenient typename checking.
    \return     The class name of the object.
*/

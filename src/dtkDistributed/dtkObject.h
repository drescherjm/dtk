/* dtkObject.h --- 
 * 
 * Author: Thibaud Kloczko
 * Created: 2013 Wed Feb 13 21:34:45 (+0100)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

#include <QtCore/QObject>

// /////////////////////////////////////////////////////////////////
// dtkObject interface
// /////////////////////////////////////////////////////////////////

class dtkObject : public QObject
{
    Q_OBJECT

public:
    dtkObject(QObject *parent = 0) {;}
    virtual ~dtkObject(void) {;}

public:
    virtual dtkObject *clone(void) = 0;

public:
   virtual QString identifier(void) const = 0;
};


Q_DECLARE_METATYPE(dtkObject*);

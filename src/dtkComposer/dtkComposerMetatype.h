/* dtkComposerMetatype.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Sat Aug  4 00:26:47 2012 (+0200)
 * Version: $Id$
 * Last-Updated: 2013 Fri Jan 18 13:53:30 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 51
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERMETATYPE_H
#define DTKCOMPOSERMETATYPE_H

#include <QtCore>



// /////////////////////////////////////////////////////////////////
// Custom type id for dtk major types
// /////////////////////////////////////////////////////////////////

static const qlonglong dtkAbstractData_Id  = 1024;
static const qlonglong dtkMatrixReal_Id    = 1025;
static const qlonglong dtkMatrixInteger_Id = 1026;

static const qlonglong dtkPlotCurve_Id = 2048;

// /////////////////////////////////////////////////////////////////
// dtkComposerMetaTypes singleton
// /////////////////////////////////////////////////////////////////

class dtkComposerMetaTypes : public QMap<qint64, qint64>
{
public:
    static dtkComposerMetaTypes *instance(void);

private:
     dtkComposerMetaTypes(void);
    ~dtkComposerMetaTypes(void);

private:
    static dtkComposerMetaTypes *s_instance;
};

inline dtkComposerMetaTypes *dtkComposerMetaTypes::instance(void)
{
    if(!s_instance)
        s_instance = new dtkComposerMetaTypes;
    
    return s_instance;
}

inline dtkComposerMetaTypes::dtkComposerMetaTypes(void) : QMap<qint64, qint64>()
{

}

inline dtkComposerMetaTypes::~dtkComposerMetaTypes(void)
{

}

// /////////////////////////////////////////////////////////////////
// Helper shortcut
// /////////////////////////////////////////////////////////////////

#define dtkComposerTypes dtkComposerMetaTypes::instance()

#endif

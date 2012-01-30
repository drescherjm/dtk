/* dtkComposer_p.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 10:35:09 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Jan 30 15:33:25 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 28
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSER_P_H
#define DTKCOMPOSER_P_H

#include <QtCore>

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

class dtkComposerScene;
class dtkComposerView;

class dtkComposerPrivate : public QObject
{
    Q_OBJECT

public:
    dtkComposerScene *scene;
    dtkComposerView *view;
};

#endif

/* dtkComposerControls.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Nov 20 16:16:42 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Mar 20 13:02:14 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 28
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERCONTROLS_H
#define DTKCOMPOSERCONTROLS_H

#include <QtGui>
#include <QtWidgets>

class dtkComposerControlsPrivate;
class dtkComposerScene;

class  dtkComposerControls : public QFrame
{
    Q_OBJECT

public:
    enum Type {
        Integer,
           None
    };

public:
     dtkComposerControls(QWidget *parent = 0);
    ~dtkComposerControls(void);

public:
    void setScene(dtkComposerScene *scene);

protected slots:
    void setup(void);
    void setup(int index);

private:
    dtkComposerControlsPrivate *d;
};

#endif

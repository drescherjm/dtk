/* dtkComposerPath.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Nov 19 11:40:26 2012 (+0100)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

#include "dtkComposerExport.h"

#include <QtCore>
#include <QtWidgets>

class dtkComposerPathPrivate;
class dtkComposerScene;

class DTKCOMPOSER_EXPORT dtkComposerPath : public QFrame
{
    Q_OBJECT

public:
     dtkComposerPath(QWidget *parent = 0);
    ~dtkComposerPath(void);

public:
    void setScene(dtkComposerScene *scene);

public:
    QSize sizeHint(void) const;

public slots:
    void update(void);

private:
    dtkComposerPathPrivate *d;
};


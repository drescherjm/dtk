/* dtkSplitter.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Oct  7 23:16:58 2008 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Mar 21 10:47:52 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 37
 */

/* Commentary:
 *
 */

/* Change log:
 * 
 */

#ifndef DTKSPLITTER_H
#define DTKSPLITTER_H

#include <QSplitter>

#include <dtkCore/dtkGlobal.h>

#include <dtkGui/dtkGuiExport.h>

class dtkSplitterPrivate;

class DTKGUI_EXPORT dtkSplitter : public QSplitter
{
    Q_OBJECT

public:
     dtkSplitter(QWidget *parent = 0, bool slim = true);
    ~dtkSplitter(void);

    QSplitterHandle *createHandle(void);

private:
    dtkSplitterPrivate *d;
};

#endif

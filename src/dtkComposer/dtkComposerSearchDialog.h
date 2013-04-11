/* dtkComposerSearchDialog.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Nov  5 16:35:28 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Apr 11 10:32:14 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 25
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

#include <QtGui>

class dtkComposerScene;
class dtkComposerSearchDialogPrivate;
class dtkComposerView;

class  dtkComposerSearchDialog : public QDialog
{
    Q_OBJECT

public:
     dtkComposerSearchDialog(dtkComposerView *parent = 0);
    ~dtkComposerSearchDialog(void);

public:
    void setScene(dtkComposerScene *scene);

protected slots:
    void find(void);
    void next(void);
    void more(void);
    void clear(void);

private:
    dtkComposerSearchDialogPrivate *d;
};


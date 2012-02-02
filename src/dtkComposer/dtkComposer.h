/* dtkComposer.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 10:34:34 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb  1 22:37:48 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 31
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSER_H
#define DTKCOMPOSER_H

#include "dtkComposerExport.h"
#include "dtkComposerWriter.h"

#include <QtCore>
#include <QtGui>

class dtkComposerFactory;
class dtkComposerMachine;
class dtkComposerPrivate;
class dtkComposerStack;

class DTKCOMPOSER_EXPORT dtkComposer : public QWidget
{
    Q_OBJECT

public:
             dtkComposer(QWidget *parent = 0);
    virtual ~dtkComposer(void);

public slots:
    virtual bool   open(const QUrl& url);
    virtual bool   open(QString file);
    virtual bool   save(QString file = QString(), dtkComposerWriter::Type type = dtkComposerWriter::Ascii);
    virtual bool insert(QString file);

signals:
    void modified(bool);

public:
    dtkComposerFactory *factory(void);
    dtkComposerMachine *machine(void);
    dtkComposerStack *stack(void);

private:
    dtkComposerPrivate *d;
};

#endif

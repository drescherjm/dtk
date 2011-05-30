/* tstInspectorDistributed.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed May 25 16:16:50 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Mon May 30 10:57:39 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 18
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef TSTINSPECTORDISTRIBUTED_H
#define TSTINSPECTORDISTRIBUTED_H

#include <QtCore>
#include <QtGui>

class tstInspectorDistributedPrivate;

class tstInspectorDistributed : public QFrame
{
    Q_OBJECT

public:
     tstInspectorDistributed(QWidget *parent = 0);
    ~tstInspectorDistributed(void);

signals:
    void    connect(const QUrl& server);
    void disconnect(const QUrl& server);
    void submit(void);

protected slots:
    void    onConnect(void);
    void onDisconnect(void);
    void onSubmit(void);

private:
    tstInspectorDistributedPrivate *d;
};

#endif

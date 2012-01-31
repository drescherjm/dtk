/* dtkComposerFactoryView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jan 31 13:22:54 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Jan 31 13:51:20 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 11
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERFACTORYVIEW_H
#define DTKCOMPOSERFACTORYVIEW_H

#include <QtCore>
#include <QtGui>

class dtkComposerFactory;
class dtkComposerFactoryViewPrivate;

class dtkComposerFactoryView : public QTreeWidget
{
    Q_OBJECT

public:
     dtkComposerFactoryView(QWidget *parent = 0);
    ~dtkComposerFactoryView(void);

public:
    void setFactory(dtkComposerFactory *factory);

public slots:
    void addItem(const QString& node, const QString& type);

public slots:
    void filter(const QString& text);

protected:
     QMimeData *mimeData(const QList<QTreeWidgetItem *> items) const;
    QStringList mimeTypes(void) const;

private:
    dtkComposerFactoryViewPrivate *d;
};

#endif

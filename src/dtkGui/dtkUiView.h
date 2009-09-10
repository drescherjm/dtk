/* dtkUiView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Jun 12 17:32:15 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Sep  9 09:44:33 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 66
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKUIVIEW_H
#define DTKUIVIEW_H

#include <QtGui/QTreeView>
#include <QtGui/QHeaderView>
#include <QtGui/QMouseEvent>

#include "dtkGuiExport.h"

class dtkUiItem;
class dtkUiViewPrivate;

class DTKGUI_EXPORT dtkUiView : public QTreeView
{
    Q_OBJECT

public:
     dtkUiView(QWidget *parent = 0);
    ~dtkUiView(void);

    void append(dtkUiItem *item);

    QSize minimumSizeHint(void) const;

signals:
    void linkClicked(const QString& key, const QVariant& value);
    void valueClicked(const QString& key, const QVariant& value);
    void buttonClicked(const QString& key, const QVariant& value);
    void multiValueClicked(const QString& key, const QVariant& value);

    void updated(void);

private slots:
    void booleanDoubleClicked(const QModelIndex& index);

private:
    dtkUiViewPrivate *d;
};

#endif

/* dtkComposerQuickView.h ---
 * 
 * Author: Julien Wintz
 * Created: Wed Apr 17 10:36:56 2013 (+0200)
 * Version: 
 * Last-Updated: Wed Apr 17 13:38:53 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 16
 */

/* Change Log:
 * 
 */

#pragma once

#include <QtCore>
#include <QtGui>
#include <QtQuick>

class dtkComposerQuickViewPrivate;

class dtkComposerQuickView : public QQuickPaintedItem
{
    Q_OBJECT

public:
     dtkComposerQuickView(QQuickItem *parent = 0);
    ~dtkComposerQuickView(void);

protected slots:
    void paint(QPainter *painter);

private:
    dtkComposerQuickViewPrivate *d;
};

QML_DECLARE_TYPE(dtkComposerQuickView)

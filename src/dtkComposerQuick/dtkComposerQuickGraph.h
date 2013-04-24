/* dtkComposerQuickGraph.h ---
 * 
 * Author: Julien Wintz
 * Created: Fri Apr 19 10:57:27 2013 (+0200)
 * Version: 
 * Last-Updated: Fri Apr 19 11:24:35 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 8
 */

/* Change Log:
 * 
 */

#pragma once

#include <dtkComposer>

#include <QtQuick>

class dtkComposerQuickGraphPrivate;

class dtkComposerQuickGraph : public QObject
{
    Q_OBJECT

public:
     dtkComposerQuickGraph(QObject *parent = 0);
    ~dtkComposerQuickGraph(void);

public:
    dtkComposerGraph *graph(void);

private:
    dtkComposerQuickGraphPrivate *d;
};

QML_DECLARE_TYPE(dtkComposerQuickGraph)

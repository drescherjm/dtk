/* dtkComposerGraphView.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Feb  9 14:42:13 2012 (+0100)
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include "dtkComposerExport.h"

#include <QtWidgets>
#include <QSvgWidget>

class dtkComposerGraphViewPrivate;
class dtkComposerGraph;


class DTKCOMPOSER_EXPORT dtkComposerGraphView : public QSvgWidget
{
    Q_OBJECT

public:
    dtkComposerGraphView(QWidget *parent = 0);
    ~dtkComposerGraphView(void);

public:
    void setGraph(dtkComposerGraph *graph);

public slots:
    void update(void);

private:
    dtkComposerGraphViewPrivate *d;
};


/* dtkComposerNodePlotCurveFile.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue May 29 14:32:55 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Jun 19 15:57:31 2013 (+0200)
 *           By: Selim Kraria
 *     Update #: 35
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODEPLOTCURVEFILE_H
#define DTKCOMPOSERNODEPLOTCURVEFILE_H

#include "dtkComposerSupportExport.h"
#include "dtkComposerNodeLeaf.h"

#include <QtCore>

class dtkComposerNodePlotCurveFilePrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodePlotCurveFile : public QObject, public dtkComposerNodeLeaf
{
    Q_OBJECT

public:
    dtkComposerNodePlotCurveFile(void);
    ~dtkComposerNodePlotCurveFile(void);

public:
    void run(void);

public:
    QString type(void);
    QString titleHint(void);

public:
    QString inputLabelHint(int);
    QString outputLabelHint(int);

protected:
    bool read(const QString&);

private:
    dtkComposerNodePlotCurveFilePrivate *d;
};

#endif

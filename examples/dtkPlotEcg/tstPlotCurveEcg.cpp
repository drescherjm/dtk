/* tstPlotCurveEcg.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jun  7 16:33:55 2011 (+0200)
 * Version: $Id$
 * Last-Updated: jeu. nov.  8 18:30:33 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 41
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "tstPlotCurveEcg.h"

#include <dtkCore/dtkGlobal.h>

#ifdef _WIN32

#define SLEEP(x) Sleep(x)

#else

#include <unistd.h>
#define SLEEP(x) usleep(x*1000)

#endif

tstPlotCurveEcg::tstPlotCurveEcg(const QString& title) : dtkPlotCurve(title)
{

}

tstPlotCurveEcg::~tstPlotCurveEcg(void)
{

}

void tstPlotCurveEcg::read(const QString& file)
{
    QStringList contents = dtkReadFile(file).split("\n");

    QVector<QPointF> values;

    qreal start = 0.0;
    qreal step = 0.01;

    for(int i = 0; i < contents.count(); i++) {

        values << QPointF(start + i*step, contents.at(i).toDouble());

        this->setData(values);

        // The following mimics a real world computation

        emit updated(); qApp->processEvents();

        SLEEP(10);
    }
}

/* tstPlotCurveEcg.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jun  7 16:33:55 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Dec  6 11:51:24 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 43
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

        qApp->processEvents();

        SLEEP(10);
    }
}

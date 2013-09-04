/* tstPlotCurveEcg.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jun  7 16:33:55 2011 (+0200)
 * Version: $Id$
 * Last-Updated: mer. sept.  4 11:37:09 2013 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 51
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "tstPlotCurveEcg.h"

#include <dtkCore/dtkGlobal.h>

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

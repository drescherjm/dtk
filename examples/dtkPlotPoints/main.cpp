/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Nov 22 11:06:52 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Nov 25 10:35:35 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 69
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtCore>
#include <QtGui>

#include <dtkPlot/dtkPlotData.h>
#include <dtkPlot/dtkPlotInterpolatorLinear.h>
#include <dtkPlot/dtkPlotInterpolatorCubic.h>
#include <dtkPlot/dtkPlotPoint.h>
#include <dtkPlot/dtkPlotScene.h>
#include <dtkPlot/dtkPlotView.h>

int main(int argc, char **argv)
{
    QApplication application(argc, argv);

    dtkPlotData *data1 = new dtkPlotData;
      data1->setFillColor(Qt::green);
    (*data1) << new dtkPlotPoint(-1.0,  1.7);
    (*data1) << new dtkPlotPoint(-0.5, -0.1);
    (*data1) << new dtkPlotPoint( 0.0,  0.0);
    (*data1) << new dtkPlotPoint( 0.5,  1.0);
    (*data1) << new dtkPlotPoint( 1.0,  0.5);
    (*data1) << new dtkPlotPoint( 1.5,  0.3);
    (*data1) << new dtkPlotPoint( 2.0,  1.8);
    (*data1) << new dtkPlotPoint( 2.5,  1.4);
    (*data1) << new dtkPlotPoint( 3.0,  0.8);
    (*data1) << new dtkPlotPoint( 3.5,  0.2);
    (*data1) << new dtkPlotPoint( 4.0,  1.0);
    (*data1) << new dtkPlotPoint( 4.5, -0.4);

    dtkPlotData *data2 = new dtkPlotData;
    (*data2) << new dtkPlotPoint(-1.0,  0.3);
    (*data2) << new dtkPlotPoint(-0.5,  0.1);
    (*data2) << new dtkPlotPoint( 0.0,  1.4);
    (*data2) << new dtkPlotPoint( 0.5,  0.8);
    (*data2) << new dtkPlotPoint( 1.0,  0.7);
    (*data2) << new dtkPlotPoint( 1.5,  0.1);
    (*data2) << new dtkPlotPoint( 2.0, -0.3);
    (*data2) << new dtkPlotPoint( 2.5, -1.4);
    (*data2) << new dtkPlotPoint( 3.0, -0.8);
    (*data2) << new dtkPlotPoint( 3.5, -0.5);
    (*data2) << new dtkPlotPoint( 4.0,  0.3);
    (*data2) << new dtkPlotPoint( 4.5,  0.1);
    data2->setFillColor(Qt::blue);

    dtkPlotInterpolatorLinear linear_interpolator;
    dtkPlotInterpolatorCubic   cubic_interpolator;

    dtkPlotScene *scene = new dtkPlotScene;
    (*scene) << data1;
    (*scene) << cubic_interpolator.interpolate(data1);
    (*scene) << data2;
    (*scene) << linear_interpolator.interpolate(data2);

    dtkPlotView *view = new dtkPlotView;
    view->setScene(scene);
    view->setWindowTitle("dtkPlot example");
    view->show();

    int status = application.exec();

    delete scene;
    delete view;

    return status;
}

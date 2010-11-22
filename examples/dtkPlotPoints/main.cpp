/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Nov 22 11:06:52 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Nov 22 13:22:56 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 22
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtCore>
#include <QtGui>

#include <dtkPlot/dtkPlotPoint.h>
#include <dtkPlot/dtkPlotScene.h>
#include <dtkPlot/dtkPlotView.h>

int main(int argc, char **argv)
{
    QApplication application(argc, argv);

    dtkPlotScene *scene = new dtkPlotScene;
    (*scene) << new dtkPlotPoint(-1.0,  1.7);
    (*scene) << new dtkPlotPoint(-0.5, -0.1);
    (*scene) << new dtkPlotPoint( 0.5,  1.0);
    (*scene) << new dtkPlotPoint( 0.0,  0.0);
    (*scene) << new dtkPlotPoint( 0.5,  1.0);
    (*scene) << new dtkPlotPoint( 1.0,  0.5);
    (*scene) << new dtkPlotPoint( 1.5,  0.3);
    (*scene) << new dtkPlotPoint( 2.0,  1.8);
    (*scene) << new dtkPlotPoint( 2.5,  1.4);
    (*scene) << new dtkPlotPoint( 3.0,  0.8);
    (*scene) << new dtkPlotPoint( 3.5,  0.2);
    (*scene) << new dtkPlotPoint( 4.0,  1.0);

    dtkPlotView *view = new dtkPlotView;
    view->setScene(scene);
    view->setWindowTitle("dtkPlotPoints example");
    view->show();

    int status = application.exec();

    delete scene;
    delete view;

    return status;
}

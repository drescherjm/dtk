/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Feb 28 12:45:08 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Feb 28 14:34:11 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 20
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkGui/dtkFlowLayout.h>

#include <QtGui>

int main(int argc, char **argv)
{
    QApplication application(argc, argv);

    dtkFlowLayout *layout = new dtkFlowLayout;
    layout->addWidget(new QPushButton("Short"));
    layout->addWidget(new QPushButton("Longer"));
    layout->addWidget(new QPushButton("Different text"));
    layout->addWidget(new QPushButton("More text"));
    layout->addWidget(new QPushButton("Even longer button text"));

    QWidget *window = new QWidget;
    window->setLayout(layout);
    window->show();
    window->raise();

    int status = application.exec();

    delete window;

    return status;
}

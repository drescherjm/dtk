/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Dec  9 09:19:30 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Dec  9 09:28:49 2009 (+0100)
 *           By: Julien Wintz
 *     Update #: 4
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkGui/dtkCocoaController.h>
#include <dtkGui/dtkSearchBar.h>
#include <dtkGui/dtkSearchBox.h>

#include <QtGui>

int main(int argc, char **argv)
{
#ifdef Q_WS_MAC
    dtkCocoaController::instance()->initialize();
#endif

    QApplication application(argc, argv);

    QWidget *window = new QWidget;

    // Setting up view

    QDirModel *model = new QDirModel;

    QTreeView *tree = new QTreeView(window);
    tree->setModel(model);
    tree->setAnimated(false);
    tree->setIndentation(20);
    tree->setSortingEnabled(true);

    // Setting up search bar

    dtkSearchBar *search = new dtkSearchBar(window);
    search->addKey("name");
    search->addKey("size");
    search->addKey("kind");
    search->addKey("date");
    search->setDefaultKey("name");
    search->setModel(model);
    search->setView(tree);

    // Setting up layout

    QVBoxLayout *layout = new QVBoxLayout(window);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(search);
    layout->addWidget(tree);

    window->setWindowTitle("dtkSearchBar");
    window->resize(640, 480);
    window->show();
    
    int status = application.exec();

#ifdef Q_WS_MAC
    dtkCocoaController::instance()->uninitialize();
#endif

    return status;
}

// Version: $Id$
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:


#ifndef DTKSCREENMENU_H
#define DTKSCREENMENU_H

#include <QtGui>
#include <QtWidgets>

#include "dtkWidgetsExport.h"

class dtkScreenMenuPrivate;

class DTKWIDGETS_EXPORT dtkScreenMenu : public QMenu
{
    Q_OBJECT

public:
    dtkScreenMenu(const QString &title, QWidget *parent = 0);

public:
    QImage screenshot(QWidget *widget, qlonglong maxsize = 0);

public slots:
    void  takeScreenshot(void);

private:
    dtkScreenMenuPrivate *d;
};

#endif // DTKSCREENMENU_H

//
// dtkScreenMenu.h ends here

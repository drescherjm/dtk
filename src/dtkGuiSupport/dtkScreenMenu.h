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

#pragma once

#include <QtCore>
#include <QtGui>
#include <QtWidgets>

#include "dtkGuiSupportExport.h"

class dtkScreenMenuPrivate;

class DTKGUISUPPORT_EXPORT dtkScreenMenu : public QMenu
{
    Q_OBJECT

public:
    dtkScreenMenu(const QString& title, QWidget *parent = 0);

public:
    QImage screenshot(QWidget *widget, qlonglong maxsize = 0);

public slots:
    void  takeScreenshot(void);
    void startScreencast(void);
    void  stopScreencast(void);

protected slots:
    void addFrameToVideo(void);

private:
    dtkScreenMenuPrivate *d;
};

//
// dtkScreenMenu.h ends here

/* dtkScreenMenu.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2013 - Nicolas Niclausse, Inria.
 * Created: ven. oct. 18 14:45:04 2013 (+0200)
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKSCREENMENU_H
#define DTKSCREENMENU_H

#include <QMenu>
#include <QImage>

#include "dtkGuiSupportExport.h"

class dtkScreenMenuPrivate;

class DTKGUISUPPORT_EXPORT dtkScreenMenu : public QMenu
{
    Q_OBJECT

public:
    dtkScreenMenu(const QString &title, QWidget *parent = 0);

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

#endif // DTKSCREENMENU_H

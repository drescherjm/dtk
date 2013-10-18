/* dtkScreenshotMenu.h ---
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

#ifndef DTKSCREENSHOTMENU_H
#define DTKSCREENSHOTMENU_H

#include <QMenu>
#include <QImage>

#include "dtkGuiExport.h"

class dtkScreenshotMenuPrivate;

class DTKGUI_EXPORT dtkScreenshotMenu : public QMenu
{
    Q_OBJECT

public:
    dtkScreenshotMenu(const QString &title, QWidget *parent = 0);

public:
    QImage screenshot(QWidget *widget, qlonglong maxsize = 0);

public slots:
    void  takeScreenshot(void);
    void startScreencast(void);
    void  stopScreencast(void);
    void addFrameToVideo(void);

private:
    dtkScreenshotMenuPrivate *d;

};

#endif // DTKSCREENSHOTMENU_H

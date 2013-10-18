/* dtkScreenshotsMenu.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Jun  8 13:45:35 2010 (+0200)
 * Version: $Id$
 * Last-Updated: ven. oct. 18 18:42:21 2013 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 269
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkConfig.h>

#include "dtkScreenshotMenu.h"

#if defined(DTK_BUILD_VIDEO) && defined(DTK_HAVE_FFMPEG)
#include <dtkVideo/dtkVideoEncoder.h>
#endif

#include <QApplication>
#include <QDesktopWidget>
#include <QtCore>

// #include <QSettings>
// #include <QFileInfo>

class dtkScreenshotMenuPrivate
{
public:
    int      fps;
    int  bitrate;
    int    width;
    int    height;

public:
    QTimer timer;

#if defined(DTK_BUILD_VIDEO) && defined(DTK_HAVE_FFMPEG)
public:
    dtkVideoEncoder * encoder;
#endif

};

dtkScreenshotMenu::dtkScreenshotMenu(const QString &title, QWidget *parent) : QMenu(title, parent), d(new dtkScreenshotMenuPrivate)
{
    d->encoder = NULL;
    d->fps     = 15;
    d->bitrate = 4000000;
    QAction* screenshot       = addAction(QString("Take screenshot"));
    screenshot->setVisible(true);
    connect(screenshot, SIGNAL(triggered(bool)), this, SLOT(takeScreenshot(void)));

    addSeparator();
    QAction* screencast_start = addAction(QString("Start screencast"));
    connect(screencast_start, SIGNAL(triggered(bool)), this, SLOT(startScreencast(void)));
    QAction* screencast_stop  = addAction(QString("Stop screencast"));
    connect(screencast_stop, SIGNAL(triggered(bool)), this, SLOT(stopScreencast(void)));

#if !defined(DTK_BUILD_VIDEO) || !defined(DTK_HAVE_FFMPEG)
    screencast_start->setEnabled(false);
    screencast_stop->setEnabled(false);
#endif

}

void dtkScreenshotMenu::startScreencast(void)
{
#if defined(DTK_BUILD_VIDEO) && defined(DTK_HAVE_FFMPEG)
    if (!d->encoder) {
        d->encoder = new dtkVideoEncoder;
    }

    // TODO: open dialog box to configure filename, fps and bitrate.

    if (QWidget * widget = dynamic_cast<QWidget *>(parent())) {
        int gop = 20;
        int FULLHD = 1920;

        d->width  = widget->width();
        d->height = widget->height();
        if (widget->width() > FULLHD) { // max  = FULL HD resolution
            d->width  = FULLHD;
            d->height = widget->height() *  FULLHD / widget->width() ;
        }
        qDebug() << "create video, resolution:"<< d->width << d->height;

        d->encoder->createFile("screencast.avi", d->width,d->height,d->bitrate,gop,d->fps);
    }
    d->timer.connect(&(d->timer), SIGNAL(timeout()),this, SLOT(addFrameToVideo()));
    int interval = 1000 / d->fps;
    qDebug() << "start timer every" << interval << "ms";
    d->timer.start(interval);
#else
    qDebug() << "dtkVideo support not available";
#endif
}

void dtkScreenshotMenu::stopScreencast(void)
{
#if defined(DTK_BUILD_VIDEO) && defined(DTK_HAVE_FFMPEG)
     d->encoder->close();
     d->timer.stop();
#endif
}

void dtkScreenshotMenu::addFrameToVideo(void)
{
#if defined(DTK_BUILD_VIDEO) && defined(DTK_HAVE_FFMPEG)
    if (QWidget * widget = dynamic_cast<QWidget *>(parent())) {
        d->encoder->encodeImage(screenshot(widget, d->width));
    }
#endif
}

QImage dtkScreenshotMenu::screenshot(QWidget *widget, qlonglong maxsize)
{
    QPixmap pixmap(widget->size());
    widget->render(&pixmap);
    if( maxsize > 0 && pixmap.width() > maxsize) {
         return pixmap.scaledToWidth(maxsize).toImage();
    }
    return pixmap.toImage();
}

void dtkScreenshotMenu::takeScreenshot(void)
{
    qDebug() << "take screenshot";
    if (QWidget * widget = dynamic_cast<QWidget *>(parent())) {
        QImage image = screenshot(widget);
        //TODO: open dialog to set image filename
        image.save("screenshot.png", "PNG");
    }
}

/* dtkScreensMenu.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Jun  8 13:45:35 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Oct 21 15:12:08 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 363
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include <dtkConfig.h>

#include "dtkScreenMenu.h"

#if defined(DTK_BUILD_VIDEO) && defined(DTK_HAVE_FFMPEG)
#include <dtkVideo/dtkVideoEncoder.h>
#endif

#include <QtGui>
#include <QtCore>

class dtkScreenMenuPrivate
{
public:
    int  fps;
    int  bitrate;
    int  width;
    int  height;

public:
    QTimer timer;

#if defined(DTK_BUILD_VIDEO) && defined(DTK_HAVE_FFMPEG)
public:
    dtkVideoEncoder * encoder;
#endif
};

dtkScreenMenu::dtkScreenMenu(const QString &title, QWidget *parent) : QMenu(title, parent), d(new dtkScreenMenuPrivate)
{
#if defined(DTK_BUILD_VIDEO) && defined(DTK_HAVE_FFMPEG)
    d->encoder = NULL;
#endif
    d->fps = 15;
    d->bitrate = 4000000;

    QAction* screenshot = this->addAction(QString("Take screenshot")); screenshot->setVisible(true);
    this->addSeparator();
    QAction* screencast_start = this->addAction(QString("Start screencast"));
    QAction* screencast_stop  = this->addAction(QString("Stop screencast"));

#if !defined(DTK_BUILD_VIDEO) || !defined(DTK_HAVE_FFMPEG)
    screencast_start->setEnabled(false);
    screencast_stop->setEnabled(false);
#else
    connect(screencast_start, SIGNAL(triggered(bool)), this, SLOT(startScreencast(void)));
    connect(screencast_stop, SIGNAL(triggered(bool)), this, SLOT(stopScreencast(void)));
#endif
    connect(screenshot, SIGNAL(triggered(bool)), this, SLOT(takeScreenshot(void)));
}

void dtkScreenMenu::startScreencast(void)
{
#if defined(DTK_BUILD_VIDEO) && defined(DTK_HAVE_FFMPEG)
    if(!d->encoder)
        d->encoder = new dtkVideoEncoder;

    QString path = QDir::homePath();
    QString name = QString("%1 - Screencast - %2").arg(qApp->applicationName()).arg(QDateTime::currentDateTime().toString());
    QString file = QDir::home().filePath(name);
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save screencast"), file, tr("Screencast (*.avi *.mpg *.mp4 *.mov *.ogv)"));

    if (QWidget * widget = dynamic_cast<QWidget *>(parent())) {

        int gop = 20;
        int FULLHD = 1920;

        d->width  = widget->width();
        d->height = widget->height();

        if (widget->width() > FULLHD) {
            d->width  = FULLHD;
            d->height = widget->height() *  FULLHD / widget->width() ;
        }

        d->encoder->createFile(fileName, d->width, d->height, d->bitrate, gop, d->fps);
    }

    d->timer.connect(&(d->timer), SIGNAL(timeout()), this, SLOT(addFrameToVideo()));

    int interval = 1000/d->fps;

    d->timer.start(interval);
#endif
}

void dtkScreenMenu::stopScreencast(void)
{
#if defined(DTK_BUILD_VIDEO) && defined(DTK_HAVE_FFMPEG)
     d->encoder->close();
     d->timer.stop();
#endif
}

void dtkScreenMenu::addFrameToVideo(void)
{
#if defined(DTK_BUILD_VIDEO) && defined(DTK_HAVE_FFMPEG)
    if (QWidget * widget = dynamic_cast<QWidget *>(parent())) {
        d->encoder->encodeImage(screenshot(widget, d->width));
    }
#endif
}

QImage dtkScreenMenu::screenshot(QWidget *widget, qlonglong maxsize)
{
    QPixmap pixmap(widget->size());
    widget->render(&pixmap);
    if( maxsize > 0 && pixmap.width() > maxsize) {
         return pixmap.scaledToWidth(maxsize).toImage();
    }
    return pixmap.toImage();
}

void dtkScreenMenu::takeScreenshot(void)
{
    if (QWidget * widget = dynamic_cast<QWidget *>(parent())) {

        QString path = QDir::homePath();
        QString name = QString("%1 - Screenshot - %2").arg(qApp->applicationName()).arg(QDateTime::currentDateTime().toString());
        QString file = QDir::home().filePath(name);
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save screenshot"), file, tr("Screenshot (*.png)"));

        QImage image = screenshot(widget);
        image.save(fileName, "PNG");
    }
}

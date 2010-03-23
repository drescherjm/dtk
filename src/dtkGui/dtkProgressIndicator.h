/* dtkProgressIndicator.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Mar 22 10:18:05 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Mar 22 10:20:42 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 7
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKPROGRESSINDICATOR_H
#define DTKPROGRESSINDICATOR_H

#include "dtkGuiExport.h"

#include <QtGui/QWidget>
#include <QtGui/QColor>

class dtkProgressIndicatorPrivate;

class dtkProgressIndicator : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int delay READ animationDelay WRITE setAnimationDelay)
    Q_PROPERTY(bool displayedWhenStopped READ isDisplayedWhenStopped WRITE setDisplayedWhenStopped)
    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    dtkProgressIndicator(QWidget* parent = 0);

    int animationDelay(void) const;

    bool isAnimated(void) const;
    bool isDisplayedWhenStopped(void) const;

    const QColor& color(void) const;

    QSize sizeHint(void) const;

    int heightForWidth(int w) const;

public slots:
    void startAnimation(void);
    void stopAnimation(void);

    void setAnimationDelay(int delay);
    void setDisplayedWhenStopped(bool state);
    void setColor(const QColor& color);

protected:
    virtual void timerEvent(QTimerEvent *event); 
    virtual void paintEvent(QPaintEvent *event);

private:
    dtkProgressIndicatorPrivate *d;
};

#endif

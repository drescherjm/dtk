/* dtkNotificationDisplay.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Apr 20 21:07:54 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Apr 23 12:01:27 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 58
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkNotification.h"
#include "dtkNotificationDisplay.h"
#include "dtkNotificationEvent.h"
#include "dtkNotificationStack.h"

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

class dtkNotificationDisplayPrivate
{
public:
    QString read(const QString& path);

public:
    dtkNotificationStack *stack;
};

QString dtkNotificationDisplayPrivate::read(const QString& path)
{
    QFile file(path);

    if(!file.open(QFile::ReadOnly))
        qDebug() << "Unable to read file" << path;

    QString contents = file.readAll();

    file.close();

    return contents;
}

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

dtkNotificationDisplay::dtkNotificationDisplay(QWidget *parent) : QLabel(parent), d(new dtkNotificationDisplayPrivate)
{
    d->stack = new dtkNotificationStack(this);
    d->stack->registerNotifiable(this);

    this->setFixedHeight(46);
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    this->setStyleSheet(d->read(":dtkNotification/dtkNotificationDisplay.qss"));
}

dtkNotificationDisplay::~dtkNotificationDisplay(void)
{
    delete d;

    d = NULL;
}

void dtkNotificationDisplay::clear(void)
{
    QLabel::clear();
}

void dtkNotificationDisplay::display(const QString& message)
{
    QLabel::setText(message);
}

QSize dtkNotificationDisplay::sizeHint(void) const
{
    return QSize(350, 46);
}

bool dtkNotificationDisplay::event(QEvent *event)
{
    if(event->type() != dtkNotificationEventType)
        return QLabel::event(event);

    d->stack->push(static_cast<dtkNotificationEvent *>(event));

    return true;
}

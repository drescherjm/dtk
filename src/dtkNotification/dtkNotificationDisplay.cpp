/* dtkNotificationDisplay.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Apr 20 21:07:54 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Apr 23 13:52:43 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 103
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

public:
    QLabel *label;

public:
    QToolButton *next;
    QToolButton *prev;
    QToolButton *clse;
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

dtkNotificationDisplay::dtkNotificationDisplay(QWidget *parent) : QFrame(parent), d(new dtkNotificationDisplayPrivate)
{
    d->stack = new dtkNotificationStack(this);
    d->stack->registerNotifiable(this);

    d->label = new QLabel(this);

    d->next = new QToolButton(this);
    d->next->setObjectName("dtkNotifiable-next");

    d->prev = new QToolButton(this);
    d->prev->setObjectName("dtkNotifiable-prev");

    d->clse = new QToolButton(this);
    d->clse->setObjectName("dtkNotifiable-clse");
    
    QVBoxLayout *v_layout = new QVBoxLayout;
    v_layout->setContentsMargins(0, 0, 0, 0);
    v_layout->setSpacing(0);
    v_layout->addWidget(d->next);
    v_layout->addWidget(d->prev);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(10);
    layout->addLayout(v_layout);
    layout->addWidget(d->label);
    layout->addWidget(d->clse);

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
    // QPropertyAnimation *animation = new QPropertyAnimation(d->label, "windowOpacity");
    // animation->setDuration(250);
    // animation->setStartValue(1.0);
    // animation->setEndValue(0.0);
    // animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void dtkNotificationDisplay::display(const QString& message)
{
    d->label->setText(message);
}

QSize dtkNotificationDisplay::sizeHint(void) const
{
    return QSize(350, 46);
}

bool dtkNotificationDisplay::event(QEvent *event)
{
    if(event->type() != dtkNotificationEventType)
        return QFrame::event(event);

    d->stack->push(static_cast<dtkNotificationEvent *>(event));

    return true;
}

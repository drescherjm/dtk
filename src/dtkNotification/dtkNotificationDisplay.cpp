/* dtkNotificationDisplay.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Apr 20 21:07:54 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Apr 23 22:23:07 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 147
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
    QLabel *message;
    QLabel *persistent_count;
    QLabel *non_persistent_count;

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
    dtkNotificationStack::instance()->registerNotifiable(this);

    d->message = new QLabel(this);

    d->persistent_count = new QLabel(QString::number(0), this);
    d->persistent_count->setObjectName("dtkNotificationDisplayCount");
    d->persistent_count->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    d->non_persistent_count = new QLabel(QString::number(0), this);
    d->non_persistent_count->setObjectName("dtkNotificationDisplayCount");
    d->non_persistent_count->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    d->next = new QToolButton(this);
    d->next->setObjectName("dtkNotifiable-next");

    d->prev = new QToolButton(this);
    d->prev->setObjectName("dtkNotifiable-prev");

    d->clse = new QToolButton(this);
    d->clse->setObjectName("dtkNotifiable-clse");
    d->clse->setVisible(false);
    
    QVBoxLayout *v_layout = new QVBoxLayout;
    v_layout->setContentsMargins(0, 0, 0, 0);
    v_layout->setSpacing(0);
    v_layout->addWidget(d->next);
    v_layout->addWidget(d->prev);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(10);
    layout->addWidget(d->persistent_count);
    layout->addLayout(v_layout);
    layout->addWidget(d->message);
    layout->addWidget(d->clse);
    layout->addWidget(d->non_persistent_count);

    this->setFixedHeight(46);
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    this->setStyleSheet(d->read(":dtkNotification/dtkNotificationDisplay.qss"));

    connect(d->clse, SIGNAL(released()), this, SLOT(dismiss()));
}

dtkNotificationDisplay::~dtkNotificationDisplay(void)
{
    delete d;

    d = NULL;
}

void dtkNotificationDisplay::clear(void)
{
    // QPropertyAnimation *animation = new QPropertyAnimation(d->message, "windowOpacity");
    // animation->setDuration(250);
    // animation->setStartValue(1.0);
    // animation->setEndValue(0.0);
    // animation->start(QAbstractAnimation::DeleteWhenStopped);

    d->message->clear();
}

void dtkNotificationDisplay::dismiss(void)
{
    dtkNotificationStack::instance()->dismiss();
}

void dtkNotificationDisplay::dismissible(bool dismissible)
{
    d->clse->setVisible(dismissible);
}

void dtkNotificationDisplay::display(const QString& message)
{
    d->message->setText(message);
}

void dtkNotificationDisplay::setPersistentCount(int count)
{
    d->persistent_count->setText(QString::number(count));

    this->update();
}

void dtkNotificationDisplay::setNonPersistentCount(int count)
{
    d->non_persistent_count->setText(QString::number(count));

    this->update();
}

QSize dtkNotificationDisplay::sizeHint(void) const
{
    return QSize(350, 46);
}

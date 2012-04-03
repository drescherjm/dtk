/* dtkSwitch.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Feb 29 23:54:03 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Mar 20 14:13:00 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 55
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkSwitch.h"

class dtkSwitchPrivate
{
public:
    void update(void);

public:
    QDeclarativeItem *root_item;
    QDeclarativeContext *root_context;

public:
    QString foreground;
    QString background;

public:
    QString l_label;
    QString r_label;

public:
    dtkSwitch *q;
};

void dtkSwitchPrivate::update(void)
{
    this->root_context->setContextProperty("wrapper", q);
}

dtkSwitch::dtkSwitch(QWidget *parent) : QDeclarativeView(parent), d(new dtkSwitchPrivate)
{
    d->q = this;

    d->foreground = "pixmaps/dtkSwitch-knob.png";
    d->background = "pixmaps/dtkSwitch-groove.png";

    d->l_label = "";
    d->r_label = "";

    d->root_context = this->rootContext();
    d->update();

    this->setSource(QUrl("qrc:dtkGui/dtkSwitch.qml"));
    this->setStyleSheet("background: transparent;");
    this->setResizeMode(QDeclarativeView::SizeViewToRootObject);

    d->root_item = qobject_cast<QDeclarativeItem *>(this->rootObject());

    QMetaObject::invokeMethod(d->root_item, "init");

    connect(d->root_item, SIGNAL(toggled(bool)), this, SIGNAL(toggled(bool)));
}

dtkSwitch::~dtkSwitch(void)
{
    delete d;

    d = NULL;
}

QString dtkSwitch::foreground(void)
{
    return d->foreground;
}

QString dtkSwitch::background(void)
{
    return d->background;
}

QString dtkSwitch::leftLabel(void)
{
    return d->l_label;
}

QString dtkSwitch::rightLabel(void)
{
    return d->r_label;
}

void dtkSwitch::toggle(void)
{
    QMetaObject::invokeMethod(d->root_item, "toggle");
}

void dtkSwitch::setForeground(const QString& pixmap)
{
    d->foreground = pixmap;
    d->update();
}

void dtkSwitch::setBackground(const QString& pixmap)
{
    d->background = pixmap;
    d->update();
}

void dtkSwitch::setLeftLabel(const QString& label)
{
    d->l_label = label;
    d->update();
}

void dtkSwitch::setRightLabel(const QString& label)
{
    d->r_label = label;
    d->update();
}

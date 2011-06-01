/* dtkInspector.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Jan 31 11:09:59 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Wed May 25 16:35:54 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 124
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkInspector.h"
#include "dtkInspectorTitleBar.h"
#include "dtkInspectorToolBar.h"

#include <dtkCore/dtkGlobal.h>

#include <QtGui>

class dtkInspectorPrivate
{
public:
    dtkInspectorTitleBar *title_bar;
    dtkInspectorToolBar *tool_bar;

public:
    QPoint drag_point;

    QHash<QAction *, QWidget *> pages;

    QStackedWidget *stack;
};

dtkInspector::dtkInspector(QWidget *parent) : QDialog(parent), d(new dtkInspectorPrivate)
{
    d->title_bar = new dtkInspectorTitleBar(this);
    d->title_bar->setTitle("Inspector");

    d->tool_bar = new dtkInspectorToolBar(this);
    d->tool_bar->hide();

    d->stack = new QStackedWidget(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(d->title_bar);
    layout->addWidget(d->stack);
    layout->addWidget(d->tool_bar);

#if defined(Q_WS_MAC)
    this->setAttribute(Qt::WA_TranslucentBackground);
#endif
    this->setStyleSheet(dtkReadFile(":dtkGui/dtkInspector.qss"));
    this->setWindowFlags(Qt::Tool | Qt::CustomizeWindowHint | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setWindowOpacity(0.95);

    connect(d->title_bar, SIGNAL(closed()), this, SLOT(close()));
    connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(close()));
}

dtkInspector::~dtkInspector(void)
{
    delete d;

    d = NULL;
}

QAction *dtkInspector::addPage(const QString& title, QWidget *page)
{
    QAction *action = new QAction(title, this);
    action->setIcon(QIcon(":icons/widget.tiff"));
    action->setToolTip(QString("Switch to %1 inspector page.").arg(title));

    d->pages.insert(action, page);
    d->stack->addWidget(page);
    d->tool_bar->addAction(action);

    connect(action, SIGNAL(triggered()), this, SLOT(onActionTriggered()));

    if (d->stack->count() == 1)
        action->trigger();

    if (d->stack->count() > 1)
        d->tool_bar->show();

    return action;
}

QAction *dtkInspector::addPage(const QString& title, QWidget *page, const QIcon& icon)
{
    QAction *action = new QAction(title, this);
    action->setIcon(icon);
    action->setToolTip(QString("Switch to %1 inspector page.").arg(title));
    action->setEnabled(d->stack->count());

    d->pages.insert(action, page);
    d->stack->addWidget(page);
    d->tool_bar->addAction(action);

    connect(action, SIGNAL(triggered()), this, SLOT(onActionTriggered()));

    if (d->stack->count() == 1)
        action->trigger();

    return action;
}

void dtkInspector::setToolBarVisible(bool visible)
{
    d->tool_bar->setVisible(visible);
}

void dtkInspector::setTitle(const QString& title)
{
    d->title_bar->setTitle(title);
}

void dtkInspector::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    
    emit visibilityChanged(false);
}

void dtkInspector::mouseMoveEvent(QMouseEvent *event)
{
    if (!d->drag_point.isNull()) {
        
        QPoint dest = QPoint(event->globalPos() - d->drag_point);
        
#if defined(Q_WS_MAC)
        if (dest.y() <= 22)
            dest.setY(22);
#endif
        
        this->move(dest);
        
        event->accept();
    }

    QDialog::mouseMoveEvent(event);
}

void dtkInspector::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        d->drag_point = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }

    QDialog::mousePressEvent(event);
}

void dtkInspector::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        d->drag_point = QPoint(0, 0);
    }

    QDialog::mouseReleaseEvent(event);
}

void dtkInspector::resizeEvent(QResizeEvent *event)
{
    QPainterPath r_path;
    r_path.addRoundedRect(QRectF(this->rect()), 5, 5, Qt::AbsoluteSize);
        
    this->setMask(QRegion(r_path.toFillPolygon().toPolygon()));
}

void dtkInspector::onActionTriggered(void)
{
    QAction *sender = qobject_cast<QAction *>(this->sender());

    foreach(QAction *action, d->pages.keys())
        action == sender ? action->setEnabled(false) : action->setEnabled(true);

    d->stack->setCurrentWidget(d->pages.value(sender));

    this->setWindowTitle("Inspector - " + sender->text());
}

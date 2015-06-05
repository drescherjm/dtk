// Version: $Id$
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

#include "dtkWidgetsViewManager.h"
#include "dtkWidgetsViewList.h"
#include "dtkWidgetsViewLayout.h"
#include "dtkWidgetsViewListControl.h"

#include <QtWidgets>

class dtkWidgetsViewManagerPrivate
{
public:
    dtkWidgetsViewList *view_list;
    dtkWidgetsViewLayout *view_layout;
    QStackedWidget *view_inspector;
};

dtkWidgetsViewManager::dtkWidgetsViewManager(QWidget *parent) : QFrame(parent), d(new dtkWidgetsViewManagerPrivate)
{
    d->view_list = new dtkWidgetsViewList;
    d->view_layout = new dtkWidgetsViewLayout;
    d->view_inspector = new QStackedWidget;

    dtkWidgetsViewListControl *view_control = new dtkWidgetsViewListControl(this);
    view_control->setLayout(d->view_layout);
    view_control->setList(d->view_list);

    QFrame *frame = new QFrame;
    frame->setAutoFillBackground(true);
    frame->setFixedWidth(300);

    QVBoxLayout *layout = new QVBoxLayout(frame);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(view_control);
    layout->addWidget(d->view_list);
    layout->addWidget(d->view_inspector);

    QHBoxLayout *main_layout = new QHBoxLayout(this);
    main_layout->setContentsMargins(0, 0, 0, 0);
    main_layout->setSpacing(0);
    main_layout->addWidget(frame);
    main_layout->addWidget(d->view_layout);

    // Behaviour

    connect(d->view_layout, SIGNAL(focused(QWidget *)), this, SIGNAL(focused(QWidget *)));
    connect(d->view_layout, SIGNAL(unfocused(QWidget *)), this, SLOT(hideCurrentWidget()));
}

dtkWidgetsViewManager::~dtkWidgetsViewManager(void)
{
    delete d;

    d = NULL;
}

void dtkWidgetsViewManager::clear(void)
{
    this->hideCurrentWidget();
    d->view_list->clear();
    d->view_layout->clear();
}

void dtkWidgetsViewManager::addWidget(QWidget *widget)
{
    d->view_inspector->addWidget(widget);
    widget->setVisible(false);
}

void dtkWidgetsViewManager::setCurrentWidget(QWidget *widget)
{
    widget->setVisible(true);
    d->view_inspector->setCurrentWidget(widget);
}

void dtkWidgetsViewManager::hideCurrentWidget(void)
{
    QWidget *widget = d->view_inspector->currentWidget();
    if (widget)
        widget->setVisible(false);
}

//
// dtkWidgetsViewManager.cpp ends here

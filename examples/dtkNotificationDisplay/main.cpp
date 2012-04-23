/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Apr 20 21:18:43 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Apr 24 01:10:31 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 101
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtCore>
#include <QtGui>

#include <dtkNotification/dtkNotification.h>
#include <dtkNotification/dtkNotificationDisplay.h>
#include <dtkNotification/dtkNotificationEvent.h>
#include <dtkNotification/dtkNotificationQueue.h>

// /////////////////////////////////////////////////////////////////
// tstMainWindow
// /////////////////////////////////////////////////////////////////

class tstMainWindow : public QMainWindow
{
    Q_OBJECT

public:
     tstMainWindow(QWidget *parent = 0);
    ~tstMainWindow(void);

protected slots:
    void onClear(void);
    void onPersistentNotification(void);
    void onNonPersistentNotification(void);

private:
    dtkNotificationDisplay *display;

private:
    QTextEdit *edit;
    QSpinBox *spin;
    QPushButton *p_button;
    QPushButton *n_button;
    QPushButton *c_button;
};

tstMainWindow::tstMainWindow(QWidget *parent) : QMainWindow(parent)
{
    this->display = new dtkNotificationDisplay(this);
    this->display->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    
    this->addToolBar(tr("Main"))->addWidget(this->display);
    
    this->edit = new QTextEdit(this);
    this->edit->setPlainText("Type your message here");
    
    this->spin = new QSpinBox(this);
    this->spin->setMinimum(250);
    this->spin->setMaximum(10000);
    this->spin->setValue(1000);
    this->spin->setSingleStep(250);

    this->p_button = new QPushButton("Persistent", this);
    this->n_button = new QPushButton("Non Persistent", this);
    this->c_button = new QPushButton("Clear", this);

    QHBoxLayout *b_layout = new QHBoxLayout;
    b_layout->addWidget(this->p_button);
    b_layout->addWidget(this->n_button);
    b_layout->addWidget(this->c_button);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(this->edit);
    layout->addWidget(this->spin);
    layout->addLayout(b_layout);

    QWidget *central = new QWidget(this);
    central->setLayout(layout);

    this->setCentralWidget(central);
    this->setUnifiedTitleAndToolBarOnMac(true);
    this->setWindowTitle("dtk notification example");

    connect(this->p_button, SIGNAL(clicked()), this, SLOT(onPersistentNotification()));
    connect(this->n_button, SIGNAL(clicked()), this, SLOT(onNonPersistentNotification()));
    connect(this->c_button, SIGNAL(clicked()), this, SLOT(onClear()));
}

tstMainWindow::~tstMainWindow(void)
{
    
}

void tstMainWindow::onClear(void)
{
    dtkNotificationQueue::instance()->clear();
}

void tstMainWindow::onPersistentNotification(void)
{
    dtkNotificationEvent *event = new dtkNotificationEvent;
    event->setMessage(this->edit->toPlainText());
    event->setType(dtkNotificationEvent::Persistent);

    dtkNotify(event);
}

void tstMainWindow::onNonPersistentNotification(void)
{
    dtkNotify(this->edit->toPlainText(), this->spin->value());
}

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
    QApplication application(argc, argv);

    tstMainWindow *window = new tstMainWindow;
    window->show();
    window->raise();

    int status = application.exec();

    delete window;

    return status;
}

#include "main.moc"

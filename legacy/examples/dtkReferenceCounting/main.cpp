/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Apr 16 09:27:23 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Apr  4 08:57:10 2012 (+0200)
 *           By: tkloczko
 *     Update #: 246
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtCore/QObject>

#include <dtkCore/dtkAbstractObject.h>
#include <dtkCore/dtkGlobal.h>

#include <dtkLog/dtkLog.h>

#include <dtkGui/dtkAboutBox.h>

// /////////////////////////////////////////////////////////////////
// dtkConcreteObjectWatcher
// /////////////////////////////////////////////////////////////////

class dtkConcreteObjectWatcher : public QObject
{
    Q_OBJECT

public:
    static dtkConcreteObjectWatcher *instance(void);

public slots:
    void destroyed(QObject *object);

protected:
    static dtkConcreteObjectWatcher *s_instance;

private:
     dtkConcreteObjectWatcher(void);
    ~dtkConcreteObjectWatcher(void);
};

dtkConcreteObjectWatcher *dtkConcreteObjectWatcher::instance(void)
{
    if(!s_instance)
        s_instance = new dtkConcreteObjectWatcher;

    return s_instance;
}

void dtkConcreteObjectWatcher::destroyed(QObject *object)
{
    QMessageBox::information(0, "dtkConcreteObjectWatcher", "Object suicided");

    object = NULL;
}

dtkConcreteObjectWatcher::dtkConcreteObjectWatcher(void)
{
    
}

dtkConcreteObjectWatcher::~dtkConcreteObjectWatcher(void)
{
    
}

dtkConcreteObjectWatcher *dtkConcreteObjectWatcher::s_instance = NULL;

// /////////////////////////////////////////////////////////////////
// dtkConcreteObject1
// /////////////////////////////////////////////////////////////////

class dtkConcreteObject1 : public dtkAbstractObject
{
public:
     dtkConcreteObject1(void);
    ~dtkConcreteObject1(void);
};

dtkConcreteObject1::dtkConcreteObject1(void) : dtkAbstractObject()
{
    dtkDebug() << "Creating concrete object 1";

    connect(this, SIGNAL(destroyed(QObject *)), dtkConcreteObjectWatcher::instance(), SLOT(destroyed(QObject *)));
}

dtkConcreteObject1::~dtkConcreteObject1(void)
{
    dtkDebug() << "Destroying concrete object 1";
}

// /////////////////////////////////////////////////////////////////
// dtkConcreteObject2
// /////////////////////////////////////////////////////////////////

class dtkConcreteObject2 : public dtkAbstractObject
{
public:
     dtkConcreteObject2(void);
    ~dtkConcreteObject2(void);
};

dtkConcreteObject2::dtkConcreteObject2(void) : dtkAbstractObject()
{
    dtkDebug() << "Creating concrete object 2";

    connect(this, SIGNAL(destroyed(QObject *)), dtkConcreteObjectWatcher::instance(), SLOT(destroyed(QObject *)));
}

dtkConcreteObject2::~dtkConcreteObject2(void)
{
    dtkDebug() << "Destroying concrete object 2";
}

// /////////////////////////////////////////////////////////////////
// dtkConcreteObjectItem
// /////////////////////////////////////////////////////////////////

class dtkConcreteObjectItem : public QListWidgetItem
{
public:
    dtkConcreteObjectItem(QString label, dtkAbstractObject *object) : QListWidgetItem(label)
    {
        m_object = object;
    }

    dtkAbstractObject *object(void)
    {
        return m_object;
    }

private:
    dtkAbstractObject *m_object;
};

// /////////////////////////////////////////////////////////////////
// dtkConcreteObjectWindow
// /////////////////////////////////////////////////////////////////

class dtkConcreteObjectWindowPrivate;

class dtkConcreteObjectWindow : public QMainWindow
{
    Q_OBJECT

public:
     dtkConcreteObjectWindow(QWidget *parent = 0);
    ~dtkConcreteObjectWindow(void);    

public slots:
    void create(void);
    void retain(void);
    void release(void);

private:
    dtkConcreteObjectWindowPrivate *d;
};

class dtkConcreteObjectWindowPrivate
{
public:
    QListWidget *list;

    QPushButton *createButton;
    QPushButton *retainButton;
    QPushButton *releaseButton;
};

dtkConcreteObjectWindow::dtkConcreteObjectWindow(QWidget *parent) : QMainWindow(parent), d(new dtkConcreteObjectWindowPrivate)
{
    QWidget *central = new QWidget(this);

    d->list = new QListWidget(central);

    QWidget *side = new QWidget(central);
    
    d->createButton = new QPushButton("Create", side);
    d->retainButton = new QPushButton("Retain", side);
    d->releaseButton = new QPushButton("Release", side);

    connect(d->createButton, SIGNAL(clicked()), this, SLOT(create()));
    connect(d->retainButton, SIGNAL(clicked()), this, SLOT(retain()));
    connect(d->releaseButton, SIGNAL(clicked()), this, SLOT(release()));

    QVBoxLayout *sideLayout = new QVBoxLayout(side);
    sideLayout->addWidget(d->createButton);
    sideLayout->addWidget(d->retainButton);
    sideLayout->addWidget(d->releaseButton);
    sideLayout->addStretch(1);

    QHBoxLayout *layout = new QHBoxLayout(central);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(d->list);
    layout->addWidget(side);

    this->setCentralWidget(central);
}

dtkConcreteObjectWindow::~dtkConcreteObjectWindow(void)
{
    delete d;

    d = NULL;
}

void dtkConcreteObjectWindow::create(void)
{
    static int type = 0;

    if(type)
        d->list->addItem(new dtkConcreteObjectItem("Object 1 - +", new dtkConcreteObject1));
    else
        d->list->addItem(new dtkConcreteObjectItem("Object 2 - +", new dtkConcreteObject2));

    type = !type;
}

void dtkConcreteObjectWindow::retain(void)
{
    dtkConcreteObjectItem *item = dynamic_cast<dtkConcreteObjectItem *>(d->list->currentItem());

    if(!item)
        return;

    dtkAbstractObject *object = item->object();

    if (object)
        object->retain();

    QString text = QString(item->text()); text += "+";

    item->setText(text);
}

void dtkConcreteObjectWindow::release(void)
{
    dtkConcreteObjectItem *item = dynamic_cast<dtkConcreteObjectItem *>(d->list->currentItem());

    if(!item)
        return;

    dtkAbstractObject *object = item->object();

    if (object->release() == 0)
        d->list->takeItem(d->list->currentRow());
    else {
        QString text = QString(item->text()); text.chop(1);

        item->setText(text);
    }
}

// /////////////////////////////////////////////////////////////////
// main
// /////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
    QApplication application(argc, argv);

    dtkConcreteObjectWindow *window = new dtkConcreteObjectWindow;
    window->setWindowTitle("dtkReferenceCounting");
    window->show();

    dtkAboutBox *about = new dtkAboutBox(window);
    about->setText("dtk Reference Counting Example");
    about->setInformativeText(
        "This example demonstrates the use "
        "of the retain/release cycle of "
        "dtkAbstractObjects and derivative classes, "
        "among which, dtkAbstractData, dtkAbstractProcess "
        "and dtkAbstractView. An example of an object watcher is "
        "implemented to track objects for self deletion. <br><br>"
        "Click <b>create</b> button to instanciate a dtkAbstractObject subclass. "
        "Use then the <b>retain</b> and <b>release</b> buttons to act on "
        "the reference count of the object instance highlighted in the list view.");
    about->setDefaultButton(QMessageBox::Ok);
    about->open();

    return application.exec();
}

#include "main.moc"

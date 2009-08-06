/* dtkCreatorWidgetFactory.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Aug  6 18:05:01 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Aug  6 18:05:40 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 2
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCREATORWIDGETFACTORY_H
#define DTKCREATORWIDGETFACTORY_H

#include <QtDebug>
#include <QtCore>
#include <QtGui>

// /////////////////////////////////////////////////////////////////
// dtkCreatorWidgetFactory - Button wrapper
// /////////////////////////////////////////////////////////////////

class dtkCreatorWidgetFactoryButton : public QPushButton
{
    Q_OBJECT

public:
    dtkCreatorWidgetFactoryButton(QString title, QString callback) : QPushButton(title, 0) {
	this->callbackFunction = callback;

	connect(this, SIGNAL(clicked()), this, SLOT(callback()));
    }

signals:
    void interpret(const QString&, int *);

public slots:
    void callback(void) {
	int stat;
	emit interpret((const QString &)callbackFunction, &stat);
    }

private:
    QString callbackFunction;
};

// /////////////////////////////////////////////////////////////////
// dtkCreatorWidgetFactory - GroupBox wrapper
// /////////////////////////////////////////////////////////////////

class dtkCreatorWidgetFactoryGroupBox : public QGroupBox
{
    Q_OBJECT

public:
    dtkCreatorWidgetFactoryGroupBox(QString title) : QGroupBox(title, 0) {
	setLayout(new QVBoxLayout(this));
    }

    void addButton(dtkCreatorWidgetFactoryButton *widget) {
	layout()->addWidget(widget);
    }

    QWidget *widget(void) {
	return (QWidget *)this;
    }
};

// /////////////////////////////////////////////////////////////////
// dtkCreatorWidgetFactory
// /////////////////////////////////////////////////////////////////

class dtkCreatorWidgetFactory : public QObject
{
    Q_OBJECT

public:
    static dtkCreatorWidgetFactory *instance(void);

signals:
    void interpret(const QString&, int *);

public slots:
    dtkCreatorWidgetFactoryButton   *createButton(QString title, QString callback);
    dtkCreatorWidgetFactoryGroupBox *createGroupBox(QString title);

protected:
     dtkCreatorWidgetFactory(void);
    ~dtkCreatorWidgetFactory(void);

private:
    static dtkCreatorWidgetFactory *m_instance;
};

#endif

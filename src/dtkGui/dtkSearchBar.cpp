/* dtkSearchBar.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Dec  9 10:18:59 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Dec  9 10:19:06 2009 (+0100)
 *           By: Julien Wintz
 *     Update #: 1
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkSearchBar.h"
#include "dtkSearchBox.h"

class dtkSearchBarItemPrivate
{
public:
    QComboBox *key;
    QLineEdit *value;

    QPushButton *more;
    QPushButton *less;

    QSortFilterProxyModel *proxy;
};

dtkSearchBarItem::dtkSearchBarItem(QWidget *parent) : QFrame(parent), d(new dtkSearchBarItemPrivate)
{
    d->key = new QComboBox(this);
    d->value = new QLineEdit(this);
    d->more = new QPushButton("+", this);
    d->less = new QPushButton("-", this);

    d->proxy = new QSortFilterProxyModel(this);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(d->key);
    layout->addWidget(d->value);
    layout->addWidget(d->more);
    layout->addWidget(d->less);

    connect(d->more, SIGNAL(clicked()), this, SLOT(onMoreClicked()));
    connect(d->less, SIGNAL(clicked()), this, SLOT(onLessClicked()));
    connect(d->key, SIGNAL(currentIndexChanged(QString)), this, SIGNAL(keyChanged(QString)));
    connect(d->key, SIGNAL(currentIndexChanged(int)), this, SLOT(setFilterKeyColumn(int)));
    connect(d->value, SIGNAL(textChanged(QString)), this, SIGNAL(valueChanged(QString)));
    connect(d->value, SIGNAL(textChanged(QString)), d->proxy, SLOT(setFilterRegExp(QString)));

    this->setAttribute(Qt::WA_MacShowFocusRect, false);
}

dtkSearchBarItem::~dtkSearchBarItem(void)
{
    delete d;

    d = NULL;
}

void dtkSearchBarItem::addKey(const QString& key)
{
    d->key->addItem(key);
}

void dtkSearchBarItem::setKey(const QString& key)
{
    d->key->setCurrentIndex(d->key->findText(key));
}

void dtkSearchBarItem::setValue(const QString& value)
{
    d->value->setText(value);
}

QString dtkSearchBarItem::key(void) const
{
    return d->key->currentText();
}

QString dtkSearchBarItem::value(void) const
{
    return d->value->text();
}

QSortFilterProxyModel *dtkSearchBarItem::proxy(void)
{
    return d->proxy;
}

void dtkSearchBarItem::onMoreClicked(void)
{
    emit more(this);
}

void dtkSearchBarItem::onLessClicked(void)
{
    emit less(this);
}

void dtkSearchBarItem::setFilterKeyColumn(int column)
{
    d->proxy->setFilterKeyColumn(column);
}

class dtkSearchBarPrivate
{
public:

    // -- graphical interface

    QVBoxLayout *layout;
    dtkSearchBox *box;

    QStringList keys;
    QString default_key;

    // -- logical interface

    QAbstractItemModel *model;
    QAbstractItemView *view;
};

dtkSearchBar::dtkSearchBar(QWidget *parent) : QWidget(parent), d(new dtkSearchBarPrivate)
{
    d->model = NULL;
    d->view = NULL;

    d->box = new dtkSearchBox(this);

    d->layout = new QVBoxLayout(this);
    d->layout->setContentsMargins(0, 0, 0, 0);
    d->layout->setSpacing(0);
    d->layout->addWidget(d->box);

    connect(d->box, SIGNAL(search(QString)), this, SLOT(setup(QString)));
}

dtkSearchBar::~dtkSearchBar(void)
{
    delete d;

    d = NULL;
}

void dtkSearchBar::addKey(const QString& key)
{
    d->keys << key;
}

void dtkSearchBar::setDefaultKey(const QString& key)
{
    d->default_key = key;
}

void dtkSearchBar::setModel(QAbstractItemModel *model)
{
    d->model = model;
}

void dtkSearchBar::setView(QAbstractItemView *view)
{
    d->view = view;
}

void dtkSearchBar::setup(QString value)
{
    this->addItem(NULL);
}

void dtkSearchBar::addItem(dtkSearchBarItem *item)
{
    Q_UNUSED(item);

    dtkSearchBarItem *new_item = new dtkSearchBarItem(this);

    if(d->layout->count() == 1) {

        new_item->addKey(d->default_key);
        new_item->setKey(d->default_key);
        new_item->setValue(d->box->text());

        connect(new_item, SIGNAL(valueChanged(QString)), d->box, SLOT(setText(QString)));
        connect(d->box, SIGNAL(textChanged(QString)), new_item, SLOT(setValue(QString)));

    }  else {

        foreach(QString key, d->keys)
            new_item->addKey(key);

    }

    connect(new_item, SIGNAL(more(dtkSearchBarItem *)), this, SLOT(addItem(dtkSearchBarItem *)));
    connect(new_item, SIGNAL(less(dtkSearchBarItem *)), this, SLOT(removeItem(dtkSearchBarItem *)));

    d->layout->addWidget(new_item);

    filter();
}

void dtkSearchBar::removeItem(dtkSearchBarItem *item)
{
    if(d->layout->count() == 1)
        return;

    d->layout->removeWidget(item);

    delete item;

    filter();
}

void dtkSearchBar::filter(void)
{
    if(!d->model && !d->view)
        return;

    QSortFilterProxyModel *last = NULL;

    for(int i = 1; i < d->layout->count(); i++) {

        dtkSearchBarItem *item = dynamic_cast<dtkSearchBarItem *>(d->layout->itemAt(i)->widget());

        last ? item->proxy()->setSourceModel(last) : item->proxy()->setSourceModel(d->model);
        last = item->proxy();
    }

    d->view->setModel(last);
}

/* tstMainWindow.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Sep  5 13:32:53 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Sep  5 13:58:18 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 55
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "tstMainWindow.h"

#include <dtkCore/dtkPlugin.h>
#include <dtkCore/dtkPluginManager.h>

#include <dtkGui/dtkAboutPlugin.h>

class tstMainWindowPrivate
{
public:
    QListWidget *list;
};

tstMainWindow::tstMainWindow(QWidget *parent) : QMainWindow(parent), d(new tstMainWindowPrivate)
{
    d->list = new QListWidget(this);

    foreach(dtkPlugin *plugin, dtkPluginManager::instance()->plugins())
        d->list->addItem(plugin->name());

    this->setCentralWidget(d->list);
    this->setWindowTitle("About plugin");

    connect(d->list, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(onItemClicked(QListWidgetItem *)));
}

tstMainWindow::~tstMainWindow(void)
{
    delete d;

    d = NULL;
}

void tstMainWindow::onItemClicked(QListWidgetItem *item)
{
    dtkAboutPlugin *about = new dtkAboutPlugin(item->text());
    
    QDialog *dialog = new QDialog(this);
    dialog->setAttribute(Qt::WA_DeleteOnClose, true);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(Qt::Horizontal);
    buttonBox->addButton(new QPushButton("Ok", buttonBox), QDialogButtonBox::AcceptRole);
    buttonBox->addButton(new QPushButton("Cancel", buttonBox), QDialogButtonBox::RejectRole);

    QVBoxLayout *layout = new QVBoxLayout(dialog);
    layout->addWidget(about);
    layout->addWidget(buttonBox);
    
    connect(buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));

    dialog->open();
}

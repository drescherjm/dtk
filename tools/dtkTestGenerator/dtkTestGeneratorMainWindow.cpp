/* dtkTestGeneratorMainWindow.cpp ---
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Mar  9 22:23:06 2009 (+0100)
 * Version: $Id$
 * Last-Updated:  Tue Mar 24 08:46:36 2009
 *           By: Jean-Christophe Lombardo
 *     Update #: 72
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include    "dtkTestGenerator.h"
#include    "dtkTestGeneratorMainWindow.h"
#include "ui_dtkTestGeneratorMainWindow.h"

class dtkTestGeneratorMainWindowPrivate
{
public:
    Ui::dtkTestGeneratorMainWindow ui;

    QString output;
    QString className;
};

dtkTestGeneratorMainWindow::dtkTestGeneratorMainWindow(QWidget *parent) : QMainWindow(parent)
{
    this->d = new dtkTestGeneratorMainWindowPrivate;
    this->d->ui.setupUi(this);

    connect(d->ui.pathToolButton, SIGNAL(clicked()), this, SLOT(onOutputPathClicked()));
    connect(d->ui.pathLineEdit,   SIGNAL(textEdited(const QString&)), this, SLOT(onOutputPathChanged()));
    connect(d->ui.classLineEdit,  SIGNAL(textEdited(const QString&)), this, SLOT(onClassNameChanged()));

    connect(d->ui.generateAction, SIGNAL(triggered()), this, SLOT(generate()));
    connect(d->ui.quitAction,     SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(d->ui.aboutAction,    SIGNAL(triggered()), this, SLOT(about()));

    Q_UNUSED(statusBar());
}

dtkTestGeneratorMainWindow::~dtkTestGeneratorMainWindow(void)
{
    delete this->d;
    this->d = NULL;
}

void dtkTestGeneratorMainWindow::about(void)
{
    QMessageBox::about(this, "dtkTestGenerator v0.1.0",
                       "<b>dtkTestGenerator</b> aims at helping developer "
                       "generate a template to be used as a starting point for "
                       "the creation of new tests.");
}

void dtkTestGeneratorMainWindow::onOutputPathClicked(void)
{
    d->output = QFileDialog::getExistingDirectory(this, tr("Choose Directory"),
                                                      ".",
                                                      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        
    d->ui.pathLineEdit->setText(d->output);

    update();
}

void dtkTestGeneratorMainWindow::onOutputPathChanged(void)
{
    d->output = d->ui.pathLineEdit->text();

    update();
}

void dtkTestGeneratorMainWindow::onClassNameChanged(void)
{
    d->className = d->ui.classLineEdit->text();

    update();
}

void dtkTestGeneratorMainWindow::update(void)
{
    d->ui.outputNameLabel->setText(
        QString("%1Test")
        .arg(d->className)
                );
}

void dtkTestGeneratorMainWindow::generate(void)
{
    QDir outputParentDirectory(d->output);

    if(d->output.isNull() || !outputParentDirectory.exists()) {
        QMessageBox::warning(this, "Plugin generation", "Specify a valid output directory.");
        return;
    }

    dtkTestGenerator generator;
    generator.setOutputDirectory(d->output);
    generator.setClassName(d->className);

    if(generator.run())
        statusBar()->showMessage("Generation succeeded", 2000);
    else
        QMessageBox::warning(this, "Plugin generation", "Generation failed.");
}

/* dtkPluginGeneratorMainWindow.cpp --- 
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

#include    "dtkPluginGenerator.h"
#include    "dtkPluginGeneratorMainWindow.h"
#include "ui_dtkPluginGeneratorMainWindow.h"

class dtkPluginGeneratorMainWindowPrivate
{
public:
    Ui::dtkPluginGeneratorMainWindow ui;

    QString output;
    QString prefix;
    QString type;
    QString suffix;
};

dtkPluginGeneratorMainWindow::dtkPluginGeneratorMainWindow(QWidget *parent) : QMainWindow(parent)
{
    this->d = new dtkPluginGeneratorMainWindowPrivate;
    this->d->ui.setupUi(this);

    connect(d->ui.pathToolButton, SIGNAL(clicked()), this, SLOT(onOutputPathClicked()));
    connect(d->ui.pathLineEdit, SIGNAL(textEdited(const QString&)), this, SLOT(onOutputPathChanged()));
    connect(d->ui.pluginTypeCombo, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(onPluginTypeChanged()));
    connect(d->ui.prefixLineEdit, SIGNAL(textEdited(const QString&)), this, SLOT(onPrefixChanged()));
    connect(d->ui.suffixLineEdit, SIGNAL(textEdited(const QString&)), this, SLOT(onSuffixChanged()));

    connect(d->ui.generateAction, SIGNAL(triggered()), this, SLOT(generate()));
    connect(d->ui.quitAction,     SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(d->ui.aboutAction,    SIGNAL(triggered()), this, SLOT(about()));

    Q_UNUSED(statusBar());
}

dtkPluginGeneratorMainWindow::~dtkPluginGeneratorMainWindow(void)
{
    delete this->d;
    this->d = NULL;
}

void dtkPluginGeneratorMainWindow::about(void)
{
    QMessageBox::about(this, "dtkPluginGenerator v0.1.0",
                       "<b>dtkPluginGenerator</b> aims at helping developer "
                       "generate a template to be used as a starting point for "
                       "the development of new plugins.");
}

void dtkPluginGeneratorMainWindow::onOutputPathClicked(void)
{
    d->output = QFileDialog::getExistingDirectory(this, tr("Choose Directory"),
                                                      ".",
                                                      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        
    d->ui.pathLineEdit->setText(d->output);

    update();
}

void dtkPluginGeneratorMainWindow::onOutputPathChanged(void)
{
    d->output = d->ui.pathLineEdit->text();

    update();
}

void dtkPluginGeneratorMainWindow::onPluginTypeChanged(void)
{
    if(d->ui.pluginTypeCombo->currentIndex() > 0) {
        d->type = d->ui.pluginTypeCombo->currentText();
        update();
    }
}

void dtkPluginGeneratorMainWindow::onPrefixChanged(void)
{
    d->prefix = d->ui.prefixLineEdit->text();
    d->prefix.toLower();

    update();
}

void dtkPluginGeneratorMainWindow::onSuffixChanged(void)
{
    d->suffix = d->ui.suffixLineEdit->text();

    update();
}

void dtkPluginGeneratorMainWindow::update(void)
{
    d->ui.outputNameLabel->setText(
        QString("%1/%2%3%4")
        .arg(d->output)
        .arg(d->prefix)
        .arg(d->type)
        .arg(d->suffix)
    );
}

void dtkPluginGeneratorMainWindow::generate(void)
{
    QDir outputParentDirectory(d->output);

    if(d->output.isNull() || !outputParentDirectory.exists()) {
        QMessageBox::warning(this, "Plugin generation", "Specify a valid output directory.");
        return;
    }

    if(d->prefix.isNull()) {
        QMessageBox::warning(this, "Plugin generation", "Specify a prefix.");
        return;
    }

    if(d->type.isNull()) {
        QMessageBox::warning(this, "Plugin generation", "Specify a plugin type.");
        return;
    }

    if(d->suffix.isNull()) {
        QMessageBox::warning(this, "Plugin generation", "Specify a suffix.");
        return;
    }

    dtkPluginGenerator generator;
    generator.setOutputDirectory(d->output);
    generator.setPrefix(d->prefix);
    generator.setSuffix(d->suffix);
    generator.setType(d->type);

    if(generator.run())
        statusBar()->showMessage("Generation succeeded", 2000);
    else
        QMessageBox::warning(this, "Plugin generation", "Generation failed.");
}

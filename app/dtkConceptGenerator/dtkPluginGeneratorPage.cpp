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

#include    "dtkPluginGeneratorPage.h"
#include "ui_dtkPluginGeneratorPage.h"

dtkPluginGeneratorPage::dtkPluginGeneratorPage(QWidget *parent) : QWizardPage(parent), ui(new Ui::dtkPluginGeneratorPage)
{
    ui->setupUi(this);
    registerField("plugin.prefix", ui->m_prefix);
    registerField("plugin.suffix", ui->m_suffix);
    registerField("plugin.name", ui->m_name);
    connect(ui->m_prefix, SIGNAL(textChanged(QString)), this, SLOT(refresh()));
    connect(ui->m_suffix, SIGNAL(textChanged(QString)), this, SLOT(refresh()));
}

dtkPluginGeneratorPage::~dtkPluginGeneratorPage(void)
{
    delete ui;
}

void dtkPluginGeneratorPage::initializePage(void)
{
    ui->m_prefix->setText(field("new.prefix").toString());
    ui->m_name->setText(ui->m_prefix->text() + field("new.name").toString());
}

void dtkPluginGeneratorPage::refresh(void)
{
    ui->m_name->setText(ui->m_prefix->text() + field("new.name").toString() + ui->m_suffix->text());
}

//
// dtkPluginGeneratorPage.cpp ends here

#include "dtkPluginGeneratorPage.h"
#include "ui_dtkPluginGeneratorPage.h"

dtkPluginGeneratorPage::dtkPluginGeneratorPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::dtkPluginGeneratorPage)
{
    ui->setupUi(this);
    registerField("plugin.prefix",ui->m_prefix);
    registerField("plugin.suffix",ui->m_suffix);
    registerField("plugin.name",ui->m_name);
}

dtkPluginGeneratorPage::~dtkPluginGeneratorPage()
{
    delete ui;
}

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
    connect(ui->m_prefix,SIGNAL(textChanged(QString)),this,SLOT(refresh()));
    connect(ui->m_suffix,SIGNAL(textChanged(QString)),this,SLOT(refresh()));
}

void dtkPluginGeneratorPage::initializePage()
{
   ui->m_prefix->setText(field("new.prefix").toString());
   ui->m_name->setText(ui->m_prefix->text()+field("new.name").toString());
}

void dtkPluginGeneratorPage::refresh()
{
    ui->m_name->setText(ui->m_prefix->text()+field("new.name").toString()+ui->m_suffix->text());
}

dtkPluginGeneratorPage::~dtkPluginGeneratorPage()
{
    delete ui;
}

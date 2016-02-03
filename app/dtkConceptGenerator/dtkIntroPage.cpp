#include "dtkIntroPage.h"
#include "ui_dtkIntroPage.h"

dtkIntroPage::dtkIntroPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::dtkIntroPage)
{
    ui->setupUi(this);
    registerField("intro.path"       ,ui->m_path       );
    connect(ui->m_browse,SIGNAL(clicked(bool)),this,SLOT(browse()));
}

void dtkIntroPage::browse()
{
    ui->m_path->setText(QFileDialog::getExistingDirectory(this,"Save"));
}

dtkIntroPage::~dtkIntroPage()
{
    delete ui;
}

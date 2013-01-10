#include <QtGui>

#include "dtkGeneratorWizard.h"
#include "dtkGenerator.h"

dtkGeneratorWizard::dtkGeneratorWizard(QWidget *parent)
    : QWizard(parent)
{
    setWindowTitle(tr("DTK Generator Wizard"));

    //! Add Pages to the Wizard.
    setPage(Page_Introduction, new IntroductionPage);
    setPage(Page_Inherit_Or_Wrapp_Interface, new InheritOrWrappInterfacePage);
    setPage(Page_CoreClass_Details, new CoreClassDetailsPage);
    setPage(Page_Common_Details, new CommonDetailsPage);
    setPage(Page_Conclusion, new ConclusionPage);

    //! Set the startup page.
    setStartId(Page_Introduction);

    //! Set 
    setPixmap(QWizard::BackgroundPixmap, QPixmap(":/images/background.png"));

    //! Rename the last button into "Generate!" button.
    setButtonText(QWizard::FinishButton,"Generate!");

    //! Enable "Help" button.
    setOption(QWizard::HaveHelpButton, true);

    //! Connections.
    connect(this, SIGNAL(helpRequested()), this, SLOT(showHelp()));
}

void dtkGeneratorWizard::showHelp()
{
    static QString lastHelpMessage;

    QString message;

    switch (currentId()) {
    case Page_Inherit_Or_Wrapp_Interface:
        message = tr("Choose if you want to inherit from a basic DTK abstraction "
                     "like dtkAbstractData, dtkAbstractProcess and dtkAbstractView "
                     "or an already created application interface.");
        break;

    case Page_CoreClass_Details:
        message = tr("Help for Page_CoreClass_Details page.");
        break;

    case Page_Common_Details:
        message = tr("Help for Page_Common_Details page.");
        break;

    default:
        message = tr("This help is likely not to be of any help.");
    }

    if (lastHelpMessage == message)
        message = tr("Sorry, I already gave what help I could. "
                     "Maybe you should try asking a human?");

    QMessageBox::information(this, tr("DTK Generator Wizard Help"), message);

    lastHelpMessage = message;
}


/* ***************** */
/* Page_Introduction */
/* ***************** */
//
IntroductionPage::IntroductionPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Introduction"));

    setSubTitle(tr("This wizard will help you to generate a core class, a plugin or a composer class for a DTK like project. "
                                      "You simply need to specify a few options to produce the desired files."));


    setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/watermark.png"));

    /*! Widgets */

    //! Widget QGroupBox typeGroupBox: Choose a type between "a Core class", "a Plugin" and "a Composer class".
    typeGroupBox = new QGroupBox(tr("I want to generate ..."));

    coreClassRadioButton = new QRadioButton(tr("a Core class"));
    coreClassRadioButton->setChecked(true);
    pluginRadioButton = new QRadioButton(tr("a Plugin"));
    composerClassRadioButton = new QRadioButton(tr("a Composer class"));


    /*! Layouts */

    //! Layout for QWizardPage IntroductionPage.
    QVBoxLayout *layout = new QVBoxLayout;

    //! Layout for QGroupBox typeGroupBox.
    QVBoxLayout* typeLayout = new QVBoxLayout;
    typeLayout->addWidget(coreClassRadioButton);
    typeLayout->addWidget(pluginRadioButton);
    typeLayout->addWidget(composerClassRadioButton);
    typeGroupBox->setLayout(typeLayout);

    layout->addStretch();
    layout->addWidget(typeGroupBox);
    layout->addStretch();

    setLayout(layout);


    /*! Register fields */

    registerField("IntroductionPage.coreClassSelected", coreClassRadioButton);
    registerField("IntroductionPage.pluginSelected", pluginRadioButton);
    registerField("IntroductionPage.composerClassSelected", composerClassRadioButton);
}

int IntroductionPage::nextId() const
{
    return dtkGeneratorWizard::Page_Inherit_Or_Wrapp_Interface;
}


/* ******************************* */
/* Page_Inherit_Or_Wrapp_Interface */
/* ******************************* */
//
InheritOrWrappInterfacePage::InheritOrWrappInterfacePage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Inherit or Wrapp interface detail"));

    /*! Widgets */

    //! Widget GroupBox interfaceGroupBox: Select an interface.
    interfaceGroupBox = new QGroupBox;

    //! Widget GroupBox dtkInterfaceGroupBox: Choose a DTK interface.
    dtkInterfaceGroupBox = new QGroupBox(tr("a DTK interface."));
    dtkInterfaceGroupBox->setObjectName("dtkInterfaceGroupBox");
    dtkInterfaceGroupBox->setCheckable(true);

    //! Widgets inside GroupBox dtkInterfaceGroupBox.
    dtkInterfaceLabel = new QLabel("dtkAbstract");
    dtkInterfaceLabel->setAlignment(Qt::AlignVCenter);
    dtkInterfaceComboBox = new QComboBox();
    dtkInterfaceComboBox->addItems(QStringList() << QString("Data") << QString("Process") << QString("View"));
    dtkInterfaceComboBox->setCurrentIndex(dtkInterfaceComboBox->findText("Process"));
    dtkInterfaceLabel->setBuddy(dtkInterfaceComboBox);

    //! Widget GroupBox applicationInterfaceGroupBox: Choose an existing application interface.
    applicationInterfaceGroupBox = new QGroupBox(tr("an existing application interface."));
    applicationInterfaceGroupBox->setObjectName("applicationInterfaceGroupBox");
    applicationInterfaceGroupBox->setCheckable(true);

    //! Widgets inside GroupBox applicationInterfaceGroupBox.
    applicationInterfaceLabel = new QLabel(tr("Interface:"));
    applicationInterfaceLineEdit = new QLineEdit;
    applicationInterfacePushButton = new QPushButton("...");
    applicationInterfaceLineEdit->setValidator(new QRegExpValidator(QRegExp("^(?:.*/)?([a-z]+)([A-Z]\\w+)?(?:Abstract)?(Data|Process|View)([A-Z]\\w+)?\\.(h|hpp)$"), this));
    applicationInterfaceLabel->setBuddy(applicationInterfaceLineEdit);


    /*! Layouts */

    //! Layout for QWizardPage Page_Inherit_Or_Wrapp_Interface.
    QVBoxLayout* layout = new QVBoxLayout;

    //! Layout for QGroupBox interfaceGroupBox.
    QVBoxLayout* interfaceLayout = new QVBoxLayout;

    //! Layout for QGroupBox dtkInterfaceGroupBox.
    QGridLayout *dtkInterfaceLayout = new QGridLayout;
    dtkInterfaceLayout->addWidget(dtkInterfaceLabel,0,0);
    dtkInterfaceLayout->addWidget(dtkInterfaceComboBox,0,1);
    dtkInterfaceGroupBox->setLayout(dtkInterfaceLayout);

    interfaceLayout->addWidget(dtkInterfaceGroupBox);

    //! Layout for QGroupBox applicationInterfaceLayout.
    QGridLayout* applicationInterfaceLayout = new QGridLayout;
    applicationInterfaceLayout->addWidget(applicationInterfaceLabel,0,0);
    applicationInterfaceLayout->addWidget(applicationInterfaceLineEdit,0,1);
    applicationInterfaceLayout->addWidget(applicationInterfacePushButton,0,2);
    applicationInterfaceGroupBox->setLayout(applicationInterfaceLayout);

    interfaceLayout->addWidget(applicationInterfaceGroupBox);
    interfaceGroupBox->setLayout(interfaceLayout);

    layout->addStretch();
    layout->addWidget(interfaceGroupBox);
    layout->addStretch();

    setLayout(layout);


    /*! Fields */

    registerField("InheritOrWrappInterfacePage.dtkInterfaceSelected", dtkInterfaceGroupBox,"checked");
    registerField("InheritOrWrappInterfacePage.dtkInterfaceText", dtkInterfaceComboBox,"currentText");
    registerField("InheritOrWrappInterfacePage.applicationInterfaceText",applicationInterfaceLineEdit);


    /*! Connections */

    //! Make exclusive dtkInterfaceGroupBox and applicationInterfaceGroupBox.
    connect(dtkInterfaceGroupBox, SIGNAL(toggled(bool)), this, SLOT(setUnChecked(bool)));
    connect(applicationInterfaceGroupBox, SIGNAL(toggled(bool)), this, SLOT(setUnChecked(bool)));

    //! Enable/disable the button "Continue" or "Next".
    connect(applicationInterfaceLineEdit, SIGNAL(textChanged(QString)), this, SIGNAL(completeChanged()));
    connect(dtkInterfaceGroupBox, SIGNAL(toggled(bool)), this, SIGNAL(completeChanged()));

    //! Open a file explorer to select an application header file.
    connect(applicationInterfacePushButton, SIGNAL(clicked()), this, SLOT(openExplorer()));

    //! Update the applicationInterfaceLineEdit with the new text received from QFileDialog.
    connect(this, SIGNAL(updateText(QString)), applicationInterfaceLineEdit, SLOT(setText(QString)));
}

//! Set the current task in the subTitle.
void InheritOrWrappInterfacePage::initializePage()
{
    //! Check and set focus to the most possible case.
    if ( field("IntroductionPage.coreClassSelected").toBool() ) {
        interfaceGroupBox->setTitle(tr("that will inherit from ..."));
        dtkInterfaceGroupBox->setChecked(true);
        applicationInterfaceGroupBox->setChecked(false);
    }
    else if ( field("IntroductionPage.pluginSelected").toBool() ) {
        interfaceGroupBox->setTitle(tr("that will inherit from ..."));
        dtkInterfaceGroupBox->setChecked(false);
        applicationInterfaceGroupBox->setChecked(true);
    }
    else {
        interfaceGroupBox->setTitle(tr("that will wrapp ..."));
        dtkInterfaceGroupBox->setChecked(false);
        applicationInterfaceGroupBox->setChecked(true);
    }
}

int InheritOrWrappInterfacePage::nextId() const
{
    if (field("IntroductionPage.coreClassSelected").toBool())
        return dtkGeneratorWizard::Page_CoreClass_Details;

    if (field("IntroductionPage.composerClassSelected").toBool() && !field("InheritOrWrappInterfacePage.dtkInterfaceSelected").toBool())
        return dtkGeneratorWizard::Page_Conclusion;

    return dtkGeneratorWizard::Page_Common_Details;
}

//! Enable/disable the button "Continue" or "Next".
bool InheritOrWrappInterfacePage::isComplete() const
{
    QString applicationInterfaceString = applicationInterfaceLineEdit->text();
    int applicationInterfacePos = 0;

    return dtkInterfaceGroupBox->isChecked() ||
           applicationInterfaceLineEdit->validator()->validate(applicationInterfaceString,applicationInterfacePos) == QValidator::Acceptable;
}

//! Make exclusive dtkInterfaceGroupBox and applicationInterfaceGroupBox.
void InheritOrWrappInterfacePage::setUnChecked(bool toggled)
{
    if (sender()->objectName() == "applicationInterfaceGroupBox") {
        applicationInterfaceGroupBox->setChecked(toggled);
        dtkInterfaceGroupBox->setChecked(!toggled);
    }
    else {
        applicationInterfaceGroupBox->setChecked(!toggled);
        dtkInterfaceGroupBox->setChecked(toggled);
    }
}

//! Open a file explorer to select an application header file.
void InheritOrWrappInterfacePage::openExplorer()
{
    QString applicationInterfaceString = QFileDialog::getOpenFileName(this,
                                                                      tr("Select an Application Interface"),
                                                                      "",
                                                                      tr("Headers (*.h *.hpp)"));
    emit updateText(applicationInterfaceString);
}


/* ********************** */
/* Page_CoreClass_Details */
/* ********************** */
//
CoreClassDetailsPage::CoreClassDetailsPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Core class <i>extra</i> details"));


    /*! Widgets */

    //! Widget QGroupBox abstractionLevelButtonGroup: Select the abstraction level of your class.
    abstractionLevelButtonGroup = new QGroupBox(tr("I want my class to be ..."));

    pureAbstractionRadioButton = new QRadioButton(tr("a pure abstraction."));
    defaultImplementationRadioButton = new QRadioButton(tr("an interface with a default implementation."));
    defaultImplementationRadioButton->setChecked(true);
    concreteRadioButton = new QRadioButton(tr("concrete."));


    /*! Layouts */

    //! Layout for QWizardPage CoreClassDetailsPage.
    QVBoxLayout *layout = new QVBoxLayout;

    //! Layout for QGroupBox typeButtonGroup.
    QVBoxLayout* abstractionLevelLayout = new QVBoxLayout;
    abstractionLevelLayout->addWidget(pureAbstractionRadioButton);
    abstractionLevelLayout->addWidget(defaultImplementationRadioButton);
    abstractionLevelLayout->addWidget(concreteRadioButton);
    abstractionLevelButtonGroup->setLayout(abstractionLevelLayout);

    layout->addStretch();
    layout->addWidget(abstractionLevelButtonGroup);
    layout->addStretch();

    setLayout(layout);


    /*! Fields */

    registerField("CoreClassDetailsPage.pureAbstractionSelected", pureAbstractionRadioButton);
    registerField("CoreClassDetailsPage.defaultImplementationSelected", defaultImplementationRadioButton);
    registerField("CoreClassDetailsPage.concreteSelected", concreteRadioButton);
}

int CoreClassDetailsPage::nextId() const
{
    return dtkGeneratorWizard::Page_Common_Details;
}


/* ******************* */
/* Page_Common_Details */
/* ******************* */
//
CommonDetailsPage::CommonDetailsPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Common details"));


    /*! Widgets */

    //! Widget QGroupBox lastDetailsGroupBox: Set the last missing details for the generation.
    lastDetailsGroupBox = new QGroupBox(tr("Here are the last details required ..."));

    //! Widgets to set the application prefix.
    applicationPrefixLabel = new QLabel(tr("Application prefix:"));
    applicationPrefixLineEdit = new QLineEdit;
    applicationPrefixLineEdit->setValidator(new QRegExpValidator(QRegExp("^[a-z]+$"), this));

    //! Widgets to set the name.
    nameLabel    = new QLabel;
    nameLineEdit = new QLineEdit;
    nameLineEdit->setValidator(new QRegExpValidator(QRegExp("^[A-Z][a-zA-Z]+$"), this));


    /*! Layouts */

    //! Layout for QWizardPage CommonDetailsPage.
    QVBoxLayout* layout = new QVBoxLayout;

    //! Layout for QGroupBox lastDetailsGroupBox.
    QGridLayout* lastDetailsLayout = new QGridLayout;

    lastDetailsLayout->addWidget(applicationPrefixLabel,0,0);
    lastDetailsLayout->addWidget(applicationPrefixLineEdit,0,1);
    lastDetailsLayout->addWidget(nameLabel,1,0);
    lastDetailsLayout->addWidget(nameLineEdit,1,1);
    lastDetailsGroupBox->setLayout(lastDetailsLayout);

    layout->addStretch();
    layout->addWidget(lastDetailsGroupBox);
    layout->addStretch();

    setLayout(layout);


    /*! Fields */

    registerField("CommonDetailsPage.applicationPrefixText",applicationPrefixLineEdit);
    registerField("CommonDetailsPage.nameText",nameLineEdit);


    /*! Connections */

    //! Enable/disable the button "Continue" or "Next"
    connect(applicationPrefixLineEdit, SIGNAL(textChanged(QString)), this, SIGNAL(completeChanged()));
    connect(nameLineEdit, SIGNAL(textChanged(QString)), this, SIGNAL(completeChanged()));
}

void CommonDetailsPage::initializePage()
{

    if (field("InheritOrWrappInterfacePage.dtkInterfaceSelected").toBool()) {
        applicationPrefixLabel->setVisible(true);
        applicationPrefixLineEdit->setVisible(true);
    }
    else {
        applicationPrefixLabel->setVisible(false);
        applicationPrefixLineEdit->setVisible(false);
    }

    if ( field("IntroductionPage.coreClassSelected").toBool() )
        nameLabel->setText(tr("Interface name:"));
    else if ( field("IntroductionPage.pluginSelected").toBool() )
        nameLabel->setText(tr("Plugin name:"));
    else if ( field("IntroductionPage.composerClassSelected").toBool() ) {
        nameLabel->setVisible(false);
        nameLineEdit->setVisible(false);
    }
}

int CommonDetailsPage::nextId() const
{
    return dtkGeneratorWizard::Page_Conclusion;
}

bool CommonDetailsPage::isComplete() const
{
    bool completed = true;

    if (field("InheritOrWrappInterfacePage.dtkInterfaceSelected").toBool()) {
        QString applicationPrefixString = applicationPrefixLineEdit->text();
        int applicationPrefixPos = 0;

        completed = completed && applicationPrefixLineEdit->validator()->validate(applicationPrefixString,applicationPrefixPos) == QValidator::Acceptable;
    }

    if (!field("IntroductionPage.composerClassSelected").toBool()) {
        QString nameString = nameLineEdit->text();
        int namePos = 0;

        completed = completed && nameLineEdit->validator()->validate(nameString,namePos) == QValidator::Acceptable;
    }

    return completed;
}


/* *************** */
/* Page_Conclusion */
/* *************** */
//
ConclusionPage::ConclusionPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle( tr("Let's get started!") );


    /*! Widgets */

    //! Widget QGroupBox outputDirGroupBox: Choose an output directory for the generation.
    QGroupBox* outputDirGroupBox = new QGroupBox( tr("I want to generate my files in ...") );

    //! Widgets to set the output directory.
    QLabel* outputDirLabel = new QLabel(tr("the following directory:"));
    QLineEdit* outputDirLineEdit = new QLineEdit;
    QPushButton* outputDirPushButton = new QPushButton("...");


    /*! Layouts */

    //! Layout for QWizardPage ConclusionPage.
    QVBoxLayout* layout = new QVBoxLayout;

    //! Layout for QGroupBox outputDirGroupBox.
    QHBoxLayout* outputDirLayout = new QHBoxLayout;
    outputDirLayout->addWidget(outputDirLabel);
    outputDirLayout->addWidget(outputDirLineEdit);
    outputDirLayout->addWidget(outputDirPushButton);
    outputDirGroupBox->setLayout(outputDirLayout);

    layout->addStretch();
    layout->addWidget(outputDirGroupBox);
    layout->addStretch();

    setLayout(layout);


    /*! Fields */

    registerField("ConclusionPage.outputDirText",outputDirLineEdit);


    /*! Connections */

    //! Open a file explorer to select an application header file.
    connect(outputDirPushButton, SIGNAL(clicked()), this, SLOT(openExplorer()));

    //! Update the applicationInterfaceLineEdit with the new text received from QFileDialog.
    connect(this, SIGNAL(updateText(QString)), outputDirLineEdit, SLOT(setText(QString)));

    //! Enable/disable the button "Continue" or "Next".
    connect(outputDirLineEdit, SIGNAL(textChanged(QString)), this, SIGNAL(completeChanged()));
}

void ConclusionPage::initializePage()
{
    QString applicationInterfaceDirectoryString;

    if ( !field("InheritOrWrappInterfacePage.dtkInterfaceSelected").toBool() ) {
        applicationInterfaceDirectoryString = QFileInfo(field("InheritOrWrappInterfacePage.applicationInterfaceText").toString()).path();

        emit updateText(applicationInterfaceDirectoryString);
    }
}

int ConclusionPage::nextId() const
{
    return -1;
}

bool ConclusionPage::isComplete() const
{
    QFileInfo outputDirFileInfo = QFileInfo(field("ConclusionPage.outputDirText").toString());

    return outputDirFileInfo.isDir() && outputDirFileInfo.isWritable();
}

bool ConclusionPage::validatePage()
{
    dtkGenerator generator;

    if (field("IntroductionPage.coreClassSelected").toBool()) {
        generator.setType("core");

        if (field("CoreClassDetailsPage.pureAbstractionSelected").toBool())
            generator.setAbstractionLevel("pure");
        else if (field("CoreClassDetailsPage.defaultImplementationSelected").toBool())
            generator.setAbstractionLevel("default");
        else if (field("CoreClassDetailsPage.concreteSelected").toBool())
            generator.setAbstractionLevel("concrete");

        generator.setName(field("CommonDetailsPage.nameText").toString());
    }
    else if (field("IntroductionPage.pluginSelected").toBool()) {
        generator.setType("plugin");
        generator.setName(field("CommonDetailsPage.nameText").toString());
    }
    else if (field("IntroductionPage.composerClassSelected").toBool())
        generator.setType("composer");

    if (field("InheritOrWrappInterfacePage.dtkInterfaceSelected").toBool()) {
        generator.setInterface("dtkAbstract" + field("InheritOrWrappInterfacePage.dtkInterfaceText").toString() + ".h");
        generator.setApplicationPrefix(field("CommonDetailsPage.applicationPrefixText").toString());
    }
    else
        generator.setInterface(QFileInfo(field("InheritOrWrappInterfacePage.applicationInterfaceText").toString()).fileName());

    generator.setOutputDirectory(field("ConclusionPage.outputDirText").toString());

    if (generator.checkParameters() && generator.run())
        return true;
    else {
        QMessageBox::warning(this,"Generation result","Generation failed.");
        return false;
    }
}

void ConclusionPage::openExplorer()
{
    emit updateText(QFileDialog::getExistingDirectory(this, tr("Select an Output Directory")));
}


/*! TODO
- Place the main help in the subtitle.
- Only use help for the mandatory syntax.
- Conclusion subTitle: Place the whole todo stuff with colors.
*/

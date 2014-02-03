#ifndef DTKGENERATORWIZARD_H
#define DTKGENERATORWIZARD_H

#include <QWizard>

QT_BEGIN_NAMESPACE
class QGroupBox;
class QCheckBox;
class QComboBox;
class QLabel;
class QLineEdit;
class QRadioButton;
class QToolButton;
class QButtonGroup;
QT_END_NAMESPACE


class dtkGeneratorWizard : public QWizard
{
    Q_OBJECT

public:
    enum { Page_Introduction, Page_Inherit_Or_Wrapp_Interface, Page_CoreClass_Details, Page_Common_Details, Page_Conclusion };

    dtkGeneratorWizard(QWidget *parent = 0);

private slots:
    void showHelp();
};

// Page_Introduction
class IntroductionPage : public QWizardPage
{
    Q_OBJECT

public:
    IntroductionPage(QWidget *parent = 0);

public:
    int nextId() const;

private:
    QGroupBox* typeGroupBox;

    QRadioButton* coreClassRadioButton;
    QRadioButton* pluginRadioButton;
    QRadioButton* composerClassRadioButton;
};

// Page_Inherit_Or_Wrapp_Interface
class InheritOrWrappInterfacePage : public QWizardPage
{
    Q_OBJECT

public:
    InheritOrWrappInterfacePage(QWidget *parent = 0);

protected:
    void initializePage();

public:
    int     nextId() const;
    bool    isComplete() const;

public slots:
    void setUnChecked(bool);
    void openExplorer();

signals:
    void updateText(QString);

private:
    QGroupBox*  interfaceGroupBox;

    QGroupBox*  dtkInterfaceGroupBox;
    QLabel*     dtkInterfaceLabel;
    QComboBox*  dtkInterfaceComboBox;

    QGroupBox*  applicationInterfaceGroupBox;
    QLabel*     applicationInterfaceLabel;
    QLineEdit*  applicationInterfaceLineEdit;
    QPushButton*  applicationInterfacePushButton;
};

// Page_CoreClass_Details
class CoreClassDetailsPage : public QWizardPage
{
    Q_OBJECT

public:
    CoreClassDetailsPage(QWidget *parent = 0);

public:
    int nextId() const;

private:
    QGroupBox* abstractionLevelButtonGroup;

    QRadioButton* pureAbstractionRadioButton;
    QRadioButton* defaultImplementationRadioButton;
    QRadioButton* concreteRadioButton;
};

// Page_Common_Details
class CommonDetailsPage : public QWizardPage
{
    Q_OBJECT

public:
    CommonDetailsPage(QWidget *parent = 0);

protected:
    void initializePage();

public:
    int nextId() const;
    bool isComplete() const;

private:
    QGroupBox* lastDetailsGroupBox;

    QLabel* applicationPrefixLabel;
    QLineEdit* applicationPrefixLineEdit;

    QLabel* nameLabel;
    QLineEdit* nameLineEdit;
};

// Page_Conclusion
class ConclusionPage : public QWizardPage
{
    Q_OBJECT

public:
    ConclusionPage(QWidget *parent = 0);

protected:
    void initializePage();

public:
    int nextId() const;
    bool isComplete() const;
    bool validatePage();

public slots:
    void openExplorer();

signals:
    void updateText(QString);

private:
    QGroupBox* outputDirGroupBox;

    QLabel* outputDirLabel;
    QLineEdit* outputDirLineEdit;
    QPushButton* outputDirPushButton;
};

#endif

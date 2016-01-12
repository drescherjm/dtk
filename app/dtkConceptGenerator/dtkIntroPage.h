#ifndef DTKINTROPAGE_H
#define DTKINTROPAGE_H

#include <QWizardPage>
#include <QFileDialog>

namespace Ui {
class dtkIntroPage;
}

class dtkIntroPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit dtkIntroPage(QWidget *parent = 0);
    ~dtkIntroPage();

public slots:
    void browse();

signals:
    void generatorSet(QString);

private:
    Ui::dtkIntroPage *ui;
};

#endif // dtkIntroPage_H

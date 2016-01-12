#include "dtkConceptGenerator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    dtkConceptGenerator wizard;
    wizard.show();

    return a.exec();
}

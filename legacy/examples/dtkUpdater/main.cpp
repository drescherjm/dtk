#include <QCoreApplication>

#include <dtkCore/dtkUpdater.h>

int main(int argc, char *argv[])
{
    QCoreApplication application(argc, argv);
    application.setApplicationVersion("0.0.1");

    dtkUpdater updater(QUrl("http://www-sop.inria.fr/dream/dtkUpdater/dtkUpdater.xml"));

    return application.exec();
}

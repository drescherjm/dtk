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

#include "dtkConceptGenerator.h"

#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    dtkConceptGenerator wizard;
    wizard.show();

    return application.exec();
}

//
// main.cpp ends here

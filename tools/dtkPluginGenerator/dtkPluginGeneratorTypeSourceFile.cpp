/* dtkPluginGeneratorTypeSourceFile.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Mar 11 14:21:10 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Aug  2 15:24:23 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 29
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkPluginGenerator.h"

bool dtkPluginGenerator::generateTypeSourceFile(void)
{
    QFile typeSourceFile(d->target.absoluteFilePath(QString(d->plugin).append(".cpp")));

    if(!typeSourceFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "dtkPluginGenerator: unable to open" << QString(d->plugin).append(".cpp") << "for writing";
        return false;
    }
        
    QTextStream stream(&typeSourceFile);

    stream << QString(
        "/* %1.cpp --- \n"
        " * \n"
        " * Author:\n"
        " * Copyright (C)\n"
        " * Created:\n"
        " * Version: $Id$\n"
        " * Last-Updated:\n"
        " *           By:\n"
        " *     Update #:\n"
        " */\n"
        "\n"
        "/* Commentary: \n"
        " * \n"
        " */\n"
        "\n"
        "/* Change log:\n"
        " * \n"
        " */\n"
        "\n"
        "#include \"%1.h\"\n"
        "\n"
        "#include <dtkCore/dtkAbstract%3Factory.h>\n"
        "\n"
        "// /////////////////////////////////////////////////////////////////\n"
        "// %1Private\n"
        "// /////////////////////////////////////////////////////////////////\n"
        "\n"
        "class %1Private\n"
        "{\n"
        "public:\n"
        "};\n"
        "\n"
        "// /////////////////////////////////////////////////////////////////\n"
        "// %1\n"
        "// /////////////////////////////////////////////////////////////////\n"
        "\n"
        "%1::%1(void) : dtkAbstract%2(), d(new %1Private)\n"
        "{\n"
        "\n"
        "}\n"
        "\n"
        "%1::~%1(void)\n"
        "{\n"
        "\n"
        "}\n"
        "\n"
        )
        .arg(QString(d->plugin))
        .arg(QString(d->type))
        .arg(QString(d->type).remove("Animator").remove("Decorator").remove("Interactor").remove("Navigator").remove("Reader").remove("Writer"));

    if(   QString(d->type).contains("DataReader")
       || QString(d->type).contains("DataWriter")
       || QString(d->type).contains("ViewAnimator")
       || QString(d->type).contains("ViewDecorator")
       || QString(d->type).contains("ViewInteractor")
       || QString(d->type).contains("ViewNavigator"))

        stream << QString(
        "bool %1::registered(void)\n"
        "{\n"
        "    return dtkAbstract%4Factory::instance()->register%2Type(\"%1\", QStringList() << \"%4\", create%3);\n"
        "}\n"
        "\n"
        "QStringList %1::handled(void) const\n"
        "{\n"
        "    return QStringList() << \"%4\";\n"
        "}\n"
        )
        .arg(QString(d->plugin))
        .arg(QString(d->type))
        .arg(QString(d->plugin).remove(d->prefix).prepend(QString(d->prefix).replace(0, 1, QString(d->prefix).left(1).toUpper())))
        .arg(QString(d->type).remove("Animator").remove("Decorator").remove("Interactor").remove("Navigator").remove("Reader").remove("Writer"));

    else

        stream << QString(
        "bool %1::registered(void)\n"
        "{\n"
        "    return dtkAbstract%4Factory::instance()->register%2Type(\"%1\", create%3);\n"
        "}\n"
        )
        .arg(QString(d->plugin))
        .arg(QString(d->type))
        .arg(QString(d->plugin).remove(d->prefix).prepend(QString(d->prefix).replace(0, 1, QString(d->prefix).left(1).toUpper())))
        .arg(QString(d->type).remove("Animator").remove("Decorator").remove("Interactor").remove("Navigator").remove("Reader").remove("Writer"));

    stream << QString(
        "\n"
        "QString %1::description(void) const\n"
        "{\n"
        "    return \"%1\";\n"
        "}\n"
        "\n"
        "// /////////////////////////////////////////////////////////////////\n"
        "// Process type instanciation\n"
        "// /////////////////////////////////////////////////////////////////\n"
        "\n"
        "dtkAbstract%2 *create%3(void)\n"
        "{\n"
        "    return new %1;\n"
        "}\n"
        "\n"
         )
        .arg(QString(d->plugin))
        .arg(QString(d->type))
        .arg(QString(d->plugin).remove(d->prefix).prepend(QString(d->prefix).replace(0, 1, QString(d->prefix).left(1).toUpper())));

    typeSourceFile.close();

    return true;
}


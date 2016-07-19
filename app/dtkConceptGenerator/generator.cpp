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

#include "generator.h"

void generate(QString target, QMap<QString,QString> pairs, QString path)
{
    QDir dirIn(":/templates/templates/"+target);

    QDir dirOut=QDir(path);
    dirOut.mkdir(target);
    dirOut.cd(target);

    qDebug()<<dirIn;

    QStringList files=dirIn.entryList(QDir::Files);

    for(QString file : files)
    {
        QString inFilePath=dirIn.absoluteFilePath(file);
        QString fileOutPath=dirOut.absolutePath()+"/"+file.replace("class",pairs["${PLUGIN_CLASS_NAME}"]).replace("_", ".");
        QFile fileOut(fileOutPath);

        if (!fileOut.open(QIODevice::WriteOnly | QIODevice::Text))
               return;

        QTextStream out(&fileOut);

        out << readAndReplace(inFilePath, pairs);
    }
}

QString readAndReplace(QString filePath, QMap<QString,QString> pairs)
{
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return QString();

    QTextStream in(&file);

    QString content=in.readAll();

    for(QString key:pairs.keys())
        content=content.replace(key,pairs[key]);

    return content;
}

//
// generator.cpp ends here

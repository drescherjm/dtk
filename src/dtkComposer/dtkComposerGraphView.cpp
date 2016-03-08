/* dtkComposerGraphView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Feb  9 14:43:33 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Mar 21 12:31:54 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 22
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerGraphView.h"
#include "dtkComposerGraph.h"
#include <dtkLog>

class dtkComposerGraphViewPrivate
{
public:
    dtkComposerGraph *graph;
    bool graphviz_avail;
};

dtkComposerGraphView::dtkComposerGraphView(QWidget *parent) : QSvgWidget(parent),d(new dtkComposerGraphViewPrivate)
{
    d->graph = NULL;
    d->graphviz_avail = true;
}

void dtkComposerGraphView::setGraph(dtkComposerGraph *graph)
{
    d->graph = graph;
}

void dtkComposerGraphView::update(void)
{
    if (!d->graphviz_avail)
        return;

    QByteArray content = d->graph->toString().append("\n").toLocal8Bit() ;
    // run dot
    QStringList arglist;
    arglist << "-Tsvg";
    QString command = "dot";
    QProcess cmd;
    QStringList PATH =  QProcessEnvironment::systemEnvironment().value("PATH").split(":") ;
    QDir::setSearchPaths("bin",PATH);
    if(QFile("bin:"+command).exists()) {

        dtkTrace() << "run graphviz dot" ;
        cmd.start(command, arglist, QProcess::Unbuffered | QProcess::ReadWrite);
        cmd.write(content);
        cmd.closeWriteChannel();
        cmd.waitForBytesWritten();
        qlonglong timeout = 3000;
        QString stdout_data;
        if (cmd.waitForFinished(timeout)) {
            QByteArray svg = cmd.readAllStandardOutput();
            this->load(svg);
        } else {
            dtkWarn() << "graphviz timeout !";
        }
    } else {
        d->graphviz_avail = false;
        dtkWarn() << "can't find 'dot' binary in PATH, graphviz probably not installed";
    }
}

dtkComposerGraphView::~dtkComposerGraphView(void)
{
    delete d;

    d = NULL;
}


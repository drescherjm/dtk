#include "dtkMonitoringWriter.h"
#include "dtkMonitor.h"
#include "dtkMonitoringScene.h"

#include <dtkComposer/dtkComposerNode>

class dtkMonitoringWriterPrivate
{
public:
    dtkMonitoringScene* scene;
};


dtkMonitoringWriter::dtkMonitoringWriter()
{
    d = new dtkMonitoringWriterPrivate();
}

dtkMonitoringWriter::~dtkMonitoringWriter()
{
    delete d;
}

void dtkMonitoringWriter::setScene(dtkMonitoringScene *scene)
{
    d->scene = scene;
}

QDomDocument dtkMonitoringWriter::toXML()
{
    if(!d->scene)
        return QDomDocument();

    QDomDocument document("dtk");

    QDomElement root = document.createElement("dtk");
    document.appendChild(root);
    QDomElement sceneElmt=document.createElement("scene");
    sceneElmt.setAttribute("x",d->scene->sceneRect().x());
    sceneElmt.setAttribute("y",d->scene->sceneRect().y());
    sceneElmt.setAttribute("w",d->scene->sceneRect().width());
    sceneElmt.setAttribute("h",d->scene->sceneRect().height());

    root.appendChild(sceneElmt);


    for(QGraphicsItem *item:d->scene->items())
    {
        dtkMonitor* monitor=dynamic_cast<dtkMonitor*>(item);
        if(!monitor)
            continue;
        QDomElement element=document.createElement("node");
        toXML(monitor,element);
        root.appendChild(element);
    }
    return document;
}

void dtkMonitoringWriter::toXML(dtkMonitor* monitor, QDomElement& elmt)
{
    if(!monitor)
        return;
    elmt.setAttribute("title",monitor->node()->titleHint());
    elmt.setAttribute("type",monitor->node()->type());
    elmt.setAttribute("x",monitor->scenePos().x());
    elmt.setAttribute("y",monitor->scenePos().y());
    elmt.setAttribute("z",monitor->zValue());
}

void dtkMonitoringWriter::write(const QString& filename)
{
    QDomDocument document=toXML();

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
          return;

    QTextStream out(&file);
    out << document.toString();
    file.close();
}

#include "dtkMonitoringReader.h"
#include "dtkMonitor.h"
#include "dtkMonitoringScene.h"
#include "dtkMonitoringFactory.h"

class dtkMonitoringReaderPrivate
{
public:
    dtkMonitoringScene* scene;
};

dtkMonitoringReader::dtkMonitoringReader()
{
    d=new dtkMonitoringReaderPrivate();
}

dtkMonitoringReader::~dtkMonitoringReader()
{
    delete d;
}

void dtkMonitoringReader::setScene(dtkMonitoringScene *scene)
{
    d->scene = scene;
}

void dtkMonitoringReader::read(const QString& filename)
{
    QDomDocument doc("dtk");
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
        return;
    if (!doc.setContent(&file)) {
        file.close();
        return;
    }
    file.close();

    QDomElement docElem = doc.documentElement();

    QDomNode n = docElem.firstChild();
    while(!n.isNull()) {
        QDomElement e = n.toElement(); // try to convert the node to an element.
        if(!e.isNull()) {
            if(e.tagName()=="scene") {
                loadSceneFromElement(e);
            } else {
                loadItemFromElement(e);
            }
        }
        n = n.nextSibling();
    }
}

void dtkMonitoringReader::loadItemFromElement(const QDomElement& document)
{
    QString title,type;
    double x,y,z,w,h;

    if(document.hasAttribute("title"))
        title=document.attribute("title");
    if(document.hasAttribute("type"))
        type=document.attribute("type");

    if(document.hasAttribute("x"))
        x=document.attribute("x").toDouble();
    if(document.hasAttribute("y"))
        y=document.attribute("y").toDouble();
    if(document.hasAttribute("z"))
        z=document.attribute("z").toDouble();

    dtkMonitor* monitor=dtkMonitoringFactory::instance()->create(type);
    monitor->setPos(monitor->mapFromScene(monitor->pos()));
    monitor->setZValue(z);
    d->scene->addItem(monitor);
}

void dtkMonitoringReader::loadSceneFromElement(const QDomElement& document)
{
    double x,y,w,h;

    if(document.hasAttribute("x"))
        x=document.attribute("x").toDouble();
    if(document.hasAttribute("y"))
        y=document.attribute("y").toDouble();
    if(document.hasAttribute("w"))
        w=document.attribute("w").toDouble();
    if(document.hasAttribute("h"))
        h=document.attribute("h").toDouble();

    d->scene->setSceneRect(x,y,w,h);
}

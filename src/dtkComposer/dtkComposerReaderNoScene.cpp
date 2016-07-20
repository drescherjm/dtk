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


#include "dtkComposerReaderNoScene.h"

#include "dtkComposerNodeFactory.h"
#include "dtkComposerGraph.h"
#include "dtkComposerNode.h"
#include "dtkComposerNodeBoolean.h"
#include "dtkComposerNodeComposite.h"
#include "dtkComposerNodeControl.h"
#include "dtkComposerNodeControlCase.h"
#include "dtkComposerNodeFile.h"
#include "dtkComposerNodeInteger.h"
#include "dtkComposerNodeLeaf.h"
#include "dtkComposerNodeReal.h"
#include "dtkComposerNodeString.h"
#include "dtkComposerTransmitter.h"
#include "dtkComposerTransmitterProxy.h"
#include "dtkComposerTransmitterProxyLoop.h"
#include "dtkComposerTransmitterProxyVariant.h"

#include <dtkCore/dtkCore.h>

#include <QtCore>
#include <QtXml>

#include <dtkLog/dtkLogger.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerReaderPrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerReaderNoScenePrivate
{
public:
    dtkComposerNodeFactory *factory;
    dtkComposerGraph *graph;

public:
    QHash<int, dtkComposerNode *> node_map;

public:
    dtkComposerNodeComposite *root;
    dtkComposerNodeComposite *node;

public:
    dtkComposerNodeControl *control;

};

// /////////////////////////////////////////////////////////////////
// dtkComposerReaderNoScene
// /////////////////////////////////////////////////////////////////

dtkComposerReaderNoScene::dtkComposerReaderNoScene(void) : d(new dtkComposerReaderNoScenePrivate)
{
    d->factory = NULL;
    d->root    = NULL;
    d->graph   = NULL;

    d->control = NULL;
}

dtkComposerReaderNoScene::~dtkComposerReaderNoScene(void)
{
    delete d;

    d = NULL;
}

void dtkComposerReaderNoScene::setFactory(dtkComposerNodeFactory *factory)
{
    d->factory = factory;
}

void dtkComposerReaderNoScene::setGraph(dtkComposerGraph *graph)
{
    d->graph = graph;
}

bool dtkComposerReaderNoScene::read(const QString& fileName)
{

    QString content;

    QFile file(fileName);

    QByteArray c_bytes;

    if (!file.open(QIODevice::ReadOnly))
        return false;


    if (!dtkFileIsBinary(fileName)) {
        c_bytes = file.readAll();
        content = QString::fromUtf8(c_bytes.data());

    } else {
        QDataStream stream(&file); stream >> c_bytes;
        QByteArray u_bytes = QByteArray::fromHex(qUncompress(c_bytes));
        content = QString::fromUtf8(u_bytes.data(), u_bytes.size());
    }

    file.close();

    return this->readString(content);
}

bool dtkComposerReaderNoScene::readString(const QString& data)
{
    QDomDocument document("dtk");

    if (!document.setContent(data)) {
        dtkDebug() << "reader: no content" << data.size();
        return false;
    }

    // Clear if applicable

    this->clear();

    d->node_map.clear();

    // --

    d->root = dynamic_cast<dtkComposerNodeComposite *>(d->factory->create("composite"));

    d->node = d->root;
    d->graph->addNode(d->root, NULL);

    // Read  nodes

    QDomNodeList nodes = document.firstChild().childNodes();

    for (int i = 0; i < nodes.count(); i++)
        if (nodes.at(i).toElement().tagName() == "node")
            if (!(this->readNode(nodes.at(i)))) {
                this->clear();
                return false;
            }

    // Read edges

    QDomNodeList edges = document.firstChild().childNodes();

    for (int i = 0; i < edges.count(); i++)
        if (edges.at(i).toElement().tagName() == "edge")
            this->readEdge(edges.at(i));

    return true;
}

dtkComposerNode *dtkComposerReaderNoScene::readNode(QDomNode node)
{
    dtkTrace() <<  "reading node" << node.toElement().attribute("type");

    QDomNodeList childNodes = node.childNodes();

    QList<QDomNode> ports;
    QList<QDomNode> notes;
    QList<QDomNode> nodes;
    QList<QDomNode> edges;
    QList<QDomNode> blocks;

    QDomNode header;
    QDomNode footer;
    bool node_control_type = false;

    for (int i = 0; i < childNodes.count(); i++)
        if (childNodes.at(i).toElement().tagName() == "port")
            ports << childNodes.at(i);

    for (int i = 0; i < childNodes.count(); i++)
        if (childNodes.at(i).toElement().tagName() == "note")
            notes << childNodes.at(i);

    for (int i = 0; i < childNodes.count(); i++)
        if (childNodes.at(i).toElement().tagName() == "node")
            nodes << childNodes.at(i);

    for (int i = 0; i < childNodes.count(); i++)
        if (childNodes.at(i).toElement().tagName() == "edge")
            edges << childNodes.at(i);

    for (int i = 0; i < childNodes.count(); i++)
        if (childNodes.at(i).toElement().tagName() == "block")
            blocks << childNodes.at(i);

    for (int i = 0; i < childNodes.count(); i++)
        if (childNodes.at(i).toElement().tagName() == "header")
            header = childNodes.at(i);

    for (int i = 0; i < childNodes.count(); i++)
        if (childNodes.at(i).toElement().tagName() == "footer")
            footer = childNodes.at(i);

    // --

    dtkComposerNode *n = NULL;
    QString type_n = node.toElement().attribute("type");

    if (blocks.count()) {

        n = d->factory->create(node.toElement().attribute("type"));

        d->graph->addNode(n, d->node);

    } else if (node.toElement().tagName() == "block") {

        node_control_type = true;

        if (dtkComposerNodeControlCase *control = dynamic_cast<dtkComposerNodeControlCase *>(d->control)) {
            if (node.toElement().attribute("title") != "Case#default") {
                dtkComposerNodeComposite *b = dynamic_cast<dtkComposerNodeComposite *>(d->factory->create("composite"));
                control->addBlock();
                d->graph->addBlock(d->control);
            }

            n = control->block(control->blockCount() - 1);
        } else {
            n = d->control->block(node.toElement().attribute("blockid").toInt());
        }

    } else if (node.toElement().tagName() == "header") {

        node_control_type = true;
        n = d->control->header();

    } else if (node.toElement().tagName() == "footer") {

        node_control_type = true;
        n = d->control->footer();

    } else if ( type_n == "composite" || type_n == "world" || type_n == "remote" || type_n == "spawn") {

        n = d->factory->create(type_n);

        if (n) {
            d->graph->addNode(n, d->node);
        } else {
            dtkError() <<  "Can't read composition, the following node is unknown:" << node.toElement().attribute("type");
            return NULL;
        }

    } else {

        n = d->factory->create(node.toElement().attribute("type"));

        if (!n) {

            dtkError() <<  "Can't read composition, the following node is unknown:" << node.toElement().attribute("type");
            return NULL;
        }

        d->graph->addNode(n, d->node);

    }

    //FIXME: set metadata ?
    // if(node.toElement().hasAttribute("title"))
    //     n->setTitle(node.toElement().attribute("title"));

    int id = node.toElement().attribute("id").toInt();

    d->node_map.insert(id, n);

    // --

    dtkComposerNodeComposite *t = d->node;

    if (dtkComposerNodeControl *control = dynamic_cast<dtkComposerNodeControl *>(n)) {

        d->control = control;

        this->readNode(header);

        for (int i = 0; i < blocks.count(); i++) {
            d->control = control;

            if (!this->readNode(blocks.at(i)))
                return NULL;
        }

        d->control = control;
        this->readNode(footer);

    }

    if (dtkComposerNodeComposite *composite = dynamic_cast<dtkComposerNodeComposite *>(n)) {

        d->node = composite;

        for (int i = 0; i < ports.count(); i++) {
            if (ports.at(i).toElement().attribute("type") == "input") {
                if (ports.at(i).toElement().attribute("kind") == "proxy") {
                    dtkComposerTransmitter *proxy = new dtkComposerTransmitterProxy(composite);
                    proxy->setRequired(false);
                    composite->appendReceiver(proxy);
                }

                if ((ports.at(i).toElement().attribute("kind") == "proxyloop") ||
                        // for backward compatibility :
                        (ports.at(i).toElement().attribute("kind") == "variant" && ports.at(i).toElement().hasAttribute("loop"))) {
                    dtkComposerTransmitter *proxyloop = new dtkComposerTransmitterProxyLoop(composite);
                    proxyloop->setRequired(false);
                    composite->appendReceiver(proxyloop);
                }

                if (ports.at(i).toElement().attribute("kind") == "proxyvariant") {
                    dtkComposerTransmitter *proxyvariant = new dtkComposerTransmitterProxyVariant(composite);
                    proxyvariant->setRequired(false);
                    composite->appendReceiver(proxyvariant);
                }
            } else {
                if (ports.at(i).toElement().attribute("kind") == "proxy") {
                    dtkComposerTransmitter *proxy = new dtkComposerTransmitterProxy(composite);
                    proxy->setRequired(false);
                    composite->appendEmitter(proxy);
                }

                if ((ports.at(i).toElement().attribute("kind") == "proxyloop") ||
                        // for backward compatibility :
                        (ports.at(i).toElement().attribute("kind") == "variant" && ports.at(i).toElement().hasAttribute("loop"))) {
                    dtkComposerTransmitter *proxyloop = new dtkComposerTransmitterProxyLoop(composite);
                    proxyloop->setRequired(false);
                    composite->appendEmitter(proxyloop);
                }

                if (ports.at(i).toElement().attribute("kind") == "proxyvariant") {
                    dtkComposerTransmitter *proxyvariant = new dtkComposerTransmitterProxyVariant(composite);
                    proxyvariant->setRequired(false);
                    composite->appendEmitter(proxyvariant);
                }

// ---- twins for loops

                if (ports.at(i).toElement().hasAttribute("twin")) {

                    int twin = ports.at(i).toElement().attribute("twin").toInt();

                    dtkComposerNode *wrapee = NULL;

                    dtkComposerTransmitterProxyLoop *proxyloop = dynamic_cast<dtkComposerTransmitterProxyLoop *>(composite->emitters().last());

                    if (proxyloop) {

                        dtkComposerTransmitterProxyLoop *twinproxy = dynamic_cast<dtkComposerTransmitterProxyLoop *>(composite->receivers().at(twin));
                        proxyloop->setTwin(twinproxy);
                        twinproxy->setTwin(proxyloop);

                        dynamic_cast<dtkComposerNodeControl *>(d->control)->appendInputTwin(twinproxy);
                        dynamic_cast<dtkComposerNodeControl *>(d->control)->appendOutputTwin(proxyloop);

                    }
                }

// ----------

            }
        }

        for (int i = 0; i < nodes.count(); i++) {
            if (!this->readNode(nodes.at(i))) {
                return NULL;
            }
        }

        for (int i = 0; i < edges.count(); i++)
            this->readEdge(edges.at(i));
    }

    if (dtkComposerNodeLeaf *leaf = dynamic_cast<dtkComposerNodeLeaf *>(n)) {

        if (dtkComposerNodeBoolean *boolean = dynamic_cast<dtkComposerNodeBoolean *>(leaf)) {

            for (int i = 0; i < childNodes.count(); i++) {
                if (childNodes.at(i).toElement().tagName() == "value") {
                    boolean->setValue(childNodes.at(i).childNodes().at(0).toText().data() == "true");
                }
            }
        }

        if (dtkComposerNodeInteger *integer = dynamic_cast<dtkComposerNodeInteger *>(leaf)) {

            for (int i = 0; i < childNodes.count(); i++) {
                if (childNodes.at(i).toElement().tagName() == "value") {
                    integer->setValue(childNodes.at(i).childNodes().at(0).toText().data().toLongLong());
                }
            }
        }

        if (dtkComposerNodeReal *real = dynamic_cast<dtkComposerNodeReal *>(leaf)) {

            for (int i = 0; i < childNodes.count(); i++) {
                if (childNodes.at(i).toElement().tagName() == "value") {
                    real->setValue(childNodes.at(i).childNodes().at(0).toText().data().toDouble());
                }
            }
        }

        if (dtkComposerNodeString *s = dynamic_cast<dtkComposerNodeString *>(leaf)) {

            for (int i = 0; i < childNodes.count(); i++) {
                if (childNodes.at(i).toElement().tagName() == "value") {
                    s->setValue(childNodes.at(i).childNodes().at(0).toText().data());
                }
            }
        }

        if (dtkComposerNodeFile *f = dynamic_cast<dtkComposerNodeFile *>(leaf)) {

            for (int i = 0; i < childNodes.count(); i++) {
                if (childNodes.at(i).toElement().tagName() == "value") {
                    f->setValue(childNodes.at(i).childNodes().at(0).toText().data());
                }
            }
        }

        if (dtkComposerNodeLeafObject *object_node = dynamic_cast<dtkComposerNodeLeafObject *>(leaf)) {

            for (int i = 0; i < childNodes.count(); i++) {
                if (childNodes.at(i).toElement().tagName() == "implementation") {
                    object_node->createObject(childNodes.at(i).childNodes().at(0).toText().data());
                }
            }
        }

        this->extend(node, leaf);
    }

    d->node = t;

    return n;
}

void dtkComposerReaderNoScene::readEdge(QDomNode node)
{
    QDomElement source = node.firstChildElement("source");
    QDomElement destin = node.firstChildElement("destination");

    int source_node = source.attribute("node").toInt();
    int destin_node = destin.attribute("node").toInt();

    int source_id = source.attribute("id").toInt();
    int destin_id = destin.attribute("id").toInt();

    QString source_type = source.attribute("type");
    QString destin_type = destin.attribute("type");


    dtkComposerTransmitter *s_t = NULL;
    dtkComposerTransmitter *d_t = NULL;

    dtkComposerNode *node_src = d->node_map.value(source_node);
    dtkComposerNode *node_dst = d->node_map.value(destin_node);

    //
    if (source_type == "input")
        if (source_id >= node_src->receivers().count())
            return;
        else
            s_t = node_src->receivers().at(source_id); //FIXME: receivers or emitters ?
    else if (source_id >= node_src->emitters().count())
        return;
    else
        s_t = node_src->emitters().at(source_id);

    if (destin_type == "input")
        if (destin_id >= node_dst->receivers().count())
            return;
        else
            d_t = node_dst->receivers().at(destin_id);
    else if (destin_id >= node_dst->emitters().count())
        return;
    else
        d_t = node_dst->emitters().at(destin_id);

//    edge->setParent(d->node);

    dtkComposerTransmitterLinkList   valid_edges;
    dtkComposerTransmitterLinkList invalid_edges;
    dtkComposerTransmitter::onTransmittersConnected(s_t, d_t, valid_edges, invalid_edges);

    d->graph->addEdge(node_src, node_dst, source_type, destin_type);

    return;
}

void dtkComposerReaderNoScene::extend(const QDomNode& node, dtkComposerNodeLeaf *leaf)
{
    Q_UNUSED(node);
    Q_UNUSED(leaf);
}

void dtkComposerReaderNoScene::clear(void)
{
    if (d->graph)
        d->graph->clear();
}

//
// dtkComposerReaderNoScene.cpp ends here

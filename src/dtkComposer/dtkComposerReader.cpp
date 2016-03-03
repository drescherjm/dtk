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

#include "dtkComposerNodeFactory.h"
#include "dtkComposerGraph.h"
#include "dtkComposerNodeBoolean.h"
#include "dtkComposerNodeComposite.h"
#include "dtkComposerNodeControl.h"
#include "dtkComposerNodeControlCase.h"
#include "dtkComposerNodeFile.h"
#include "dtkComposerNodeInteger.h"
#include "dtkComposerNodeLeaf.h"
// #include "dtkComposerNodeLeafData.h"
// #include "dtkComposerNodeLeafProcess.h"
// #include "dtkComposerNodeLeafView.h"
#include "dtkComposerNodeReal.h"
#include "dtkComposerNodeString.h"
#include "dtkComposerReader.h"
#include "dtkComposerScene.h"
#include "dtkComposerScene_p.h"
#include "dtkComposerSceneEdge.h"
#include "dtkComposerSceneNode.h"
#include "dtkComposerSceneNodeComposite.h"
#include "dtkComposerSceneNodeControl.h"
#include "dtkComposerSceneNodeLeaf.h"
#include "dtkComposerSceneNote.h"
#include "dtkComposerScenePort.h"
#include "dtkComposerStackUtils.h"
#include "dtkComposerTransmitter.h"
#include "dtkComposerTransmitterProxy.h"
#include "dtkComposerTransmitterProxyLoop.h"
#include "dtkComposerTransmitterProxyVariant.h"

#include <dtkCore/dtkCore.h>

#include <QtCore>
#include <QtXml>

#include <dtkLog/dtkLogger.h>

// /////////////////////////////////////////////////////////////////
// dtkLog categories
// /////////////////////////////////////////////////////////////////

//DTK_LOG_CATEGORY(FR_INRIA_DTK_COMPOSER_IO, "fr.inria.dtk.composer.io")

// /////////////////////////////////////////////////////////////////
// dtkComposerReaderPrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerReaderPrivate
{
public:
    bool check(const QDomDocument& document);

public:
    dtkComposerNodeFactory *factory;
    dtkComposerScene *scene;
    dtkComposerGraph *graph;

public:
    QHash<int, dtkComposerSceneNode *> node_map;

public:
    dtkComposerSceneNodeComposite *root;
    dtkComposerSceneNodeComposite *node;

public:
    dtkComposerSceneNodeControl *control;

public:
    QStringList missing_implementation;
    QStringList default_implementation;

public:
    bool use_gui;
};

bool dtkComposerReaderPrivate::check(const QDomDocument& document)
{
    // missing_implementation.clear();
    // default_implementation.clear();

    // QStringList implementations;
    // implementations << dtkAbstractDataFactory::instance()->implementations();
    // implementations << dtkAbstractProcessFactory::instance()->implementations();
    // implementations << dtkAbstractViewFactory::instance()->implementations();

    // QDomNodeList nodes = document.elementsByTagName("implementation");

    // for(int i = 0; i < nodes.count(); i++)
    // {
    //     QString composition_implementation = nodes.at(i).toElement().text();

    //     if(composition_implementation.isEmpty())
    //     {
    //         default_implementation << QString("- %1\n").arg(nodes.at(i).parentNode().toElement().attribute("type"));
    //     }
    //     else if(!implementations.contains(composition_implementation))
    //     {
    //         missing_implementation << QString("- %1\n").arg(composition_implementation);
    //     }
    // }

    // return (missing_implementation.count() + default_implementation.count()) == 0;

    return true;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerReader
// /////////////////////////////////////////////////////////////////

dtkComposerReader::dtkComposerReader(void) : d(new dtkComposerReaderPrivate)
{
    d->factory = NULL;
    d->scene = NULL;
    d->root = NULL;
    d->graph = NULL;

    d->control = NULL;
    d->use_gui = (qApp && qobject_cast<QGuiApplication *>(qApp) && (QGuiApplication::platformName() != "minimal")) ;
}

dtkComposerReader::~dtkComposerReader(void)
{
    delete d;

    d = NULL;
}

void dtkComposerReader::setFactory(dtkComposerNodeFactory *factory)
{
    d->factory = factory;
}

void dtkComposerReader::setScene(dtkComposerScene *scene)
{
    d->scene = scene;
}

void dtkComposerReader::setGraph(dtkComposerGraph *graph)
{
    d->graph = graph;
}

bool dtkComposerReader::read(const QString& fileName, bool append)
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

    return this->readString(content,append);
}

bool dtkComposerReader::readString(const QString& data, bool append, bool paste)
{
    QDomDocument document("dtk");

    if (!document.setContent(data)) {
        dtkDebug()<< "reader: no content"<< data.size();
        return false;
    }

    if(!d->check(document)) {
        if(d->missing_implementation.count() > 0) {
            if (d->use_gui) {
                QMessageBox msgBox;

                msgBox.setText("Node implementations are missing. Load anyway?");
                msgBox.setInformativeText("You will be able to load the composition structure but evaluation will fail if you do not set the missing implementations up.");
                msgBox.setDetailedText(QString("The following implementations are missing:\n%1").arg(d->missing_implementation.join("")));
                msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
                msgBox.setDefaultButton(QMessageBox::Cancel);

                if(msgBox.exec() == QMessageBox::Cancel)
                    return false;
            } else {
                dtkError() << "Can't load composition, mission implementation(s):" << d->missing_implementation.join("");
                return false;
            }
        }

        if(d->default_implementation.count() > 0) {
            QMessageBox msgBox;

            msgBox.setText("Default implementations are used. Load anyway?");
            msgBox.setInformativeText("You will be able to load the composition structure and run the evaluation correctly as long as the default implementations fits your needs.");
            msgBox.setDetailedText(QString("The following default implementations are used:\n%1").arg(d->default_implementation.join("")));
            msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Cancel);

            if(msgBox.exec() == QMessageBox::Cancel)
                return false;
        }
    }

    // Clear scene if applicable

    if(!append) {
        this->clear();
    }

    d->node_map.clear();

    // --

    d->root = d->scene->root();

    if(!append) {
        d->node = d->root;
        d->graph->addNode(d->root->wrapee(), NULL);
    } else if(paste) {
        d->node = d->scene->current();
    } else {
        d->node = new dtkComposerSceneNodeComposite;
        d->node->wrap(d->factory->create("composite"));
        d->node->setParent(d->scene->current());
        d->scene->current()->addNode(d->node);
        d->graph->addNode(d->node->wrapee(), d->node->parent()->wrapee());
    }

    // Feeding scene with notes

    QDomNodeList notes = document.firstChild().childNodes();

    for(int i = 0; i < notes.count(); i++)
        if(notes.at(i).toElement().tagName() == "note")
            this->readNote(notes.at(i));

    // Feeding scene with nodes

    QDomNodeList nodes = document.firstChild().childNodes();

    for(int i = 0; i < nodes.count(); i++)
        if(nodes.at(i).toElement().tagName() == "node")
            if (!(this->readNode(nodes.at(i),paste))) {
                this->clear();
                return false;
            }

    // Feeding scene with edges

    QDomNodeList edges = document.firstChild().childNodes();

    for(int i = 0; i < edges.count(); i++)
        if(edges.at(i).toElement().tagName() == "edge")
            this->readEdge(edges.at(i));

    // --

    if(!append)
        d->scene->setRoot(d->root);
    else if(!paste)
        d->scene->addItem(d->node);

    // --

    return true;
}

dtkComposerSceneNote *dtkComposerReader::readNote(QDomNode node)
{
    qreal x = node.toElement().attribute("x").toFloat();
    qreal y = node.toElement().attribute("y").toFloat();
    qreal w = node.toElement().attribute("w").toFloat();
    qreal h = node.toElement().attribute("h").toFloat();

    dtkComposerSceneNote *note = new dtkComposerSceneNote;
    note->setPos(QPointF(x, y));
    note->setSize(QSizeF(w, h));
    note->setText(node.childNodes().at(0).toText().data());

    d->node->addNote(note);

    note->setParent(d->node);

    return note;
}

dtkComposerSceneNode *dtkComposerReader::readNode(QDomNode node, bool paste)
{
    // qDebug() << Q_FUNC_INFO << "reading node" << node.toElement().attribute("type");

    QDomNodeList childNodes = node.childNodes();

    QList<QDomNode> ports;
    QList<QDomNode> notes;
    QList<QDomNode> nodes;
    QList<QDomNode> edges;
    QList<QDomNode> blocks;

    QDomNode header;
    QDomNode footer;

    for(int i = 0; i < childNodes.count(); i++)
        if(childNodes.at(i).toElement().tagName() == "port")
            ports << childNodes.at(i);

    for(int i = 0; i < childNodes.count(); i++)
        if(childNodes.at(i).toElement().tagName() == "note")
            notes << childNodes.at(i);

    for(int i = 0; i < childNodes.count(); i++)
        if(childNodes.at(i).toElement().tagName() == "node")
            nodes << childNodes.at(i);

    for(int i = 0; i < childNodes.count(); i++)
        if(childNodes.at(i).toElement().tagName() == "edge")
            edges << childNodes.at(i);

    for(int i = 0; i < childNodes.count(); i++)
        if(childNodes.at(i).toElement().tagName() == "block")
            blocks << childNodes.at(i);

    for(int i = 0; i < childNodes.count(); i++)
        if(childNodes.at(i).toElement().tagName() == "header")
            header = childNodes.at(i);

    for(int i = 0; i < childNodes.count(); i++)
        if(childNodes.at(i).toElement().tagName() == "footer")
            footer = childNodes.at(i);

    // --

    dtkComposerSceneNode *n = NULL;
    QString type_n = node.toElement().attribute("type");
    if(blocks.count()) {

        qreal w = node.toElement().attribute("w").toFloat()-4.0;
        qreal h = node.toElement().attribute("h").toFloat()-4.0;

        n = new dtkComposerSceneNodeControl;
        n->wrap(d->factory->create(node.toElement().attribute("type")));
        n->setParent(d->node);
        d->node->addNode(n);
        d->graph->addNode(n->wrapee(), d->node->wrapee());
        n->resize(w, h);

    } else if(node.toElement().tagName() == "block") {

        if (dtkComposerNodeControlCase *control = dynamic_cast<dtkComposerNodeControlCase *>(d->control->wrapee())) {
            if(node.toElement().attribute("title") != "Case#default") {
                dtkComposerSceneNodeComposite *b = new dtkComposerSceneNodeComposite;
                control->addBlock();
                b->wrap(control->block(control->blockCount()-1));
                d->control->addBlock(b);
                d->graph->addBlock(d->control->wrapee());
            }
            n = d->control->blocks().last();
        } else {
            n = d->control->blocks().at(node.toElement().attribute("blockid").toInt());

            qreal x = node.toElement().attribute("x").toFloat();
            qreal y = node.toElement().attribute("y").toFloat();
            qreal w = node.toElement().attribute("w").toFloat()-4;
            qreal h = node.toElement().attribute("h").toFloat()-4;

            d->control->setBlockSize(dynamic_cast<dtkComposerSceneNodeComposite *>(n), x, y, w, h);
        }

    } else if(node.toElement().tagName() == "header") {

        n = d->control->header();

    } else if(node.toElement().tagName() == "footer") {

        n = d->control->footer();

    } else if( type_n == "composite" || type_n == "world" || type_n == "remote"|| type_n == "spawn") {

        dtkComposerNode *c = d->factory->create(type_n);
        if (c) {
            n = new dtkComposerSceneNodeComposite;
            n->wrap(c);
            n->setParent(d->node);
            d->node->addNode(n);
            d->graph->addNode(c, d->node->wrapee());
            if (paste)
                d->scene->addItem(n);
        } else {

            if (d->use_gui) {
                QMessageBox msgBox;
                msgBox.setText("Can't create node " + type_n);
                msgBox.setInformativeText("You are not be able to load the composition.");
                if  (type_n == "remote")
                    msgBox.setDetailedText("You need to compile DTK with DTK_BUILD_DISTRIBUTED");
                else if (type_n == "world")
                    msgBox.setDetailedText("You need to compile DTK with DTK_BUILD_MPI");
                msgBox.setStandardButtons(QMessageBox::Ok);
                msgBox.setDefaultButton(QMessageBox::Ok);

                msgBox.exec();

            } else {
                dtkError() <<  "Can't read composition, the following node is unknown:" << node.toElement().attribute("type");
            }
            return NULL;
        }

    } else {

        n = new dtkComposerSceneNodeLeaf;
        dtkComposerNode *new_node = d->factory->create(node.toElement().attribute("type"));
        if (!new_node) {

            if (d->use_gui) {
                QMessageBox msgBox;
                msgBox.setText("Can't create core node.");
                msgBox.setInformativeText("You are not be able to load the composition.");
                msgBox.setDetailedText(QString("The following node is unknown:\n%1").arg(node.toElement().attribute("type")));
                msgBox.setStandardButtons(QMessageBox::Ok);
                msgBox.setDefaultButton(QMessageBox::Ok);

                msgBox.exec();

            } else {
                dtkError() <<  "Can't read composition, the following node is unknown:" << node.toElement().attribute("type");
            }
            delete n;
            return NULL;
        }

        n->wrap(new_node);
        n->setParent(d->node);
        d->node->addNode(n);
        d->graph->addNode(new_node, d->node->wrapee());

    }
    QPointF position;

    if(node.toElement().hasAttribute("x"))
        position.setX(node.toElement().attribute("x").toFloat());

    if(node.toElement().hasAttribute("y"))
        position.setY(node.toElement().attribute("y").toFloat());

    if (paste)
        n->setPos(position+QPointF(100,100));
    else
        n->setPos(position);

    if(node.toElement().hasAttribute("title"))
        n->setTitle(node.toElement().attribute("title"));

    int id = node.toElement().attribute("id").toInt();

    d->node_map.insert(id, n);

    // --

    dtkComposerSceneNodeComposite *t = d->node;

    if(dtkComposerSceneNodeControl *control = dynamic_cast<dtkComposerSceneNodeControl *>(n)) {

        control->layout();

        d->control = control;

        this->readNode(header);

        for(int i = 0; i < blocks.count(); i++) {
            d->control = control;
            if (!this->readNode(blocks.at(i)))
                return NULL;
        }

        d->control = control;
        this->readNode(footer);

// --- next/previous for loops

        if(dtkComposerSceneNodeComposite *body = control->block("Body")) {

            foreach(dtkComposerScenePort *port, body->inputPorts()) {

                if(int loop = port->loop()) {

                    dtkComposerTransmitter *proxyloop = port->node()->wrapee()->receivers().at(port->node()->inputPorts().indexOf(port));

                    if(dtkComposerSceneNodeComposite *conditional = control->block("Conditional")) {

                        foreach(dtkComposerScenePort *i, conditional->inputPorts()) {

                            if(i->loop() == loop) {

                                dtkComposerTransmitter *proxy = i->node()->wrapee()->receivers().at(i->node()->inputPorts().indexOf(i));

                                dtkComposerTransmitterLinkList   valid_edges;
                                dtkComposerTransmitterLinkList invalid_edges;
                                dtkComposerTransmitter::onTransmittersConnected(proxyloop, proxy, valid_edges, invalid_edges);
                                dtkComposerPropagateEdgeValidity(d->root, valid_edges, invalid_edges);

                            }
                        }
                    }
                }
            }


            foreach(dtkComposerScenePort *port, body->outputPorts()) {

                if(int loop = port->loop()) {

                    dtkComposerTransmitter *proxyloop = port->node()->wrapee()->emitters().at(port->node()->outputPorts().indexOf(port));

                    if(dtkComposerSceneNodeComposite *increment = control->block("Increment")) {

                        foreach(dtkComposerScenePort *i, increment->inputPorts()) {

                            if(i->loop() == loop) {

                                dtkComposerTransmitter *proxy = i->node()->wrapee()->receivers().at(i->node()->inputPorts().indexOf(i));

                                dtkComposerTransmitterLinkList   valid_edges;
                                dtkComposerTransmitterLinkList invalid_edges;
                                dtkComposerTransmitter::onTransmittersConnected(proxyloop, proxy, valid_edges, invalid_edges);
                                dtkComposerPropagateEdgeValidity(d->root, valid_edges, invalid_edges);

                            }
                        }
                    }
                }
            }
        }
// ---
    }

    if(dtkComposerSceneNodeComposite *composite = dynamic_cast<dtkComposerSceneNodeComposite *>(n)) {

        d->node = composite;

        for(int i = 0; i < ports.count(); i++) {
            if(ports.at(i).toElement().attribute("type") == "input") {
                dtkComposerScenePort *port = new dtkComposerScenePort(dtkComposerScenePort::Input, composite);
                if (ports.at(i).toElement().hasAttribute("label"))
                    port->setLabel(ports.at(i).toElement().attribute("label"));
                composite->addInputPort(port);
                if (ports.at(i).toElement().attribute("kind") == "proxy") {
                    dtkComposerTransmitter *proxy = new dtkComposerTransmitterProxy(composite->wrapee());
                    proxy->setRequired(false);
                    composite->wrapee()->appendReceiver(proxy);
                }
                if ((ports.at(i).toElement().attribute("kind") == "proxyloop") ||
                    // for backward compatibility :
                    (ports.at(i).toElement().attribute("kind") == "variant" && ports.at(i).toElement().hasAttribute("loop"))) {
                    dtkComposerTransmitter *proxyloop = new dtkComposerTransmitterProxyLoop(composite->wrapee());
                    proxyloop->setRequired(false);
                    composite->wrapee()->appendReceiver(proxyloop);
                }
                if (ports.at(i).toElement().attribute("kind") == "proxyvariant") {
                    dtkComposerTransmitter *proxyvariant = new dtkComposerTransmitterProxyVariant(composite->wrapee());
                    proxyvariant->setRequired(false);
                    composite->wrapee()->appendReceiver(proxyvariant);
                }
                if (ports.at(i).toElement().hasAttribute("loop"))
                    port->setLoop(ports.at(i).toElement().attribute("loop").toInt());
            } else {
                dtkComposerScenePort *port = new dtkComposerScenePort(dtkComposerScenePort::Output, composite);
                if (ports.at(i).toElement().hasAttribute("label"))
                    port->setLabel(ports.at(i).toElement().attribute("label"));
                composite->addOutputPort(port);
                if (ports.at(i).toElement().attribute("kind") == "proxy") {
                    dtkComposerTransmitter *proxy = new dtkComposerTransmitterProxy(composite->wrapee());
                    proxy->setRequired(false);
                    composite->wrapee()->appendEmitter(proxy);
                }
                if ((ports.at(i).toElement().attribute("kind") == "proxyloop") ||
                    // for backward compatibility :
                    (ports.at(i).toElement().attribute("kind") == "variant" && ports.at(i).toElement().hasAttribute("loop"))) {
                    dtkComposerTransmitter *proxyloop = new dtkComposerTransmitterProxyLoop(composite->wrapee());
                    proxyloop->setRequired(false);
                    composite->wrapee()->appendEmitter(proxyloop);
                }
                if (ports.at(i).toElement().attribute("kind") == "proxyvariant") {
                    dtkComposerTransmitter *proxyvariant = new dtkComposerTransmitterProxyVariant(composite->wrapee());
                    proxyvariant->setRequired(false);
                    composite->wrapee()->appendEmitter(proxyvariant);
                }
                if (ports.at(i).toElement().hasAttribute("loop"))
                    port->setLoop(ports.at(i).toElement().attribute("loop").toInt());

// ---- twins for loops

                if (ports.at(i).toElement().hasAttribute("twin")) {

                    int twin = ports.at(i).toElement().attribute("twin").toInt();

                    QString block;

                    if (ports.at(i).toElement().hasAttribute("block"))
                        block = ports.at(i).toElement().attribute("block");

                    dtkComposerNode *wrapee = NULL;

                    if(block.isEmpty())
                        wrapee = composite->wrapee();
                    else if (d->control) {
                        wrapee = d->control->block(block)->wrapee();
                    }

                    if(wrapee) {

                        dtkComposerTransmitterProxyLoop *proxyloop = dynamic_cast<dtkComposerTransmitterProxyLoop *>(composite->wrapee()->emitters().last());

                        if(proxyloop) {

                            dtkComposerTransmitterProxyLoop *twinproxy = dynamic_cast<dtkComposerTransmitterProxyLoop *>(wrapee->receivers().at(twin));
                            proxyloop->setTwin(twinproxy);
                            twinproxy->setTwin(proxyloop);

                            dynamic_cast<dtkComposerNodeControl *>(d->control->wrapee())->appendInputTwin(twinproxy);
                            dynamic_cast<dtkComposerNodeControl *>(d->control->wrapee())->appendOutputTwin(proxyloop);

                        }
                    }
                }
// ----------

            }
        }

        composite->layout();

        for(int i = 0; i < notes.count(); i++)
            this->readNote(notes.at(i));

        for(int i = 0; i < nodes.count(); i++)
            if (!this->readNode(nodes.at(i)))
                return NULL;

        for(int i = 0; i < edges.count(); i++)
            this->readEdge(edges.at(i));
    }

    if(dtkComposerSceneNodeLeaf *leaf = dynamic_cast<dtkComposerSceneNodeLeaf *>(n)) {

        for(int i = 0; i < childNodes.count(); i++) {
            if(childNodes.at(i).toElement().tagName() == "flag") {
                leaf->flag(QColor(childNodes.at(i).childNodes().at(0).toText().data()));
            }
        }

        for(int i = 0; i < ports.count(); i++) {
            if (ports.at(i).toElement().hasAttribute("label")) {
                if(ports.at(i).toElement().attribute("type") == "input")
                    leaf->inputPorts().at(ports.at(i).toElement().attribute("id").toUInt())->setLabel(ports.at(i).toElement().attribute("label"));
                else
                    leaf->outputPorts().at(ports.at(i).toElement().attribute("id").toUInt())->setLabel(ports.at(i).toElement().attribute("label"));
            }
        }

        if(dtkComposerNodeBoolean *boolean = dynamic_cast<dtkComposerNodeBoolean *>(leaf->wrapee())) {

            for(int i = 0; i < childNodes.count(); i++) {
                if(childNodes.at(i).toElement().tagName() == "value") {
                    boolean->setValue(childNodes.at(i).childNodes().at(0).toText().data() == "true");
                }
            }
        }

        if(dtkComposerNodeInteger *integer = dynamic_cast<dtkComposerNodeInteger *>(leaf->wrapee())) {

            for(int i = 0; i < childNodes.count(); i++) {
                if(childNodes.at(i).toElement().tagName() == "value") {
                    integer->setValue(childNodes.at(i).childNodes().at(0).toText().data().toLongLong());
                }
            }
        }

        if(dtkComposerNodeReal *real = dynamic_cast<dtkComposerNodeReal *>(leaf->wrapee())) {

            for(int i = 0; i < childNodes.count(); i++) {
                if(childNodes.at(i).toElement().tagName() == "value") {
                    real->setValue(childNodes.at(i).childNodes().at(0).toText().data().toDouble());
                }
            }
        }

        if(dtkComposerNodeString *s = dynamic_cast<dtkComposerNodeString *>(leaf->wrapee())) {

            for(int i = 0; i < childNodes.count(); i++) {
                if(childNodes.at(i).toElement().tagName() == "value") {
                    s->setValue(childNodes.at(i).childNodes().at(0).toText().data());
                }
            }
        }

        if(dtkComposerNodeFile *f = dynamic_cast<dtkComposerNodeFile *>(leaf->wrapee())) {

            for(int i = 0; i < childNodes.count(); i++) {
                if(childNodes.at(i).toElement().tagName() == "value") {
                    f->setValue(childNodes.at(i).childNodes().at(0).toText().data());
                }
            }
        }

        if(dtkComposerNodeLeafObject *object_node = dynamic_cast<dtkComposerNodeLeafObject *>(leaf->wrapee())) {

            for(int i = 0; i < childNodes.count(); i++) {
                if(childNodes.at(i).toElement().tagName() == "implementation") {
                    object_node->createObject(childNodes.at(i).childNodes().at(0).toText().data());
                }
            }
        }

        this->extend(node,leaf);
    }

    d->node = t;

    return n;
}

dtkComposerSceneEdge *dtkComposerReader::readEdge(QDomNode node)
{
    QDomElement source = node.firstChildElement("source");
    QDomElement destin = node.firstChildElement("destination");

    int source_node = source.attribute("node").toInt();
    int destin_node = destin.attribute("node").toInt();

    int source_id = source.attribute("id").toInt();
    int destin_id = destin.attribute("id").toInt();

    QString source_type = source.attribute("type");
    QString destin_type = destin.attribute("type");

    dtkComposerSceneEdge *edge = new dtkComposerSceneEdge;
    if (source_type == "input")
        if (source_id >= d->node_map.value(source_node)->inputPorts().count())
            goto handle_failure;
        else
            edge->setSource(d->node_map.value(source_node)->inputPorts().at(source_id));
    else
        if (source_id >= d->node_map.value(source_node)->outputPorts().count())
            goto handle_failure;
        else
            edge->setSource(d->node_map.value(source_node)->outputPorts().at(source_id));
    if (destin_type == "input")
        if (destin_id >= d->node_map.value(destin_node)->inputPorts().count())
            goto handle_failure;
        else
            edge->setDestination(d->node_map.value(destin_node)->inputPorts().at(destin_id));
    else
        if (destin_id >= d->node_map.value(destin_node)->outputPorts().count())
            goto handle_failure;
        else
            edge->setDestination(d->node_map.value(destin_node)->outputPorts().at(destin_id));

    edge->link();
    edge->adjust();

    d->node->addEdge(edge);

    edge->setParent(d->node);

    dtkComposerTransmitterConnection(d->scene->root(), d->node, edge);

    d->graph->addEdge(edge->source()->node()->wrapee(), edge->destination()->node()->wrapee(), source_type, destin_type);

    return edge;

handle_failure:
    dtkWarn() << "Can't create edge from " << d->node_map.value(source_node)->title() << "to" << d->node_map.value(destin_node)->title();
    delete edge;
    return NULL;

}

void dtkComposerReader::extend(const QDomNode& node, dtkComposerSceneNodeLeaf* leaf)
{
    Q_UNUSED(node);
    Q_UNUSED(leaf);
}

void dtkComposerReader::clear(void)
{
    if (d->graph)
        d->graph->clear();

    if (d->scene)
        d->scene->clear();

}

//
// dtkComposerReader.cpp ends here

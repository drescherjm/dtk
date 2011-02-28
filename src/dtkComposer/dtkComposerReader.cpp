/* dtkComposerReader.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Aug 16 15:02:49 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Feb 28 15:26:04 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 485
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerEdge.h"
#include "dtkComposerNode.h"
#include "dtkComposerNodeBoolean.h"
#include "dtkComposerNodeBooleanOperator.h"
#include "dtkComposerNodeFile.h"
#include "dtkComposerNodeNumber.h"
#include "dtkComposerNodeProcess.h"
#include "dtkComposerNodeProperty.h"
#include "dtkComposerNodeString.h"
#include "dtkComposerNodeStringComparator.h"
#include "dtkComposerNodeStringOperator.h"
#include "dtkComposerReader.h"
#include "dtkComposerScene.h"

#include <dtkCore/dtkGlobal.h>

#include <QtXml>

// /////////////////////////////////////////////////////////////////
// dtkComposerReaderPrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerReaderPrivate
{
public:
    dtkComposerScene *scene;

    QHash<int, dtkComposerNode *> node_map;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerReader
// /////////////////////////////////////////////////////////////////

dtkComposerReader::dtkComposerReader(dtkComposerScene *scene) : QObject(), d(new dtkComposerReaderPrivate)
{
    d->scene = scene;
}

dtkComposerReader::~dtkComposerReader(void)
{
    delete d;

    d = NULL;
}

void dtkComposerReader::read(const QString& fileName)
{
    // Setting dom document

    QDomDocument doc("dtk");

    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly))
        return;

    if (!doc.setContent(&file)) {
        file.close();
        return;
    }

    file.close();

    // Clear scene

    d->scene->clear();

    d->node_map.clear();

    // Feeding scene with nodes

    QDomNodeList nodes = doc.firstChild().childNodes();

    for(int i = 0; i < nodes.count(); i++)
        if(nodes.at(i).toElement().tagName() == "node")
            this->readNode(nodes.at(i));

    // Feeding scene with edges

    QDomNodeList edges = doc.firstChild().childNodes();

    for(int i = 0; i < edges.count(); i++) {

        if(edges.at(i).toElement().tagName() != "edge")
            continue;

        QDomElement source = edges.at(i).firstChildElement("source");
        QDomElement destin = edges.at(i).firstChildElement("destination");

        int source_id = source.attribute("node").toInt();
        int destin_id = destin.attribute("node").toInt();
        
        QString source_property = source.attribute("property");
        QString destin_property = destin.attribute("property");
        
        QString source_property_id;
        QString destin_property_id;
        
        if (source.hasAttribute("id"))
            source_property_id = source.attribute("id");

        if (destin.hasAttribute("id"))
            destin_property_id = destin.attribute("id");

        dtkComposerEdge *edge = new dtkComposerEdge;
        
        if(source_property_id.isEmpty() && destin_property_id.isEmpty()) {
            edge->setSource(d->node_map.value(source_id)->outputProperty(source_property));
            edge->setDestination(d->node_map.value(destin_id)->inputProperty(destin_property));
        }

        else if(!source_property_id.isEmpty() && !destin_property_id.isEmpty()) {

            dtkComposerNode *l = d->node_map.value(source_id);
            dtkComposerNode *r = d->node_map.value(destin_id);

            if(l->parentNode() == r) {
                
                edge->setSource(d->node_map.value(source_id)->outputProperty(source_property, d->node_map.value(source_property_id.toInt())));
                edge->setDestination(d->node_map.value(destin_id)->outputProperty(destin_property, d->node_map.value(destin_property_id.toInt())));
            }

            else if(r->parentNode() == l) {

                edge->setSource(d->node_map.value(source_id)->inputProperty(source_property, d->node_map.value(source_property_id.toInt())));
                edge->setDestination(d->node_map.value(destin_id)->inputProperty(destin_property, d->node_map.value(destin_property_id.toInt())));
            }

            else {

                edge->setSource(d->node_map.value(source_id)->outputProperty(source_property, d->node_map.value(source_property_id.toInt())));
                edge->setDestination(d->node_map.value(destin_id)->inputProperty(destin_property, d->node_map.value(destin_property_id.toInt())));
            }
        }


        else if(!source_property_id.isEmpty() || !destin_property_id.isEmpty()) {

            dtkComposerNode *l = d->node_map.value(source_id);
            dtkComposerNode *r = d->node_map.value(destin_id);

            if(!source_property_id.isEmpty()) {

                if(r->parentNode() == l)
                    edge->setSource(d->node_map.value(source_id)->inputProperty(source_property, d->node_map.value(source_property_id.toInt())));
                else
                    edge->setSource(d->node_map.value(source_id)->outputProperty(source_property, d->node_map.value(source_property_id.toInt())));

                edge->setDestination(d->node_map.value(destin_id)->inputProperty(destin_property));
            }

            else {
                
                edge->setSource(d->node_map.value(source_id)->outputProperty(source_property));

                if(l->parentNode() == r)
                    edge->setDestination(d->node_map.value(destin_id)->outputProperty(destin_property, d->node_map.value(destin_property_id.toInt())));
                else
                    edge->setDestination(d->node_map.value(destin_id)->inputProperty(destin_property, d->node_map.value(destin_property_id.toInt())));
            }
        }

        edge->link(true);

        d->scene->addEdge(edge);

        if (edge->source()->node()->parentNode() || edge->destination()->node()->parentNode())
            edge->hide();
    }

    // Feeding scene with notes
    
    QDomNodeList notes = doc.firstChild().childNodes();

    for(int i = 0; i < notes.count(); i++) {
        
        if(notes.at(i).toElement().tagName() != "note")
            continue;

        qreal x = notes.at(i).toElement().attribute("x").toFloat();
        qreal y = notes.at(i).toElement().attribute("y").toFloat();
        qreal w = notes.at(i).toElement().attribute("w").toFloat();
        qreal h = notes.at(i).toElement().attribute("h").toFloat();
        
        d->scene->createNote(notes.at(i).childNodes().at(0).toText().data(), QPointF(x, y), QSizeF(w, h));
    }
}

dtkComposerNode *dtkComposerReader::readNode(QDomNode node)
{
    QPointF position;
    
    if(node.toElement().hasAttribute("x"))
        position.setX(node.toElement().attribute("x").toFloat());
    
    if(node.toElement().hasAttribute("y"))
        position.setY(node.toElement().attribute("y").toFloat());

    dtkComposerNode *n = NULL;

    if(node.toElement().attribute("type") != "dtkComposerNodeComposite")
        n = d->scene->createNode(node.toElement().attribute("type"), position);

    int id = node.toElement().attribute("id").toInt();

    // Composite node

    if(node.toElement().attribute("type") == "dtkComposerNodeComposite") {

        QList<dtkComposerNode *> child_nodes;

        QDomNodeList children = node.childNodes();

        for(int i = 0; i < children.count(); i++) {

            if(children.at(i).toElement().tagName() != "node")
                continue;
         
            child_nodes << this->readNode(children.at(i));
        }

        n = d->scene->createGroup(child_nodes, position);
    }
    
    // Boolean node
    
    if(dtkComposerNodeBoolean *boolean_node = dynamic_cast<dtkComposerNodeBoolean *>(n)) {
        
        QDomNodeList children = node.childNodes();
        
        for(int i = 0; i < children.count(); i++) {

            if(children.at(i).toElement().tagName() != "value")
                continue;

            boolean_node->setValue((children.at(i).childNodes().at(0).toText().data() == "true"));
        }
    }

    // Boolean operator node
    
    if(dtkComposerNodeBooleanOperator *boolean_operator_node = dynamic_cast<dtkComposerNodeBooleanOperator *>(n)) {
        
        QDomNodeList children = node.childNodes();
        
        for(int i = 0; i < children.count(); i++) {

            if(children.at(i).toElement().tagName() != "operation")
                continue;

            dtkComposerNodeBooleanOperator::Operation operation;

            if(children.at(i).childNodes().at(0).toText().data() == "and")
                operation = dtkComposerNodeBooleanOperator::And;
            else if(children.at(i).childNodes().at(0).toText().data() == "or")
                operation = dtkComposerNodeBooleanOperator::Or;
            else if(children.at(i).childNodes().at(0).toText().data() == "xor")
                operation = dtkComposerNodeBooleanOperator::Xor;
            else if(children.at(i).childNodes().at(0).toText().data() == "nand")
                operation = dtkComposerNodeBooleanOperator::Nand;
            else if(children.at(i).childNodes().at(0).toText().data() == "nor")
                operation = dtkComposerNodeBooleanOperator::Nor;
            else if(children.at(i).childNodes().at(0).toText().data() == "xnor")
                operation = dtkComposerNodeBooleanOperator::Xnor;
            else if(children.at(i).childNodes().at(0).toText().data() == "imp")
                operation = dtkComposerNodeBooleanOperator::Imp;
            else if(children.at(i).childNodes().at(0).toText().data() == "nimp")
                operation = dtkComposerNodeBooleanOperator::Nimp;
            else
                operation = dtkComposerNodeBooleanOperator::And;

            boolean_operator_node->setOperation(operation);
        }        
    }
    
    // Number node
    
    if(dtkComposerNodeNumber *number_node = dynamic_cast<dtkComposerNodeNumber *>(n)) {
        
        QDomNodeList children = node.childNodes();
        
        for(int i = 0; i < children.count(); i++) {

            if(children.at(i).toElement().tagName() != "genre") 
                continue;

            dtkComposerNodeNumber::Genre genre;

            if(children.at(i).childNodes().at(0).toText().data() == "int")
                genre = dtkComposerNodeNumber::Int;
            else if(children.at(i).childNodes().at(0).toText().data() == "uint")
                genre = dtkComposerNodeNumber::UInt;
            else if(children.at(i).childNodes().at(0).toText().data() == "long")
                genre = dtkComposerNodeNumber::Long;
            else if(children.at(i).childNodes().at(0).toText().data() == "ulong")
                genre = dtkComposerNodeNumber::ULong;
            else if(children.at(i).childNodes().at(0).toText().data() == "longlong")
                genre = dtkComposerNodeNumber::LongLong;
            else if(children.at(i).childNodes().at(0).toText().data() == "ulonglong")
                genre = dtkComposerNodeNumber::ULongLong;
            else if(children.at(i).childNodes().at(0).toText().data() == "float")
                genre = dtkComposerNodeNumber::Float;
            else if(children.at(i).childNodes().at(0).toText().data() == "double")
                genre = dtkComposerNodeNumber::Double;

            number_node->setGenre(genre);
        }
        
        for(int i = 0; i < children.count(); i++) {

            if(children.at(i).toElement().tagName() != "value") 
                continue;

            QString value = children.at(i).childNodes().at(0).toText().data();

            switch (number_node->genre()) {

            case (dtkComposerNodeNumber::Int):
                number_node->setValue(value.toInt());
                break;
        
            case (dtkComposerNodeNumber::UInt):
                number_node->setValue(value.toUInt());
                break;
                
            case (dtkComposerNodeNumber::Long):
                number_node->setValue(value.toLong());
                break;
                
            case (dtkComposerNodeNumber::ULong):
                number_node->setValue(value.toULong());
                break;
                
            case (dtkComposerNodeNumber::LongLong):
                number_node->setValue(value.toLongLong());
                break;
                
            case (dtkComposerNodeNumber::ULongLong):
                number_node->setValue(value.toULongLong());
                break;
                
            case (dtkComposerNodeNumber::Float):
                number_node->setValue(value.toFloat());
                break;
                
            case (dtkComposerNodeNumber::Double):
                number_node->setValue(value.toDouble());
                break;
                
            default:
                number_node->setGenre(dtkComposerNodeNumber::Int);
                number_node->setValue(value.toInt());
                break;
            }
        }
    }

    // File node
    
    if(dtkComposerNodeFile *file_node = dynamic_cast<dtkComposerNodeFile *>(n)) {
        
        QDomNodeList children = node.childNodes();
        
        for(int i = 0; i < children.count(); i++) {

            if(children.at(i).toElement().tagName() != "name")
                continue;

            file_node->setFileName(children.at(i).childNodes().at(0).toText().data());
        }        
    }

    // String node
    
    if(dtkComposerNodeString *string_node = dynamic_cast<dtkComposerNodeString *>(n)) {
        
        QDomNodeList children = node.childNodes();
        
        for(int i = 0; i < children.count(); i++) {

            if(children.at(i).toElement().tagName() != "value")
                continue;

            string_node->setValue(children.at(i).childNodes().at(0).toText().data());
        }
    }

    // String comparator
    
    if(dtkComposerNodeStringComparator *string_comparator_node = dynamic_cast<dtkComposerNodeStringComparator *>(n)) {
        
        QDomNodeList children = node.childNodes();
        
        for(int i = 0; i < children.count(); i++) {

            if(children.at(i).toElement().tagName() != "operation")
                continue;

            dtkComposerNodeStringComparator::Operation operation;

            if(children.at(i).childNodes().at(0).toText().data() == "<")
                operation = dtkComposerNodeStringComparator::LesserThan;
            else if(children.at(i).childNodes().at(0).toText().data() == "<=")
                operation = dtkComposerNodeStringComparator::LesserThanOrEqual;
            else if(children.at(i).childNodes().at(0).toText().data() == ">")
                operation = dtkComposerNodeStringComparator::GreaterThan;
            else if(children.at(i).childNodes().at(0).toText().data() == ">=")
                operation = dtkComposerNodeStringComparator::GreaterThanOrEqual;
            else if(children.at(i).childNodes().at(0).toText().data() == "==")
                operation = dtkComposerNodeStringComparator::Equal;
            else if(children.at(i).childNodes().at(0).toText().data() == "!=")
                operation = dtkComposerNodeStringComparator::Differ;
            else
                operation = dtkComposerNodeStringComparator::Equal;

            string_comparator_node->setOperation(operation);
        }
    }

    // String operator
    
    if(dtkComposerNodeStringOperator *string_operator_node = dynamic_cast<dtkComposerNodeStringOperator *>(n)) {
        
        QDomNodeList children = node.childNodes();
        
        for(int i = 0; i < children.count(); i++) {

            if(children.at(i).toElement().tagName() != "operation")
                continue;

            dtkComposerNodeStringOperator::Operation operation;

            if(children.at(i).childNodes().at(0).toText().data() == "<<")
                operation = dtkComposerNodeStringOperator::Append;
            else if(children.at(i).childNodes().at(0).toText().data() == ">>")
                operation = dtkComposerNodeStringOperator::Prepend;
            else
                operation = dtkComposerNodeStringOperator::Append;

            string_operator_node->setOperation(operation);
        }
    }
    
    // Process node
    
    if(dtkComposerNodeProcess *process_node = dynamic_cast<dtkComposerNodeProcess *>(n)) {
        
        QDomNodeList children = node.childNodes();
        
        for(int i = 0; i < children.count(); i++) {

            if(children.at(i).toElement().tagName() != "implementation")
                continue;

            process_node->setupImplementation(children.at(i).childNodes().at(0).toText().data());
        }
    }

    // Generic node
    
    { // -- title
        
        QDomNodeList children = node.childNodes();
        
        for(int i = 0; i < children.count(); i++) {

            if(children.at(i).toElement().tagName() != "title")
                continue;

            n->setTitle(children.at(i).childNodes().at(0).toText().data());
        }
    }

    { // -- properties
        
        QDomNodeList children = node.childNodes();
        
        for(int i = 0; i < children.count(); i++) {

            if(children.at(i).toElement().tagName() != "property")
                continue;

            QString name = children.at(i).toElement().attribute("name");
            QString type = children.at(i).toElement().attribute("type");
            QString hidden = children.at(i).toElement().attribute("hidden");
            
            int p_id = -1;

            if(children.at(i).toElement().hasAttribute("id"))
                p_id = children.at(i).toElement().attribute("id").toInt();

            if(type == "input") {
                foreach(dtkComposerNodeProperty *property, n->inputProperties()) {
                    if(property->name() == name) {
                        if(p_id >= 0) {
                            if(p_id == d->node_map.key(property->clonedFrom()) && hidden == "false") {
                                property->show();
                            }
                        } else {
                            if(hidden == "true") {
                                property->hide();
                            }

                            if(hidden == "false") {
                                property->show();
                            }
                        }
                    }
                }
            }

            if(type == "output") {
                foreach(dtkComposerNodeProperty *property, n->outputProperties()) {
                    if(property->name() == name) {
                        if(p_id >= 0) {
                            if(p_id == d->node_map.key(property->clonedFrom()) && hidden == "false") {
                                property->show();
                            }
                        } else {
                            if(hidden == "true") {
                                property->hide();
                            }

                            if(hidden == "false") {
                                property->show();
                            }
                        }
                    }
                }
            }
        }
    }

    d->node_map.insert(id, n);

    return n;
}

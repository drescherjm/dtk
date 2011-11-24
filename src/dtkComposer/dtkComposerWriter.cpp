/* dtkComposerWriter.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Aug 16 15:02:49 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Nov 24 14:39:04 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 470
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
#include "dtkComposerNodeControl.h"
#include "dtkComposerNodeControlBlock.h"
#include "dtkComposerNodeFile.h"
#include "dtkComposerNodeNumber.h"
#include "dtkComposerNodeNumberComparator.h"
#include "dtkComposerNodeNumberOperator.h"
#include "dtkComposerNodeProperty.h"
#include "dtkComposerNodeProcess.h"
#include "dtkComposerNodeString.h"
#include "dtkComposerNodeStringComparator.h"
#include "dtkComposerNodeStringOperator.h"
#include "dtkComposerNote.h"
#include "dtkComposerScene.h"
#include "dtkComposerWriter.h"

#include <QtXml>

// /////////////////////////////////////////////////////////////////
// dtkComposerWriterPrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerWriterPrivate
{
public:
    dtkComposerScene *scene;

    QHash<int, dtkComposerNode *> node_ids;

    int id;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerWriter
// /////////////////////////////////////////////////////////////////

dtkComposerWriter::dtkComposerWriter(dtkComposerScene *scene) : QObject(), d(new dtkComposerWriterPrivate)
{
    d->scene = scene;
}

dtkComposerWriter::~dtkComposerWriter(void)
{
    delete d;

    d = NULL;
}

void dtkComposerWriter::write(const QString& fileName, Type type)
{
    d->node_ids.clear();
    d->id = 0;

    // Building dom document

    QDomDocument document("dtk");

    QDomElement root = document.createElement("dtk");
    document.appendChild(root);

    // -- Writing nodes

    foreach(dtkComposerNode *node, d->scene->nodes())
        if(!node->parentNode() && !node->parentItem())
            this->writeNode(node, root, document);

    // -- Writing edges

    foreach(dtkComposerEdge *edge, d->scene->edges()) {

        QDomElement source = document.createElement("source");
        source.setAttribute("node", d->node_ids.key(edge->source()->node()));
        source.setAttribute("property", edge->source()->name());
        if(edge->source()->clonedFrom())
            source.setAttribute("id", d->node_ids.key(edge->source()->clonedFrom()));
        if(!edge->source()->blockedFrom().isEmpty())
            source.setAttribute("block", edge->source()->blockedFrom());

        QDomElement destin = document.createElement("destination");
        destin.setAttribute("node", d->node_ids.key(edge->destination()->node()));
        destin.setAttribute("property", edge->destination()->name());
        if(edge->destination()->clonedFrom())
            destin.setAttribute("id", d->node_ids.key(edge->destination()->clonedFrom()));
        if(!edge->destination()->blockedFrom().isEmpty())
            destin.setAttribute("block", edge->destination()->blockedFrom());

        QDomElement tag = document.createElement("edge");
        tag.appendChild(source);
        tag.appendChild(destin);

        root.appendChild(tag);
    }

    // Writing notes

    foreach(dtkComposerNote *note, d->scene->notes()) {

        QDomText text = document.createTextNode(note->text());

        QDomElement tag = document.createElement("note");
        tag.setAttribute("x", QString::number(note->pos().x()));
        tag.setAttribute("y", QString::number(note->pos().y()));
        tag.setAttribute("w", QString::number(note->boundingRect().width()));
        tag.setAttribute("h", QString::number(note->boundingRect().height()));
        tag.appendChild(text);

        root.appendChild(tag);
    }

    // Writing file

    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly))
        return;

    if(type == dtkComposerWriter::Ascii) {
        QTextStream out(&file); out << document.toString();
    } else {
        QDataStream out(&file); out << qCompress(document.toByteArray().toHex());
    }

    file.close();
}

QDomElement dtkComposerWriter::writeNode(dtkComposerNode *node, QDomElement& element, QDomDocument& document)
{
    int current_id = d->id++;

    QDomElement tag = document.createElement("node");
    tag.setAttribute("type", node->type());
    tag.setAttribute("x", QString::number(node->pos().x()));
    tag.setAttribute("y", QString::number(node->pos().y()));
    tag.setAttribute("id", QString::number(current_id));
     
    // -- Boolean node
    
    if(dtkComposerNodeBoolean *boolean_node = dynamic_cast<dtkComposerNodeBoolean *>(node)) {
        
        bool value = boolean_node->value();
        
        QDomText text = document.createTextNode(value ? "true" : "false");
        
        QDomElement e_value = document.createElement("value");
        e_value.appendChild(text);
        
        tag.appendChild(e_value);
    }

    // -- Boolean operator node
    
    if(dtkComposerNodeBooleanOperator *boolean_operator_node = dynamic_cast<dtkComposerNodeBooleanOperator *>(node)) {
        
        dtkComposerNodeBooleanOperator::Operation operation = boolean_operator_node->operation();
        
        QDomText text;

        switch(operation) {
        case dtkComposerNodeBooleanOperator::And:
            text = document.createTextNode("and");
            break;
        case dtkComposerNodeBooleanOperator::Or:
            text = document.createTextNode("or");
            break;
        case dtkComposerNodeBooleanOperator::Xor:
            text = document.createTextNode("xor");
            break;
        case dtkComposerNodeBooleanOperator::Nand:
            text = document.createTextNode("nand");
            break;
        case dtkComposerNodeBooleanOperator::Nor:
            text = document.createTextNode("nor");
            break;
        case dtkComposerNodeBooleanOperator::Xnor:
            text = document.createTextNode("xnor");
            break;
        case dtkComposerNodeBooleanOperator::Imp:
            text = document.createTextNode("imp");
            break;
        case dtkComposerNodeBooleanOperator::Nimp:
            text = document.createTextNode("nimp");
            break;
        default:
            break;
        }
        
        QDomElement e_operation = document.createElement("operation");
        e_operation.appendChild(text);
        
        tag.appendChild(e_operation);
    }
     
    // -- Number node
    
    if(dtkComposerNodeNumber *number_node = dynamic_cast<dtkComposerNodeNumber *>(node)) {

        number_node->touch(); // enables to update text in edition aera.

        QDomText text = document.createTextNode(number_node->editorText());        
        QDomElement e_value = document.createElement("value");
        e_value.appendChild(text);        
        tag.appendChild(e_value);
    }

    // -- Number comparator node
    
    if(dtkComposerNodeNumberComparator *number_comparator_node = dynamic_cast<dtkComposerNodeNumberComparator *>(node)) {
        
        dtkComposerNodeNumberComparator::Operation operation = number_comparator_node->operation();
        
        QDomText text;

        switch(operation) {
        case dtkComposerNodeNumberComparator::LesserThan:
            text = document.createTextNode("<");
            break;
        case dtkComposerNodeNumberComparator::LesserThanOrEqual:
            text = document.createTextNode("<=");
            break;
        case dtkComposerNodeNumberComparator::GreaterThan:
            text = document.createTextNode(">");
            break;
        case dtkComposerNodeNumberComparator::GreaterThanOrEqual:
            text = document.createTextNode(">=");
            break;
        case dtkComposerNodeNumberComparator::Equal:
            text = document.createTextNode("==");
            break;
        case dtkComposerNodeNumberComparator::Differ:
            text = document.createTextNode("!=");
            break;
        default:
            break;
        }
        
        QDomElement e_operation = document.createElement("operation");
        e_operation.appendChild(text);
        
        tag.appendChild(e_operation);
    }

    // -- Number operator node
    
    if(dtkComposerNodeNumberOperator *number_operator_node = dynamic_cast<dtkComposerNodeNumberOperator *>(node)) {
        
        dtkComposerNodeNumberOperator::Operation operation = number_operator_node->operation();
        
        QDomText text;

        switch(operation) {
        case dtkComposerNodeNumberOperator::Addition:
            text = document.createTextNode("+");
            break;
        case dtkComposerNodeNumberOperator::Substraction:
            text = document.createTextNode("-");
            break;
        case dtkComposerNodeNumberOperator::Multiplication:
            text = document.createTextNode("x");
            break;
        case dtkComposerNodeNumberOperator::Division:
            text = document.createTextNode("/");
            break;
        case dtkComposerNodeNumberOperator::Increment:
            text = document.createTextNode("++");
            break;
        case dtkComposerNodeNumberOperator::Decrement:
            text = document.createTextNode("--");
            break;
        case dtkComposerNodeNumberOperator::Modulo:
            text = document.createTextNode("%");
            break;
        case dtkComposerNodeNumberOperator::Min:
            text = document.createTextNode("MIN");
            break;
        case dtkComposerNodeNumberOperator::Max:
            text = document.createTextNode("MAX");
            break;
        default:
            break;
        }
        
        QDomElement e_operation = document.createElement("operation");
        e_operation.appendChild(text);
        
        tag.appendChild(e_operation);
    }

    // -- File node
    
    if(dtkComposerNodeFile *file_node = dynamic_cast<dtkComposerNodeFile *>(node)) {
        
        QUrl file_url = file_node->url();

        QString file_name = file_node->name();

        if(!file_url.isEmpty() && file_url.isValid()) {

            QDomText text = document.createTextNode(file_url.toString());
            
            QDomElement url = document.createElement("url");
            url.appendChild(text);
            
            tag.appendChild(url);

        } else if(!file_name.isEmpty()) {
            
            QDomText text = document.createTextNode(file_name);
            
            QDomElement name = document.createElement("name");
            name.appendChild(text);
            
            tag.appendChild(name);
        }
    }

    // -- String node
    
    if(dtkComposerNodeString *string_node = dynamic_cast<dtkComposerNodeString *>(node)) {
        
        QString value = string_node->value();
        
        QDomText text = document.createTextNode(value);
        
        QDomElement e_value = document.createElement("value");
        e_value.appendChild(text);
        
        tag.appendChild(e_value);
    }

    // -- String comparator node
    
    if(dtkComposerNodeStringComparator *string_comparator_node = dynamic_cast<dtkComposerNodeStringComparator *>(node)) {
        
        dtkComposerNodeStringComparator::Operation operation = string_comparator_node->operation();
        
        QDomText text;

        switch(operation) {
        case dtkComposerNodeStringComparator::LesserThan:
            text = document.createTextNode("<");
            break;
        case dtkComposerNodeStringComparator::LesserThanOrEqual:
            text = document.createTextNode("<=");
            break;
        case dtkComposerNodeStringComparator::GreaterThan:
            text = document.createTextNode(">");
            break;
        case dtkComposerNodeStringComparator::GreaterThanOrEqual:
            text = document.createTextNode(">=");
            break;
        case dtkComposerNodeStringComparator::Equal:
            text = document.createTextNode("==");
            break;
        case dtkComposerNodeStringComparator::Differ:
            text = document.createTextNode("!=");
            break;
        default:
            break;
        }
        
        QDomElement e_operation = document.createElement("operation");
        e_operation.appendChild(text);
        
        tag.appendChild(e_operation);
    }

    // -- String operator node
    
    if(dtkComposerNodeStringOperator *string_operator_node = dynamic_cast<dtkComposerNodeStringOperator *>(node)) {
        
        dtkComposerNodeStringOperator::Operation operation = string_operator_node->operation();
        
        QDomText text;

        switch(operation) {
        case dtkComposerNodeStringOperator::Append:
            text = document.createTextNode("<<");
            break;
        case dtkComposerNodeStringOperator::Prepend:
            text = document.createTextNode(">>");
            break;
        default:
            break;
        }
        
        QDomElement e_operation = document.createElement("operation");
        e_operation.appendChild(text);
        
        tag.appendChild(e_operation);
    }
    
    // -- Process node
    
    if(dtkComposerNodeProcess *process_node = dynamic_cast<dtkComposerNodeProcess *>(node)) {
        
        QString implementation = process_node->implementation();
        
        if(!implementation.isEmpty()) {
            
            QDomText text = document.createTextNode(implementation);
            
            QDomElement implementation = document.createElement("implementation");
            implementation.appendChild(text);
            
            tag.appendChild(implementation);
        }
    }

    // -- Control node
    
    if(dtkComposerNodeControl *control_node = dynamic_cast<dtkComposerNodeControl *>(node)) {
        
        tag.setAttribute("w", QString::number(control_node->boundingRect().width()));
        tag.setAttribute("h", QString::number(control_node->boundingRect().height()));

        foreach(dtkComposerNodeControlBlock *block, control_node->blocks()) {
            
            QDomElement block_element = document.createElement("block");
            block_element.setAttribute("title", block->title());
            block_element.setAttribute("h", QString::number(block->height()));

            foreach(dtkComposerNode *block_node, block->nodes())
                this->writeNode(block_node, block_element, document);

            tag.appendChild(block_element);
        }
    }
    
    // -- Composite node
    
    if(node->kind() == dtkComposerNode::Composite) {
        foreach(dtkComposerNode *child, node->childNodes())
            this->writeNode(child, tag, document);
    }
    
    { // -- Generic node
        
        { // -- title
            
            QString node_title = node->title();
            
            QDomText text = document.createTextNode(node_title);
            
            QDomElement title = document.createElement("title");
            title.appendChild(text);
            
            tag.appendChild(title);
        }

        { // -- properties

            foreach(dtkComposerNodeProperty *property, node->g->leftProperties()) {
                
                QDomElement property_element = document.createElement("property");
                property_element.setAttribute("name", property->name());
                switch (property->type()) {
                case dtkComposerNodeProperty::Generic:
                    property_element.setAttribute("type", "generic");
                    property_element.setAttribute("position", "left");
                    switch (property->behavior()) {
                    case dtkComposerNodeProperty::AsInput:
                        property_element.setAttribute("behavior", "asinput");
                        break;
                    case dtkComposerNodeProperty::AsOutput:
                        property_element.setAttribute("behavior", "asoutput");
                        break;
                    case dtkComposerNodeProperty::AsRelay:
                        property_element.setAttribute("behavior", "asrelay");
                        break;
                    case dtkComposerNodeProperty::AsLoop:
                        property_element.setAttribute("behavior", "asloop");
                        break;
                    }
                    switch (property->multiplicity()) {
                    case dtkComposerNodeProperty::Null:
                        property_element.setAttribute("multiplicity", "null");
                        break;
                    case dtkComposerNodeProperty::Single:
                        property_element.setAttribute("multiplicity", "single");
                        break;
                    case dtkComposerNodeProperty::Multiple:
                        property_element.setAttribute("multiplicity", "multiple");
                        break;
                    }
                    break;
                case dtkComposerNodeProperty::Input:
                    property_element.setAttribute("type", "input");
                    break;
                case dtkComposerNodeProperty::HybridInput:
                    property_element.setAttribute("type", "hybridinput");
                    break;
                case dtkComposerNodeProperty::HybridOutput:
                    break;
                case dtkComposerNodeProperty::PassThroughInput:
                    property_element.setAttribute("type", "passthroughinput");
                    break;
                case dtkComposerNodeProperty::PassThroughOutput:
                        break;
                case dtkComposerNodeProperty::Output:
                    property_element.setAttribute("type", "passthroughinput");
                    break;
                }
                property_element.setAttribute("hidden", property->isDisplayed() ? "false" : "true");
                if(node->kind() == dtkComposerNode::Composite)
                    property_element.setAttribute("id", d->node_ids.key(property->clonedFrom()));
                if(node->kind() == dtkComposerNode::Control && !property->blockedFrom().isEmpty())
                    property_element.setAttribute("block", property->blockedFrom());
                tag.appendChild(property_element);
            }

            foreach(dtkComposerNodeProperty *property, node->g->rightProperties()) {
                
                QDomElement property_element = document.createElement("property");
                property_element.setAttribute("name", property->name());
                switch (property->type()) {
                case dtkComposerNodeProperty::Generic:
                    property_element.setAttribute("type", "generic");
                    property_element.setAttribute("position", "right");
                    switch (property->behavior()) {
                    case dtkComposerNodeProperty::AsInput:
                        property_element.setAttribute("behavior", "asinput");
                        break;
                    case dtkComposerNodeProperty::AsOutput:
                        property_element.setAttribute("behavior", "asoutput");
                        break;
                    case dtkComposerNodeProperty::AsRelay:
                        property_element.setAttribute("behavior", "asrelay");
                        break;
                    case dtkComposerNodeProperty::AsLoop:
                        property_element.setAttribute("behavior", "asloop");
                        break;
                    }
                    switch (property->multiplicity()) {
                    case dtkComposerNodeProperty::Null:
                        property_element.setAttribute("multiplicity", "null");
                        break;
                    case dtkComposerNodeProperty::Single:
                        property_element.setAttribute("multiplicity", "single");
                        break;
                    case dtkComposerNodeProperty::Multiple:
                        property_element.setAttribute("multiplicity", "multiple");
                        break;
                    }
                    break;
                case dtkComposerNodeProperty::Input:
                    break;
                case dtkComposerNodeProperty::Output:
                    property_element.setAttribute("type", "output");
                    break;
                case dtkComposerNodeProperty::HybridInput:
                    break;
                case dtkComposerNodeProperty::HybridOutput:
                    property_element.setAttribute("type", "hybridoutput");
                    break;
                case dtkComposerNodeProperty::PassThroughInput:
                    break;
                case dtkComposerNodeProperty::PassThroughOutput:
                    property_element.setAttribute("type", "passthroughoutput");
                    break;
                }
                property_element.setAttribute("hidden", property->isDisplayed() ? "false" : "true");
                if(node->kind() == dtkComposerNode::Composite)
                    property_element.setAttribute("id", d->node_ids.key(property->clonedFrom()));
                if(node->kind() == dtkComposerNode::Control && !property->blockedFrom().isEmpty())
                    property_element.setAttribute("block", property->blockedFrom());
                tag.appendChild(property_element);
            }
        }

        { // -- Attributes

            QString node_attribute;

            if(node->attribute() == dtkComposerNode::Sequential)
                node_attribute = "sequential";
            
            if(node->attribute() == dtkComposerNode::Parallel)
                node_attribute = "parallel";

            QDomText text = document.createTextNode(node_attribute);
            
            QDomElement title = document.createElement("attribute");
            title.appendChild(text);
            
            tag.appendChild(title);

        }
    }

    // --
    
    element.appendChild(tag);
    
    d->node_ids.insert(current_id, node);

    this->extend(node, tag, document);

    return tag;
}

void dtkComposerWriter::extend(dtkComposerNode *node, QDomElement& element, QDomDocument& document)
{
    Q_UNUSED(node);
    Q_UNUSED(element);
    Q_UNUSED(document);
}

/* dtkComposerNodeGraphic.cpp --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Thu Nov  3 13:28:33 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Nov  4 14:34:00 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 108
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeGraphic.h"

#include "dtkComposerEdge.h"
#include "dtkComposerNode.h"
#include "dtkComposerNodeProperty.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeGraphicPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeGraphicPrivate
{
public:
    QList<dtkComposerEdge *>  leftRoute(dtkComposerEdge *edge);
    QList<dtkComposerEdge *> rightRoute(dtkComposerEdge *edge);

public:
    QList<dtkComposerNodeProperty *>  left_properties;
    QList<dtkComposerNodeProperty *> right_properties;

    QList<dtkComposerEdge *>  left_edges;
    QList<dtkComposerEdge *> right_edges;

    QList<dtkComposerEdge *>  left_relay_edges;
    QList<dtkComposerEdge *> right_relay_edges;

    // -- Following vectors enable to map edges to property (QHash would be redundant in this case)

    QVector<dtkComposerNodeProperty *>   left_edges_to_left_property;
    QVector<dtkComposerNodeProperty *> right_edges_to_right_property;

    QVector<dtkComposerNodeProperty *>   left_relay_edges_to_left_property;
    QVector<dtkComposerNodeProperty *> right_relay_edges_to_right_property;

public:
    dtkComposerNode *node;
    // dtkComposerNode *parent;
    // QList<dtkComposerNode *> children;
    
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeGraphicPrivate implementation
// /////////////////////////////////////////////////////////////////

//! Computes potential left routes related to \a edge.
/*! 
 *  Three cases can occur:
 *
 *  - the source node is not a composite, the route is then the same than the edge.
 *
 *  - the source node is a composite, then two cases remain to distinct:
 *
 *    + the composite is the parent of the destination node, then all
 *    left edges of the composite connected to the source property of
 *    \a edge would likely provide left routes, so the same method is
 *    reccursively applied to them.
 *
 *    + the composite is not the parent of the destination node, then
 *    all right relay edges connected to the source property of \a
 *    edge would likely provide left routes, so the same method is
 *    reccursively applied to them.
 */
QList<dtkComposerEdge *> dtkComposerNodeGraphicPrivate::leftRoute(dtkComposerEdge *edge)
{
    QList<dtkComposerEdge *> edges;

    if (edge->source()->node()->kind() != dtkComposerNode::Composite) {

        // qDebug() << DTK_COLOR_BG_WHITE << DTK_PRETTY_FUNCTION << edge->source()->node()->title() << "is not composite" << DTK_NO_COLOR;

        edges << edge;

    } else {

        if (edge->source()->node() == edge->destination()->node()->parentNode()) {

            // qDebug() << DTK_COLOR_BG_WHITE << DTK_PRETTY_FUNCTION << edge->source()->node()->title() << "parent is composite" << DTK_NO_COLOR;

            foreach(dtkComposerEdge *l_edge, edge->source()->node()->g->leftEdges())
                if (l_edge->destination() == edge->source())
                    edges << this->leftRoute(l_edge);
        } else {

            // qDebug() << DTK_COLOR_BG_WHITE << DTK_PRETTY_FUNCTION << edge->source()->node()->title() << "source is composite" << DTK_NO_COLOR;

            foreach(dtkComposerEdge *relay, edge->source()->node()->g->rightRelayEdges())
                if (relay->destination() == edge->source())
                    edges << this->leftRoute(relay);
        }
    }

    return edges;
}

//! Computes potential right routes related to \a edge.
/*! 
 *  Three cases can occur:
 *
 *  - the destination node is not a composite, the route is then the same than the edge.
 *
 *  - the destination node is a composite, then two cases remain to distinct:
 *
 *    + the composite is the parent of the source node, then all
 *    right edges of the composite connected to the destination
 *    property of \a edge would likely provide right routes, so the
 *    same method is reccursively applied to them.
 *
 *    + the composite is not the parent of the source node, then all
 *    left relay edges connected to the destination property of \a
 *    edge would likely provide right routes, so the same method is
 *    reccursively applied to them.
 */
QList<dtkComposerEdge *> dtkComposerNodeGraphicPrivate::rightRoute(dtkComposerEdge *edge)
{
    QList<dtkComposerEdge *> edges;

    if (edge->destination()->node()->kind() != dtkComposerNode::Composite) {

        // qDebug() << DTK_COLOR_BG_WHITE << DTK_PRETTY_FUNCTION << edge->destination()->node()->title() << "is not composite" << DTK_NO_COLOR;

        edges << edge;

    } else {

        if (edge->destination()->node() == edge->source()->node()->parentNode()) {

            // qDebug() << DTK_COLOR_BG_WHITE << DTK_PRETTY_FUNCTION << edge->destination()->node()->title() << "parent is composite" << DTK_NO_COLOR;

            foreach(dtkComposerEdge *r_edge, edge->destination()->node()->g->rightEdges())
                if (r_edge->source() == edge->destination())
                    edges << this->rightRoute(r_edge);

        } else {

            // qDebug() << DTK_COLOR_BG_WHITE << DTK_PRETTY_FUNCTION << edge->destination()->node()->title() << "destination is composite" << DTK_NO_COLOR;

            foreach(dtkComposerEdge *relay, edge->destination()->node()->g->leftRelayEdges())
                if (relay->source() == edge->destination())
                    edges << this->rightRoute(relay);

        }
    }

    return edges;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeGraphic implementation
// /////////////////////////////////////////////////////////////////

//! Constructs dtkComposerNodeGraphic.
/*! 
 *  
 */
dtkComposerNodeGraphic::dtkComposerNodeGraphic(dtkComposerNode *node) : QObject(node), d(new dtkComposerNodeGraphicPrivate)
{
    d->node = node;
}

//! Destroys dtkComposerNodeGraphic.
/*! 
 *  
 */
dtkComposerNodeGraphic::~dtkComposerNodeGraphic(void)
{
    delete d;
    d = NULL;
}

//! Return pointer to the owner node.
/*! 
 *  
 */
dtkComposerNode *dtkComposerNodeGraphic::node(void)
{
    return d->node;
}

//! Appends \a property in list of left properties
/*! 
 *  
 */
void dtkComposerNodeGraphic::appendLeftProperty(dtkComposerNodeProperty *property)
{
    if (d->left_properties.contains(property))
        return;

    d->left_properties << property;
}

//! Appends \a property in list of right properties
/*! 
 *  
 */
void dtkComposerNodeGraphic::appendRightProperty(dtkComposerNodeProperty *property)
{
    if (d->right_properties.contains(property))
        return;

    d->right_properties << property;
}

//! Removes \a property from list of left properties
/*! 
 *  
 */
void dtkComposerNodeGraphic::removeLeftProperty(dtkComposerNodeProperty *property)
{
    d->left_properties.removeAll(property);
}

//! Removes \a property from list of right properties
/*! 
 *  
 */
void dtkComposerNodeGraphic::removeRightProperty(dtkComposerNodeProperty *property)
{
    d->right_properties.removeAll(property);
}

//! Clears left and right lists of properties
/*! 
 *  
 */
void dtkComposerNodeGraphic::removeAllProperties(void)
{
    d->left_properties.clear();
    d->right_properties.clear();
}

//! Appends \a edge connected to \a property to the list of left edges.
/*! 
 *  The map connected left edges to left properties is updated.
 */
void dtkComposerNodeGraphic::appendLeftEdge(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    if (d->left_edges.contains(edge))
        return;

    d->left_edges << edge;
    d->left_edges_to_left_property << property;
}

//! Appends \a edge connected to \a property to the list of right edges.
/*! 
 *  The map connected right edges to right properties is updated.
 */
void dtkComposerNodeGraphic::appendRightEdge(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    if (d->right_edges.contains(edge))
        return;

    d->right_edges << edge;
    d->right_edges_to_right_property << property;
}

//! Removes \a edge from the list of left edges.
/*! 
 *  The map connected left edges to left properties is updated.
 */
void dtkComposerNodeGraphic::removeLeftEdge(dtkComposerEdge *edge)
{
    d->left_edges_to_left_property.remove(d->left_edges.indexOf(edge));
    d->left_edges.removeAll(edge);
}

//! Removes \a edge from the list of right edges.
/*! 
 *  The map connected right edges to right properties is updated.
 */
void dtkComposerNodeGraphic::removeRightEdge(dtkComposerEdge *edge)
{
    d->right_edges_to_right_property.remove(d->right_edges.indexOf(edge));
    d->right_edges.removeAll(edge);
}

//! Clears left and right lists of edges.
/*! 
 *  Related maps are also cleared.
 */
void dtkComposerNodeGraphic::removeAllEdges(void)
{
    d->left_edges_to_left_property.clear();
    d->left_edges.clear();

    d->right_edges_to_right_property.clear();
    d->right_edges.clear();
}

//! Appends \a edge connected to \a property to the list of left relay edges.
/*! 
 *  The map connected left relay edges to left properties is updated.
 */
void dtkComposerNodeGraphic::appendLeftRelayEdge(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    if (d->left_relay_edges.contains(edge))
        return;

    d->left_relay_edges << edge;
    d->left_relay_edges_to_left_property << property;
}

//! Appends \a edge connected to \a property to the list of right relay edges.
/*! 
 *  The map connected right relay edges to right properties is updated.
 */
void dtkComposerNodeGraphic::appendRightRelayEdge(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    if (d->right_relay_edges.contains(edge))
        return;

    d->right_relay_edges << edge;
    d->right_relay_edges_to_right_property << property;
}

//! Removes \a edge from the list of left relay edges.
/*! 
 *  The map connected left relay edges to left properties is updated.
 */
void dtkComposerNodeGraphic::removeLeftRelayEdge(dtkComposerEdge *edge)
{
    d->left_relay_edges_to_left_property.remove(d->left_relay_edges.indexOf(edge));
    d->left_relay_edges.removeAll(edge);
}

//! Removes \a edge from the list of right relay edges.
/*! 
 *  The map connected right relay edges to right properties is updated.
 */
void dtkComposerNodeGraphic::removeRightRelayEdge(dtkComposerEdge *edge)
{
    d->right_relay_edges_to_right_property.remove(d->right_relay_edges.indexOf(edge));
    d->right_relay_edges.removeAll(edge);
}

//! Clears lists of left and right relay edges.
/*! 
 *  Related maps are also cleared.
 */
void dtkComposerNodeGraphic::removeAllRelayEdges(void)
{
    d->left_relay_edges_to_left_property.clear();
    d->left_relay_edges.clear();

    d->right_relay_edges_to_right_property.clear();
    d->right_relay_edges.clear();
}

//! Returns left property identified by its \a name.
/*! 
 *  Returns NULL if not found.
 */
dtkComposerNodeProperty *dtkComposerNodeGraphic::leftProperty(const QString& name) const
{
    foreach(dtkComposerNodeProperty *property, d->left_properties)
        if (property->name() == name)
            return property;

    return NULL;
}

//! Returns right property identified by its \a name.
/*! 
 *  Returns NULL if not found.
 */
dtkComposerNodeProperty *dtkComposerNodeGraphic::rightProperty(const QString& name) const
{
    foreach(dtkComposerNodeProperty *property, d->right_properties)
        if (property->name() == name)
            return property;

    return NULL;
}

//! Returns list of left properties.
/*! 
 *  
 */
const QList<dtkComposerNodeProperty *>& dtkComposerNodeGraphic::leftProperties(void) const
{
    return d->left_properties;
}

//! Returns list of right properties.
/*! 
 *  
 */
const QList<dtkComposerNodeProperty *>& dtkComposerNodeGraphic::rightProperties(void) const
{
    return d->right_properties;
}

//! Returns list of left edges.
/*! 
 *  
 */
const QList<dtkComposerEdge *>& dtkComposerNodeGraphic::leftEdges(void) const
{
    return d->left_edges;
}

//! Returns list of right edges.
/*! 
 *  
 */
const QList<dtkComposerEdge *>& dtkComposerNodeGraphic::rightEdges(void) const
{
    return d->right_edges;
}

//! Returns list of left relay edges.
/*! 
 *  
 */
const QList<dtkComposerEdge *>& dtkComposerNodeGraphic::leftRelayEdges(void) const
{
    return d->left_relay_edges;
}

//! Returns list of right relay edges.
/*! 
 *  
 */
const QList<dtkComposerEdge *>& dtkComposerNodeGraphic::rightRelayEdges(void) const
{
    return d->right_relay_edges;
}

//! Returns the number of edges connected to \a property.
/*! 
 *  
 */
int dtkComposerNodeGraphic::edgeCount(dtkComposerNodeProperty *property) const
{
    int edge_count = 0;

    if (d->left_properties.contains(property)) {

        foreach(dtkComposerNodeProperty *pp, d->left_edges_to_left_property) {
            if (property == pp)
                edge_count++;
        }

        foreach(dtkComposerNodeProperty *pp, d->left_relay_edges_to_left_property) {
            if (property == pp)
                edge_count++;
        }

    } else if (d->right_properties.contains(property)) {

        foreach(dtkComposerNodeProperty *pp, d->right_edges_to_right_property) {
            if (property == pp)
                edge_count++;
        }

        foreach(dtkComposerNodeProperty *pp, d->right_relay_edges_to_right_property) {
            if (property == pp)
                edge_count++;
        }
        
    }

    return edge_count;
}

//! Returns the index position of \a property in the lists of
//! properties. Returns -1 if no item match.
/*! 
 *  The research is performed in lists of left and right properties.
 */
int dtkComposerNodeGraphic::indexOf(dtkComposerNodeProperty *property) const
{
    int index = 1;

    index +=  d->left_properties.indexOf(property);
    index += d->right_properties.indexOf(property);

    return index;
}

// //! 
// /*! 
//  *  
//  */
// int dtkComposerNodeGraphic::onEdgeConnected(dtkComposerEdge *edge)
// {
    
// }

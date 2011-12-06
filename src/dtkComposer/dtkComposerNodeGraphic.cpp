/* dtkComposerNodeGraphic.cpp --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Thu Nov  3 13:28:33 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Dec  6 13:56:47 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 386
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
#include "dtkComposerNodeControl.h"
#include "dtkComposerNodeProperty.h"

#include <dtkCore/dtkGlobal>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeGraphicPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeGraphicPrivate
{
public:
    typedef QPair<dtkComposerNodeProperty *, dtkComposerNodeProperty *> Route;
    typedef QMultiHash<dtkComposerNodeProperty *, dtkComposerEdge *> EdgesToProperty;
    typedef QHash<Route, QList<dtkComposerEdge *> > EdgesAlongRoutes;

public:
    EdgesToProperty  leftRoute(dtkComposerEdge *edge, QList<dtkComposerEdge *>& list);
    EdgesToProperty rightRoute(dtkComposerEdge *edge, QList<dtkComposerEdge *>& list);

    EdgesAlongRoutes edgesAlongRoutes(dtkComposerEdge *edge);

public:
    dtkComposerEdge  *leftEdge(dtkComposerNodeProperty *property);
    dtkComposerEdge *rightEdge(dtkComposerNodeProperty *property);

    dtkComposerEdge  *leftRelayEdge(dtkComposerNodeProperty *property);
    dtkComposerEdge *rightRelayEdge(dtkComposerNodeProperty *property);

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
dtkComposerNodeGraphicPrivate::EdgesToProperty dtkComposerNodeGraphicPrivate::leftRoute(dtkComposerEdge *edge, QList<dtkComposerEdge *>& list)
{
    dtkComposerNodeGraphicPrivate::EdgesToProperty map_edges_to_property;

    if (edge->source()->node()->kind() != dtkComposerNode::Composite) {

        map_edges_to_property.insert(edge->source(), edge);

        foreach(dtkComposerEdge *e, list)
            map_edges_to_property.insert(edge->source(), e);

    } else {

        list << edge;

        if (edge->source()->node() == edge->destination()->node()->parentNode()) {

            foreach(dtkComposerEdge *l_edge, edge->source()->node()->g->leftEdges()) {
                if (l_edge->destination() == edge->source())
                    map_edges_to_property += this->leftRoute(l_edge, list);
            }

        } else {

            foreach(dtkComposerEdge *relay, edge->source()->node()->g->rightRelayEdges()) {
                if (relay->destination() == edge->source())
                    map_edges_to_property += this->leftRoute(relay, list);                    
            }
        }
    }

    return map_edges_to_property;
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
dtkComposerNodeGraphicPrivate::EdgesToProperty dtkComposerNodeGraphicPrivate::rightRoute(dtkComposerEdge *edge, QList<dtkComposerEdge *>& list)
{
    dtkComposerNodeGraphicPrivate::EdgesToProperty map_edges_to_property;

    if (edge->destination()->node()->kind() != dtkComposerNode::Composite) {

        map_edges_to_property.insert(edge->destination(), edge);

        foreach(dtkComposerEdge *e, list)
            map_edges_to_property.insert(edge->destination(), e);

    } else {

        list << edge;

        if (edge->destination()->node() == edge->source()->node()->parentNode()) {

            foreach(dtkComposerEdge *r_edge, edge->destination()->node()->g->rightEdges()) {
                if (r_edge->source() == edge->destination())
                    map_edges_to_property += this->rightRoute(r_edge, list);
            }

        } else {
                
            foreach(dtkComposerEdge *relay, edge->destination()->node()->g->leftRelayEdges()) {
                if (relay->source() == edge->destination())
                    map_edges_to_property += this->rightRoute(relay, list);               
            }
        }        
    }

    return map_edges_to_property;
}

//! 
/*! 
 *  
 */
dtkComposerNodeGraphicPrivate::EdgesAlongRoutes dtkComposerNodeGraphicPrivate::edgesAlongRoutes(dtkComposerEdge *edge)
{
    dtkComposerNodeGraphicPrivate::EdgesAlongRoutes map;

    QList<dtkComposerEdge *> list;

    dtkComposerNodeGraphicPrivate::EdgesToProperty  left_map =  this->leftRoute(edge, list);
    dtkComposerNodeGraphicPrivate::EdgesToProperty right_map = this->rightRoute(edge, list);

    foreach(dtkComposerNodeProperty *source, left_map.uniqueKeys()) {
        foreach(dtkComposerNodeProperty *destin, right_map.uniqueKeys()) {

            QList<dtkComposerEdge *> edges_along_route;
            foreach(dtkComposerEdge *e, left_map.values(source))
                if(!edges_along_route.contains(e))
                    edges_along_route << e;

            foreach(dtkComposerEdge *e, right_map.values(destin))
                if(!edges_along_route.contains(e))
                    edges_along_route << e;

            map.insert(qMakePair(source, destin), edges_along_route);
        }
    }

    return map;
}

//! Returns the last left edge connected to \a property.
/*! 
 *  Returns NULL, when no edge is connected to \a property.
 */
dtkComposerEdge *dtkComposerNodeGraphicPrivate::leftEdge(dtkComposerNodeProperty *property)
{
    int index = this->left_edges_to_left_property.lastIndexOf(property);

    if (index < 0)
        return NULL;

    return this->left_edges.at(index);
}

//! Returns the last right edge connected to \a property.
/*! 
 *  Returns NULL, when no edge is connected to \a property.
 */
dtkComposerEdge *dtkComposerNodeGraphicPrivate::rightEdge(dtkComposerNodeProperty *property)
{
    int index = this->right_edges_to_right_property.lastIndexOf(property);

    if (index < 0)
        return NULL;

    return this->right_edges.at(index);
}

//! Returns the last left relay edge connected to \a property.
/*! 
 *  Returns NULL, when no edge is connected to \a property.
 */
dtkComposerEdge *dtkComposerNodeGraphicPrivate::leftRelayEdge(dtkComposerNodeProperty *property)
{
    int index = this->left_relay_edges_to_left_property.lastIndexOf(property);

    if (index < 0)
        return NULL;

    return this->left_relay_edges.at(index);
}

//! Returns the last right relay edge connected to \a property.
/*! 
 *  Returns NULL, when no edge is connected to \a property.
 */
dtkComposerEdge *dtkComposerNodeGraphicPrivate::rightRelayEdge(dtkComposerNodeProperty *property)
{
    int index = this->right_relay_edges_to_right_property.lastIndexOf(property);

    if (index < 0)
        return NULL;

    return  this->right_relay_edges.at(index);
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
 *  Owner node layout is also updated.
 */
void dtkComposerNodeGraphic::appendLeftProperty(dtkComposerNodeProperty *property)
{
    if (d->left_properties.contains(property))
        return;

    d->left_properties << property;

    d->node->layout();
}

//! Appends \a property in list of right properties
/*! 
 *  Owner node layout is also updated.
 */
void dtkComposerNodeGraphic::appendRightProperty(dtkComposerNodeProperty *property)
{
    if (d->right_properties.contains(property))
        return;

    d->right_properties << property;

    d->node->layout();
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
    int index = d->left_edges.indexOf(edge);
    if (index < 0) {
        qDebug() << "Edge" << edge << "is no more in the list. Bad use of " << DTK_PRETTY_FUNCTION;
        return;
    }

    d->left_edges_to_left_property.remove(index);
    d->left_edges.removeAll(edge);
}

//! Removes \a edge from the list of right edges.
/*! 
 *  The map connected right edges to right properties is updated.
 */
void dtkComposerNodeGraphic::removeRightEdge(dtkComposerEdge *edge)
{
    int index = d->right_edges.indexOf(edge);
    if (index < 0) {
        qDebug() << "Edge" << edge << "is no more in the list. Bad use of " << DTK_PRETTY_FUNCTION;
        return;
    }

    d->right_edges_to_right_property.remove(index);
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
    int index = d->left_relay_edges.indexOf(edge);
    if (index < 0) {
        qDebug() << "Edge" << edge << "is no more in the list. Bad use of " << DTK_PRETTY_FUNCTION;
        return;
    }

    d->left_relay_edges_to_left_property.remove(index);
    d->left_relay_edges.removeAll(edge);
}

//! Removes \a edge from the list of right relay edges.
/*! 
 *  The map connected right relay edges to right properties is updated.
 */
void dtkComposerNodeGraphic::removeRightRelayEdge(dtkComposerEdge *edge)
{
    int index = d->right_relay_edges.indexOf(edge);
    if (index < 0) {
        qDebug() << "Edge" << edge << "is no more in the list. Bad use of " << DTK_PRETTY_FUNCTION;
        return;
    }

    d->right_relay_edges_to_right_property.remove(index);
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

//! Returns last left edge connected to \a property.
/*! 
 *  Returns NULL, when no edge has been found.
 */
dtkComposerEdge *dtkComposerNodeGraphic::leftEdge(dtkComposerNodeProperty *property) const
{
    return d->leftEdge(property);
}

//! Returns last right edge connected to \a property.
/*! 
 *  Returns NULL, when no edge has been found.
 */
dtkComposerEdge *dtkComposerNodeGraphic::rightEdge(dtkComposerNodeProperty *property) const
{
    return d->rightEdge(property);
}

//! Returns last left relay edge connected to \a property.
/*! 
 *  Returns NULL, when no edge has been found.
 */
dtkComposerEdge *dtkComposerNodeGraphic::leftRelayEdge(dtkComposerNodeProperty *property) const
{
    return d->leftRelayEdge(property);
}

//! Returns last right relay edge connected to \a property.
/*! 
 *  Returns NULL, when no edge has been found.
 */
dtkComposerEdge *dtkComposerNodeGraphic::rightRelayEdge(dtkComposerNodeProperty *property) const
{
    return d->rightRelayEdge(property);
}

//! Returns last edge connected to \a property.
/*! 
 *  Returns NULL, when no edge has been found.
 */
dtkComposerEdge *dtkComposerNodeGraphic::edge(dtkComposerNodeProperty *property) const
{
    dtkComposerEdge *edge = NULL;
    
    if (d->node->kind() != dtkComposerNode::Composite) {

        if (property->type() == dtkComposerNodeProperty::Generic) {

            if (property->position() == dtkComposerNodeProperty::Left) {

                if (property->behavior() == dtkComposerNodeProperty::AsInput)
                    edge = d->leftEdge(property);
                else
                    edge = d->leftRelayEdge(property);

            } else if (property->position() == dtkComposerNodeProperty::Right) {

                if (property->behavior() == dtkComposerNodeProperty::AsOutput)
                    edge = d->rightEdge(property);
                else
                    edge = d->rightRelayEdge(property);
            }

        } else if (property->type() == dtkComposerNodeProperty::Input && property->behavior() == dtkComposerNodeProperty::AsLoopOutput) {
             edge = d->rightRelayEdge(property);

         } else if (property->type() == dtkComposerNodeProperty::Input) {
             edge = d->leftEdge(property);

         } else if (property->type() == dtkComposerNodeProperty::HybridInput || property->type() == dtkComposerNodeProperty::PassThroughInput) {
             if (property->behavior() == dtkComposerNodeProperty::AsInput)
                 edge = d->leftEdge(property);
             else if (property->behavior() == dtkComposerNodeProperty::AsRelay)
                 edge = d->leftRelayEdge(property);
        
        } else if (property->type() == dtkComposerNodeProperty::Output) {
                 edge = d->rightEdge(property);

         } else if (property->type() == dtkComposerNodeProperty::HybridOutput || property->type() == dtkComposerNodeProperty::PassThroughOutput) {
             if (property->behavior() == dtkComposerNodeProperty::AsRelay)
                 edge = d->rightRelayEdge(property);
             else if (property->behavior() == dtkComposerNodeProperty::AsOutput)
                 edge = d->rightEdge(property);

         }
    } else {

        if (property->type() == dtkComposerNodeProperty::Input) {
            if (d->node->isGhost())            
                edge = d->leftRelayEdge(property);
            else
                edge = d->leftEdge(property);
        }
        
        if (property->type() == dtkComposerNodeProperty::Output) {
            if (d->node->isGhost())
                edge = d->rightRelayEdge(property);
            else 
                edge = d->rightEdge(property);
        }
        
    }
    
    return edge;
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

//! 
/*! 
 *  
 */
void dtkComposerNodeGraphic::onEdgeConnected(dtkComposerEdge *edge)
{
    dtkComposerNodeGraphicPrivate::EdgesAlongRoutes map = d->edgesAlongRoutes(edge);

    if (!map.count()) {
        edge->invalidate();

    } else {

        foreach(dtkComposerNodeGraphicPrivate::Route pair, map.keys()) {
            if (pair.first->node()->l->canConnectRoute(pair.first, pair.second, pair.second->node())) {
                foreach(dtkComposerEdge *e, map.value(pair))
                    e->validate();
            } else {
                foreach(dtkComposerEdge *e, map.value(pair))
                    if (!this->isEdgeAlongRoute(e))
                        e->invalidate();
            }
        }
    }

    // QList<dtkComposerNodeProperty *> sources;
    // QList<dtkComposerNodeProperty *> destinations;
        
    // foreach(dtkComposerEdge *e, d->leftRoute(edge))
    //     if (!sources.contains(e->source()) && 
    //         e->source()->node()->kind() != dtkComposerNode::Composite)
    //         sources << e->source();
        
    // foreach(dtkComposerEdge *e, d->rightRoute(edge))
    //     if (!destinations.contains(e->destination()) && 
    //         e->destination()->node()->kind() != dtkComposerNode::Composite)
    //         destinations << e->destination();

    // dtkComposerEdge *current_route = NULL;

    // foreach(dtkComposerNodeProperty *source, sources) {
    //     foreach(dtkComposerNodeProperty *destin, destinations) {

    //         current_route = source->node()->l->canConnectRoute(source, destin, destin->node());
    //         if (current_route) {
    //             foreach(dtkComposerEdge *edge_on_route, d->edgesAlongRoute(current_route))
    //                 edge_on_route->invalidate();
    //         } else {
    //             foreach(dtkComposerEdge *edge_on_route, d->edgesAlongRoute(current_route))
    //                 edge_on_route->validate();
    //         }    
    //     }
    // }
}

//! 
/*! 
 *  
 */
void dtkComposerNodeGraphic::onEdgeDisconnected(dtkComposerEdge *edge)
{
    dtkComposerNodeGraphicPrivate::EdgesAlongRoutes map = d->edgesAlongRoutes(edge);

    if (!map.count()) {
        edge->validate();

    } else {

        foreach(dtkComposerNodeGraphicPrivate::Route pair, map.keys()) {
            pair.first->node()->l->onRouteDisconnected(pair.first, pair.second, pair.second->node());
            foreach(dtkComposerEdge *e, map.value(pair)) {
                if (e != edge && !this->isEdgeAlongRoute(e))
                    e->invalidate();
                else
                    e->validate();
            }
            
        }
    }

    // QList<dtkComposerNodeProperty *> sources;
    // QList<dtkComposerNodeProperty *> destinations;

    // foreach(dtkComposerEdge *e, d->leftRoute(edge))
    //     if (!sources.contains(e->source()) && e->source()->node()->kind() != dtkComposerNode::Composite)
    //         sources << e->source();

    // foreach(dtkComposerEdge *e, d->rightRoute(edge))
    //     if (!destinations.contains(e->destination()) && e->destination()->node()->kind() != dtkComposerNode::Composite)
    //         destinations << e->destination();

    // dtkComposerEdge *input_route = NULL;
    // dtkComposerEdge *output_route = NULL;
        
    // foreach(dtkComposerNodeProperty *source, sources) {
    //     foreach(dtkComposerNodeProperty *destin, destinations) {

    //         if (source->type() == dtkComposerNodeProperty::Generic) {

    //             if (source->position() == dtkComposerNodeProperty::Right) {

    //                 if (source->node()->kind() == dtkComposerNode::Control) {

    //                     dtkComposerNodeControl *control_node = dynamic_cast<dtkComposerNodeControl *>(source->node());  

    //                     foreach(dtkComposerEdge *o_route, source->node()->l->rightRoutes()) {
    //                         if (o_route->source() == source && o_route->destination() == destin) {
    //                             output_route = o_route;
    //                             source->node()->l->removeRightRoute(output_route);
    //                             break;
    //                         }
    //                     }

    //                     foreach(dtkComposerEdge *active_route, control_node->outputActiveRoutes()) {
    //                         if (active_route->source() == source && active_route->destination() == destin) {                           
    //                             control_node->removeOutputActiveRoute(active_route);
    //                             if (destin->position() == dtkComposerNodeProperty::Right) {
    //                                 dtkComposerNodeControl *output_control_node = dynamic_cast<dtkComposerNodeControl *>(destin->node());
    //                                 output_control_node->removeOutputRelayRoute(active_route);
    //                             } else {
    //                                 destin->node()->l->removeLeftRoute(active_route);
    //                             }
    //                         }
    //                     }

    //                     if (output_route)
    //                         delete output_route;
    //                     output_route = NULL;                        
                        
    //                 } else {

    //                     if (destin->position() == dtkComposerNodeProperty::Right && 
    //                         source->node()->isChildOfControlNode(destin->node())) {

    //                         dtkComposerNodeControl *control_node = dynamic_cast<dtkComposerNodeControl *>(destin->node());
    //                         foreach(dtkComposerEdge *o_route, control_node->outputRelayRoutes()) {
    //                             if (o_route->source() == source && o_route->destination() == destin) {
    //                                 foreach(dtkComposerEdge *active_route, control_node->outputActiveRoutes()) {
    //                                     if (active_route->source() == destin || active_route->source() == source) {
    //                                         active_route->destination()->node()->removeRoute(active_route);
    //                                         control_node->removeOutputActiveRoute(active_route);
    //                                         delete active_route;
    //                                         active_route = NULL;
    //                                     }
    //                                 }
    //                                 input_route = o_route;
    //                                 control_node->removeOutputRelayRoute(input_route);
    //                                 input_route->source()->node()->l->removeRightRoute(input_route);
    //                                 break;
    //                             }
    //                         }

    //                         if (input_route)
    //                             delete input_route;
    //                         input_route = NULL;                            

    //                     } else {

    //                         foreach(dtkComposerEdge *i_route, destin->node()->l->leftRoutes()) {
    //                             if (i_route->source() == source && i_route->destination() == destin) {
    //                                 input_route = i_route;
    //                                 destin->node()->l->removeLeftRoute(input_route);
    //                                 break;
    //                             }
    //                         }
                            
    //                         foreach(dtkComposerEdge *o_route, source->node()->l->rightRoutes()) {
    //                             if (o_route->source() == source && o_route->destination() == destin) {
    //                                 output_route = o_route;
    //                                 source->node()->l->removeRightRoute(output_route);
    //                                 break;
    //                             }
    //                         }

    //                         if (input_route == output_route)
    //                             output_route = NULL;
                            
    //                         if (input_route)
    //                             delete input_route;
                            
    //                         if (output_route)
    //                             delete output_route;
                            
    //                         input_route = NULL;
    //                         output_route = NULL;
                            
    //                     }
                        
    //                 }

    //             } else {

    //                 dtkComposerNodeControl *control_node = dynamic_cast<dtkComposerNodeControl *>(source->node());
    //                 foreach(dtkComposerEdge *i_route, control_node->inputRelayRoutes()) {
    //                     if (i_route->source() == source && i_route->destination() == destin) {
    //                         foreach(dtkComposerEdge *active_route, control_node->inputActiveRoutes()) {
    //                             if (active_route->destination() == destin) {
    //                                 active_route->destination()->node()->removeRoute(active_route);
    //                                 control_node->removeInputActiveRoute(active_route);
    //                                 delete active_route;
    //                                 active_route = NULL;
    //                             }
    //                         }
    //                         output_route = i_route;
    //                         control_node->removeInputRelayRoute(output_route);
    //                         break;
    //                     }
    //                 }
    //                 if (output_route)
    //                     delete output_route;
    //                 output_route = NULL;

    //             }

    //         } else if (source->type() == dtkComposerNodeProperty::HybridOutput || 
    //             source->type() == dtkComposerNodeProperty::PassThroughOutput || 
    //             (source->type() == dtkComposerNodeProperty::Output && source->node()->kind() == dtkComposerNode::Control && !destin->node()->isChildOfControlNode(source->node()))) {

    //             dtkComposerNodeControl *control_node = dynamic_cast<dtkComposerNodeControl *>(source->node());  

    //             foreach(dtkComposerEdge *o_route, source->node()->l->rightRoutes()) {
    //                 if (o_route->source() == source && o_route->destination() == destin) {
    //                     output_route = o_route;
    //                     source->node()->l->removeRightRoute(output_route);
    //                     break;
    //                 }
    //             }

    //             foreach(dtkComposerEdge *active_route, control_node->outputActiveRoutes()) {
    //                 if (active_route->source() == source && active_route->destination() == destin) {                            
    //                     control_node->removeOutputActiveRoute(active_route);
    //                     if (destin->type() == dtkComposerNodeProperty::HybridOutput || 
    //                         destin->type() == dtkComposerNodeProperty::PassThroughOutput || 
    //                         (destin->type() == dtkComposerNodeProperty::Input && destin->node()->kind() == dtkComposerNode::Control && source->node()->isChildOfControlNode(destin->node()))) {
    //                         dtkComposerNodeControl *output_control_node = dynamic_cast<dtkComposerNodeControl *>(destin->node());
    //                         output_control_node->removeOutputRelayRoute(active_route);
    //                     } else {
    //                         destin->node()->l->removeLeftRoute(active_route);
    //                     }
    //                     delete active_route;
    //                     active_route = NULL;
    //                 }
    //             }
                    
    //             if (output_route)
    //                 delete output_route;
    //             output_route = NULL;
                    
    //         } else if (source->type() == dtkComposerNodeProperty::HybridInput || 
    //                    source->type() == dtkComposerNodeProperty::PassThroughInput || 
    //                    (source->type() == dtkComposerNodeProperty::Output && source->node()->kind() == dtkComposerNode::Control && destin->node()->isChildOfControlNode(source->node()))) {

    //             dtkComposerNodeControl *control_node = dynamic_cast<dtkComposerNodeControl *>(source->node());
    //             foreach(dtkComposerEdge *i_route, control_node->inputRelayRoutes()) {
    //                 if (i_route->source() == source && i_route->destination() == destin) {
    //                     foreach(dtkComposerEdge *active_route, control_node->inputActiveRoutes()) {
    //                         if (active_route->destination() == destin) {
    //                             active_route->destination()->node()->removeRoute(active_route);
    //                             control_node->removeInputActiveRoute(active_route);
    //                             delete active_route;
    //                             active_route = NULL;
    //                         }
    //                     }
    //                     output_route = i_route;
    //                     control_node->removeInputRelayRoute(output_route);
    //                     break;
    //                 }
    //             }

    //             if (output_route)
    //                 delete output_route;
    //             output_route = NULL;
              
    //         } else if (destin->type() == dtkComposerNodeProperty::Input && destin->node()->kind() == dtkComposerNode::Control && source->node()->isChildOfControlNode(destin->node())) {

    //             dtkComposerNodeControl *control_node = dynamic_cast<dtkComposerNodeControl *>(destin->node());
    //             foreach(dtkComposerEdge *o_route, control_node->outputRelayRoutes()) {
    //                 if (o_route->source() == source && o_route->destination() == destin) {
    //                     input_route = o_route;
    //                     control_node->removeOutputRelayRoute(input_route);
    //                     input_route->source()->node()->l->removeRightRoute(input_route);
    //                     break;
    //                 }
    //             }

    //             if (input_route)
    //                 delete input_route;
    //             input_route = NULL;

    //         } else if (destin->type() == dtkComposerNodeProperty::HybridOutput || 
    //                    destin->type() == dtkComposerNodeProperty::PassThroughOutput) {
                
    //             dtkComposerNodeControl *control_node = dynamic_cast<dtkComposerNodeControl *>(destin->node());
    //             foreach(dtkComposerEdge *o_route, control_node->outputRelayRoutes()) {
    //                 if (o_route->source() == source && o_route->destination() == destin) {
    //                     foreach(dtkComposerEdge *active_route, control_node->outputActiveRoutes()) {
    //                         if (active_route->source() == destin || active_route->source() == source) {
    //                             active_route->destination()->node()->removeRoute(active_route);
    //                             control_node->removeOutputActiveRoute(active_route);
    //                             delete active_route;
    //                             active_route = NULL;
    //                         }
    //                     }
    //                     input_route = o_route;
    //                     control_node->removeOutputRelayRoute(input_route);
    //                     input_route->source()->node()->l->removeRightRoute(input_route);
    //                     break;
    //                 }
    //             }
                
    //             if (input_route)
    //                 delete input_route;
    //             input_route = NULL;

    //         } else {

    //             foreach(dtkComposerEdge *i_route, destin->node()->l->leftRoutes()) {
    //                 if (i_route->source() == source && i_route->destination() == destin) {
    //                     input_route = i_route;
    //                     destin->node()->l->removeLeftRoute(input_route);
    //                     break;
    //                 }
    //             }

    //             foreach(dtkComposerEdge *o_route, source->node()->l->rightRoutes()) {
    //                 if (o_route->source() == source && o_route->destination() == destin) {
    //                     output_route = o_route;
    //                     source->node()->l->removeRightRoute(output_route);
    //                     break;
    //                 }
    //             }
                
    //             if (input_route == output_route)
    //                 output_route = NULL;

    //             if (input_route)
    //                 delete input_route;

    //             if (output_route)
    //                 delete output_route;

    //             input_route = NULL;
    //             output_route = NULL;
    //         }
    //     }
    // }
}

//! 
/*! 
 *  
 */
bool dtkComposerNodeGraphic::isEdgeAlongRoute(dtkComposerEdge *edge)
{    
    dtkComposerNodeGraphicPrivate::EdgesAlongRoutes map = d->edgesAlongRoutes(edge);

    foreach(dtkComposerNodeGraphicPrivate::Route pair, map.keys())
        if(pair.first->node()->l->isRoute(pair.first, pair.second))
            return true;

    return false;    
}

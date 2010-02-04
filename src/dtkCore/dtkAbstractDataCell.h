/* dtkAbstractDataCell.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Dec 11 11:04:22 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb  4 17:02:24 2010 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 25
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKABSTRACTDATACELL_H
#define DTKABSTRACTDATACELL_H

#include "dtkAbstractData.h"

class dtkAbstractDataVertex;
class dtkAbstractDataEdge;
class dtkAbstractDataFace;

class dtkAbstractDataCell : public dtkAbstractData
{
    Q_OBJECT

public:
             dtkAbstractDataCell(dtkAbstractData *parent = 0);
    virtual ~dtkAbstractDataCell(void);

    enum Type {
        dtkAbstractDataCellTetrahedron,
        dtkAbstractDataCellCube,
        dtkAbstractDataCellPolyhedron
    };

    virtual int countVertices(void) = 0;
    virtual int countEdges(void) = 0;
    virtual int countFaces(void) = 0;

    virtual QList<dtkAbstractDataVertex *> vertices(void) = 0;
    virtual QList<dtkAbstractDataEdge *> edges(void) = 0;
    virtual QList<dtkAbstractDataFace *> faces(void) = 0;

    virtual Type type(void) = 0;

    virtual void addVertex(dtkAbstractDataVertex *vertex) = 0;
    virtual void addEdge(dtkAbstractDataEdge *edge) = 0;
    virtual void addFace(dtkAbstractDataFace *face) = 0;
};

#endif

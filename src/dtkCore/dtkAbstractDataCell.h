/* dtkAbstractDataCell.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Dec 11 11:04:22 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb  1 22:16:40 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 22
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
        dtkAbstractDataFaceTetrahedron,
        dtkAbstractDataFaceCube,
        dtkAbstractDataFacePolyhedron
    };

    virtual int countVertices(void) = 0;
    virtual int countEdges(void) = 0;
    virtual int countFaces(void) = 0;

    virtual QList<dtkAbstractDataVertex *> vertices(void) = 0;
    virtual QList<dtkAbstractDataEdge *> edges(void) = 0;
    virtual QList<dtkAbstractDataFace *> faces(void) = 0;

    virtual Type type(void) = 0;
};

#endif

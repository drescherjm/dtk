/* dtk3DQuickMesh.h ---
 * 
 * Author: Julien Wintz
 * Created: Fri Apr  5 10:55:47 2013 (+0200)
 * Version: 
 * Last-Updated: Fri Apr  5 11:28:37 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 20
 */

/* Change Log:
 * 
 */

#pragma once

#include "dtk3DQuickItem"

#include <QtCore>
#include <QtQuick>

class dtk3DQuickMeshPrivate;

class dtk3DQuickMesh : public dtk3DQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QString type READ type WRITE setType)
    Q_PROPERTY(QString file READ file WRITE setFile)

public:
     dtk3DQuickMesh(QObject *parent = 0);
    ~dtk3DQuickMesh(void);

#pragma mark -
#pragma mark Properties - getters
    
    const QString& file(void);
    const QString& type(void);

#pragma mark -
#pragma mark Properties - setters
    
    void setFile(const QString& file);
    void setType(const QString& type);

private:
    dtk3DQuickMeshPrivate *d;
};

QML_DECLARE_TYPE(dtk3DQuickMesh)

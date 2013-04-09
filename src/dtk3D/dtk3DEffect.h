/* dtk3DEffect.h ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr  8 12:44:22 2013 (+0200)
 * Version: 
 * Last-Updated: Mon Apr  8 14:53:13 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 45
 */

/* Change Log:
 * 
 */

#pragma once

#include <QtCore>
#include <QtGui>
#include <QtOpenGL>
#include <Qt3D/QGLAbstractEffect>
#include <Qt3D/QGLPainter>

class dtk3DEffectPrivate;

class dtk3DEffect : public QGLAbstractEffect
{
public:
             dtk3DEffect(void);
    virtual ~dtk3DEffect(void);

public:
    void setActive(QGLPainter *painter, bool flag);

public:
    void update(QGLPainter *painter, QGLPainter::Updates updates);

#pragma mark -
#pragma mark Vertex shader

    QByteArray vertexShader(void) const;
    void setVertexShader(const QByteArray &source);
    void setVertexShaderFromFile(const QString &fileName);

#pragma mark -
#pragma mark Geometry shader

    QByteArray geometryShader(void) const;
    void setGeometryShader(const QByteArray &source);
    void setGeometryShaderFromFile(const QString &fileName);

#pragma mark -
#pragma mark Fragment shader

    QByteArray fragmentShader(void) const;
    void setFragmentShader(const QByteArray &source);
    void setFragmentShaderFromFile(const QString &fileName);

#pragma mark -
#pragma mark Lighting

        int maximumLights(void) const;
    void setMaximumLights(int value);

#pragma mark -
#pragma mark Shader program

    QGLShaderProgram *program(void) const;

protected:
    virtual bool beforeLink(void);
    virtual void afterLink(void);

private:
    dtk3DEffectPrivate *d;

private:
    Q_DISABLE_COPY(dtk3DEffect)
};

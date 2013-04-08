/* dtk3DEffect.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr  8 14:11:18 2013 (+0200)
 * Version: 
 * Last-Updated: Mon Apr  8 19:41:36 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 161
 */

/* Change Log:
 * 
 */

#include "dtk3DEffect"
#include "dtk3DEffect_p"

dtk3DEffect::dtk3DEffect(void) : d(new dtk3DEffectPrivate)
{

}

dtk3DEffect::~dtk3DEffect(void)
{
    delete d;
}

void dtk3DEffect::setActive(QGLPainter *painter, bool flag)
{
#if !defined(QGL_SHADERS_ONLY)
    d->fixedFunction = painter->isFixedFunction();

    if (d->fixedFunction) {
        if (flag)
            glEnableClientState(GL_VERTEX_ARRAY);
        else
            glDisableClientState(GL_VERTEX_ARRAY);
        return;
    }
#endif

#if !defined(QGL_FIXED_FUNCTION_ONLY)
    static const char *const attributes[] = {
        "qt_Vertex",
        "qt_Normal",
        "qt_Color",
        "qt_MultiTexCoord0",
        "qt_MultiTexCoord1",
        "qt_MultiTexCoord2",
        "qt_Custom0",
        "qt_Custom1"
    };
    static const int numAttributes = 8;

    Q_UNUSED(painter);

    if (d->regenerate) {
        delete d->program;
        d->program = 0;
        d->regenerate = false;
    }

    if (!d->program) {

        if (!flag)
            return;

        Q_ASSERT(!d->vertexShader.isEmpty());
        Q_ASSERT(!d->fragmentShader.isEmpty());

        d->program = new QGLShaderProgram;
        d->program->addShaderFromSourceCode(QGLShader::Vertex, d->vertexShader);
        d->program->addShaderFromSourceCode(QGLShader::Fragment, d->fragmentShader);
	if(!d->geometryShader.isEmpty()) {
	    d->program->addShaderFromSourceCode(QGLShader::Geometry, d->geometryShader);
	    d->program->setGeometryInputType(GL_TRIANGLES);
	    d->program->setGeometryOutputType(GL_TRIANGLES);
	}

        if (beforeLink()) {
            for (int attr = 0; attr < numAttributes; ++attr)
                d->program->bindAttributeLocation(attributes[attr], attr);
        }

        if (!d->program->link()) {
            qWarning("dtk3DEffect::setActive(): could not link shader program");
            delete d->program;
            d->program = 0;
            return;
        }

        afterLink();

        d->attributes = 0;

        for (int attr = 0; attr < numAttributes; ++attr) {
            if (d->program->attributeLocation(attributes[attr]) != -1)
                d->attributes |= (1 << attr);
        }

        if (d->program->attributeLocation("qgl_Vertex") != -1)
            qWarning("dtk3DEffect: qgl_Vertex no longer supported; use qt_Vertex instead");

        d->matrix = d->program->uniformLocation("qt_ModelViewProjectionMatrix");
        d->mvMatrix = d->program->uniformLocation("qt_ModelViewMatrix");
        d->projMatrix = d->program->uniformLocation("qt_ProjectionMatrix");
        d->normalMatrix = d->program->uniformLocation("qt_NormalMatrix");
        d->worldMatrix = d->program->uniformLocation("qt_WorldMatrix");
        d->texture0 = d->program->uniformLocation("qt_Texture0");
        d->texture1 = d->program->uniformLocation("qt_Texture1");
        d->texture2 = d->program->uniformLocation("qt_Texture2");
        d->color = d->program->uniformLocation("qt_Color");
        d->numLights = d->program->uniformLocation("qt_NumLights");
        d->haveLight = (d->program->uniformLocation("qt_Light.position") != -1);
        d->haveLights = (d->program->uniformLocation("qt_Lights[0].position") != -1);
        d->haveMaterial = (d->program->uniformLocation("qt_Material.diffuse") != -1);
        d->haveMaterials = (d->program->uniformLocation("qt_Materials[0].diffuse") != -1);
    }

    if (flag) {

        d->program->bind();

        for (int attr = 0; attr < numAttributes; ++attr) {
            if ((d->attributes & (1 << attr)) == 0)
                continue;
            d->program->enableAttributeArray(attr);
        }

        if (d->texture0 != -1)
            d->program->setUniformValue(d->texture0, 0);

        if (d->texture1 != -1)
            d->program->setUniformValue(d->texture1, 1);

        if (d->texture2 != -1)
            d->program->setUniformValue(d->texture2, 2);

    } else {

        for (int attr = 0; attr < int(QGL::UserVertex); ++attr) {
            if ((d->attributes & (1 << attr)) != 0)
                d->program->disableAttributeArray(attr);
        }

        d->program->release();
    }
#endif
}

void dtk3DEffect::update(QGLPainter *painter, QGLPainter::Updates updates)
{
#if !defined(QGL_SHADERS_ONLY)
    if (d->fixedFunction) {
        painter->updateFixedFunction(updates & (QGLPainter::UpdateColor | QGLPainter::UpdateMatrices));
        return;
    }
#endif

#if !defined(QGL_FIXED_FUNCTION_ONLY)
    if (!d->program)
        return;

    if ((updates & QGLPainter::UpdateColor) != 0 && d->color != -1)
        d->program->setUniformValue(d->color, painter->color());

    if ((updates & QGLPainter::UpdateMatrices) != 0) {
        if (d->matrix != -1)
            d->program->setUniformValue(d->matrix, painter->combinedMatrix());
    }

    if ((updates & QGLPainter::UpdateModelViewMatrix) != 0) {
        if (d->mvMatrix != -1)
            d->program->setUniformValue(d->mvMatrix, painter->modelViewMatrix());
        if (d->normalMatrix != -1)
            d->program->setUniformValue(d->normalMatrix, painter->normalMatrix());
        if (d->worldMatrix != -1)
            d->program->setUniformValue(d->worldMatrix, painter->worldMatrix());
    }

    if ((updates & QGLPainter::UpdateProjectionMatrix) != 0) {
        if (d->projMatrix != -1)
            d->program->setUniformValue(d->projMatrix, painter->projectionMatrix());
    }

    if ((updates & QGLPainter::UpdateLights) != 0) {
        if (d->haveLight) {
            d->setLight(painter->mainLight(), painter->mainLightTransform(), "qt_Light", -1);
        } else if (d->haveLights) {
            int numLights = 0;
            int maxLightId = painter->maximumLightId();

            if (maxLightId < 0) {
                painter->mainLight();
                maxLightId = 0;
            }

            for (int lightId = 0; lightId <= maxLightId; ++lightId) {
                const QGLLightParameters *lparams = painter->light(lightId);

                if (!lparams)
                    continue;

                d->setLight(lparams, painter->lightTransform(lightId), "qt_Lights", numLights);

                ++numLights;

                if (numLights >= d->maximumLights)
                    break;
            }

            if (d->numLights != -1)
                d->program->setUniformValue(d->numLights, numLights);
        }
    }

    if ((updates & QGLPainter::UpdateMaterials) != 0 || ((updates & QGLPainter::UpdateLights) != 0 && d->haveLight)) {
        if (d->haveLight) {
            if (d->haveMaterial) {
                d->setMaterial(painter->faceMaterial(QGL::FrontFaces),
                               painter->lightModel(), painter->mainLight(), "qt_Material", -1);
            } else if (d->haveMaterials) {
                d->setMaterial(painter->faceMaterial(QGL::FrontFaces), painter->lightModel(), painter->mainLight(), "qt_Materials", 0);
                d->setMaterial(painter->faceMaterial(QGL::BackFaces), painter->lightModel(), painter->mainLight(), "qt_Materials", 1);
            }
        } else {
            if (d->haveMaterial) {
                d->setMaterial(painter->faceMaterial(QGL::FrontFaces), painter->lightModel(), 0, "qt_Material", -1);
            } else if (d->haveMaterials) {
                d->setMaterial(painter->faceMaterial(QGL::FrontFaces), painter->lightModel(), 0, "qt_Materials", 0);
                d->setMaterial(painter->faceMaterial(QGL::BackFaces), painter->lightModel(), 0, "qt_Materials", 1);
            }
        }
    }
#endif
}

QByteArray dtk3DEffect::vertexShader(void) const
{
    return d->vertexShader;
}

void dtk3DEffect::setVertexShader(const QByteArray &source)
{
    d->vertexShader = source;
    d->regenerate = true;
}

void dtk3DEffect::setVertexShaderFromFile(const QString &fileName)
{
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly)) {
        d->vertexShader = file.readAll();
        d->regenerate = true;
    } else {
        qWarning() << "dtk3DEffect::setVertexShaderFromFile: could not open " << fileName;
    }
}

QByteArray dtk3DEffect::geometryShader(void) const
{
    return d->geometryShader;
}

void dtk3DEffect::setGeometryShader(const QByteArray &source)
{
    d->geometryShader = source;
    d->regenerate = true;
}

void dtk3DEffect::setGeometryShaderFromFile(const QString &fileName)
{
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly)) {
        d->geometryShader = file.readAll();
        d->regenerate = true;
    } else {
        qWarning() << "dtk3DEffect::setGeometryShaderFromFile: could not open " << fileName;
    }
}

QByteArray dtk3DEffect::fragmentShader(void) const
{
    return d->fragmentShader;
}

void dtk3DEffect::setFragmentShaderFromFile(const QString &fileName)
{
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly)) {
        d->fragmentShader = file.readAll();
        d->regenerate = true;
    } else {
        qWarning() << "dtk3DEffect::setFragmentShaderFromFile: could not open " << fileName;
    }
}

void dtk3DEffect::setFragmentShader(const QByteArray &source)
{
    d->fragmentShader = source;
    d->regenerate = true;
}

int dtk3DEffect::maximumLights(void) const
{
    return d->maximumLights;
}

void dtk3DEffect::setMaximumLights(int value)
{
    d->maximumLights = value;
}

QGLShaderProgram *dtk3DEffect::program(void) const
{
#if !defined(QGL_FIXED_FUNCTION_ONLY)
    return d->program;
#else
    return NULL;
#endif
}

bool dtk3DEffect::beforeLink(void)
{
    return true;
}

void dtk3DEffect::afterLink(void)
{

}

// ///////////////////////////////////////////////////////////////////
// dtk3DEffectPrivate implementation
// ///////////////////////////////////////////////////////////////////

dtk3DEffectPrivate::dtk3DEffectPrivate(void)
#if !defined(QGL_FIXED_FUNCTION_ONLY)
    : program(0)
    , matrix(-1)
    , mvMatrix(-1)
    , projMatrix(-1)
    , normalMatrix(-1)
    , worldMatrix(-1)
    , texture0(-1)
    , texture1(-1)
    , texture2(-1)
    , color(-1)
    , numLights(-1)
    , haveLight(0)
    , haveLights(0)
    , haveMaterial(0)
    , haveMaterials(0)
#endif
{
    this->geometryInputType = GL_TRIANGLE_STRIP;
    this->geometryOutputType = GL_TRIANGLE_STRIP;
    this->maximumLights = 8;
    this->attributes = 0;
    this->regenerate = true;
    this->fixedFunction = false;
}

dtk3DEffectPrivate::~dtk3DEffectPrivate(void)
{
#if !defined(QGL_FIXED_FUNCTION_ONLY)
    delete program;
#endif
}

#if !defined(QGL_FIXED_FUNCTION_ONLY)

void dtk3DEffectPrivate::setUniformValue(const char *array, int index, const char *field, GLfloat v)
{
    char name[128];

    if (index >= 0)
        qsnprintf(name, sizeof(name), "%s[%d].%s", array, index, field);
    else
        qsnprintf(name, sizeof(name), "%s.%s", array, field);

    program->setUniformValue(name, v);
}

void dtk3DEffectPrivate::setUniformValue(const char *array, int index, const char *field, const QVector3D &v)
{
    char name[128];

    if (index >= 0)
        qsnprintf(name, sizeof(name), "%s[%d].%s", array, index, field);
    else
        qsnprintf(name, sizeof(name), "%s.%s", array, field);

    program->setUniformValue(name, v);
}

void dtk3DEffectPrivate::setUniformValue(const char *array, int index, const char *field, const QVector4D &v)
{
    char name[128];

    if (index >= 0)
        qsnprintf(name, sizeof(name), "%s[%d].%s", array, index, field);
    else
        qsnprintf(name, sizeof(name), "%s.%s", array, field);

    program->setUniformValue(name, v);
}

void dtk3DEffectPrivate::setUniformValue(const char *array, int index, const char *field, const QColor &v)
{
    char name[128];

    if (index >= 0)
        qsnprintf(name, sizeof(name), "%s[%d].%s", array, index, field);
    else
        qsnprintf(name, sizeof(name), "%s.%s", array, field);

    program->setUniformValue(name, v);
}

void dtk3DEffectPrivate::setLight(const QGLLightParameters *lparams, const QMatrix4x4 &ltransform, const char *array, int index)
{
    if (index >= 0) {
        setUniformValue(array, index, "ambient", lparams->ambientColor());
        setUniformValue(array, index, "diffuse", lparams->diffuseColor());
        setUniformValue(array, index, "specular", lparams->specularColor());
    }

    setUniformValue(array, index, "position", lparams->eyePosition(ltransform));
    setUniformValue(array, index, "spotDirection", lparams->eyeSpotDirection(ltransform).normalized());
    setUniformValue(array, index, "spotExponent", GLfloat(lparams->spotExponent()));
    setUniformValue(array, index, "spotCutoff", GLfloat(lparams->spotAngle()));
    setUniformValue(array, index, "spotCosCutoff", GLfloat(lparams->spotCosAngle()));
    setUniformValue(array, index, "constantAttenuation", GLfloat(lparams->constantAttenuation()));
    setUniformValue(array, index, "linearAttenuation", GLfloat(lparams->linearAttenuation()));
    setUniformValue(array, index, "quadraticAttenuation", GLfloat(lparams->quadraticAttenuation()));
}

static inline QVector4D colorToVector4(const QColor& color)
{
    return QVector4D(color.redF(), color.greenF(), color.blueF(), color.alphaF());
}

static inline QVector4D colorToVector4(const QColor &color, const QColor &lightColor)
{
    return QVector4D(color.redF() * lightColor.redF(),
                     color.greenF() * lightColor.greenF(),
                     color.blueF() * lightColor.blueF(),
                     color.alphaF() * lightColor.alphaF());
}

void dtk3DEffectPrivate::setMaterial(const QGLMaterial *mparams, const QGLLightModel *model, const QGLLightParameters *lparams, const char *array, int index)
{
    if (lparams) {
        setUniformValue(array, index, "ambient", colorToVector4(mparams->ambientColor(), lparams->ambientColor()));
        setUniformValue(array, index, "diffuse", colorToVector4(mparams->diffuseColor(), lparams->diffuseColor()));
        setUniformValue(array, index, "specular", colorToVector4(mparams->specularColor(), lparams->specularColor()));
    } else {
        setUniformValue(array, index, "ambient", mparams->ambientColor());
        setUniformValue(array, index, "diffuse", mparams->diffuseColor());
        setUniformValue(array, index, "specular", mparams->specularColor());
    }
    setUniformValue(array, index, "emission", colorToVector4(mparams->emittedLight()) + colorToVector4(mparams->ambientColor(), model->ambientSceneColor()));
    setUniformValue(array, index, "shininess", GLfloat(mparams->shininess()));
}

#endif // !QGL_FIXED_FUNCTION_ONLY

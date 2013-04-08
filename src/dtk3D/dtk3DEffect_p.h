/* dtk3DEffect_p.h ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr  8 14:30:50 2013 (+0200)
 * Version: 
 * Last-Updated: Mon Apr  8 14:52:50 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 8
 */

/* Change Log:
 * 
 */

class dtk3DEffectPrivate
{
public:
     dtk3DEffectPrivate(void);
    ~dtk3DEffectPrivate(void);

public:
    QByteArray vertexShader;
    QByteArray fragmentShader;
    QByteArray geometryShader;

    GLenum geometryInputType;
    GLenum geometryOutputType;

    int maximumLights;
    int attributes;

    bool regenerate;
    bool fixedFunction;

#if !defined(QGL_FIXED_FUNCTION_ONLY)
    QGLShaderProgram *program;
    int matrix;
    int mvMatrix;
    int projMatrix;
    int normalMatrix;
    int worldMatrix;
    int texture0;
    int texture1;
    int texture2;
    int color;
    int numLights;
    int haveLight : 1;
    int haveLights : 1;
    int haveMaterial : 1;
    int haveMaterials : 1;

public:
    void setUniformValue(const char *array, int index, const char *field, GLfloat v);
    void setUniformValue(const char *array, int index, const char *field, const QVector3D &v);
    void setUniformValue(const char *array, int index, const char *field, const QVector4D &v);
    void setUniformValue(const char *array, int index, const char *field, const QColor &v);

public:
    void setLight(const QGLLightParameters *lparams, const QMatrix4x4 &ltransform, const char *array, int index);
    void setMaterial(const QGLMaterial *mparams, const QGLLightModel *model, const QGLLightParameters *lparams, const char *array, int index);
#endif
};

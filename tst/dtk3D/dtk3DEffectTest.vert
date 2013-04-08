#version 120

/* dtk3DShaderTest.vert ---
 * 
 * Author: Julien Wintz
 * Created: Fri Apr  5 19:33:30 2013 (+0200)
 * Version: 
 * Last-Updated: Mon Apr  8 20:29:11 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 140
 */

/* Change Log:
 * 
 */

#extension GL_EXT_gpu_shader4 : enable

// ///////////////////////////////////////////////////////////////////
// Customs
// ///////////////////////////////////////////////////////////////////

struct qt_MaterialParameters {
    mediump vec4 emission;
    mediump vec4 ambient;
    mediump vec4 diffuse;
    mediump vec4 specular;
    mediump float shininess;
};

struct qt_SingleLightParameters {
    mediump vec4 position;
    mediump vec3 spotDirection;
    mediump float spotExponent;
    mediump float spotCutoff;
    mediump float spotCosCutoff;
    mediump float constantAttenuation;
    mediump float linearAttenuation;
    mediump float quadraticAttenuation;
};

// ///////////////////////////////////////////////////////////////////
// Attributes
// ///////////////////////////////////////////////////////////////////

attribute highp vec4 qt_Vertex;
attribute highp vec3 qt_Normal;

// ///////////////////////////////////////////////////////////////////
// Uniforms
// ///////////////////////////////////////////////////////////////////

uniform mediump mat4 qt_ModelViewMatrix;
uniform mediump mat4 qt_ModelViewProjectionMatrix;
uniform mediump mat3 qt_NormalMatrix;

uniform mediump qt_MaterialParameters qt_Material;
uniform mediump qt_SingleLightParameters qt_Light;

// ///////////////////////////////////////////////////////////////////
// Varyings
// ///////////////////////////////////////////////////////////////////

varying mediump vec3 vs_Normal;
varying mediump vec4 vs_Ambient;
varying mediump vec4 vs_Diffuse;
varying mediump vec3 vs_HalfVector;
varying mediump vec3 vs_VertexToLight;
varying mediump vec3 vs_LightDirection;

// ///////////////////////////////////////////////////////////////////
// Helper functions
// ///////////////////////////////////////////////////////////////////

void qLightVertex(vec4 vertex, vec3 normal)
{
    vec3 toEye = vec3(0, 0, 1);

    vs_Normal = normal;
    vs_Ambient = qt_Material.emission + qt_Material.ambient;
    vs_Diffuse = qt_Material.diffuse;
    vs_LightDirection = normalize(qt_Light.position.xyz);
    vs_HalfVector = normalize(vs_LightDirection + toEye);
    vs_VertexToLight = vertex.xyz - qt_Light.position.xyz;
}

// ///////////////////////////////////////////////////////////////////
// Vertex shader
// ///////////////////////////////////////////////////////////////////

void main(void)
{
    gl_Position = qt_ModelViewProjectionMatrix * qt_Vertex;

    vec4 vertex = qt_ModelViewMatrix * qt_Vertex;
    vec3 normal = normalize(qt_NormalMatrix * qt_Normal);

    qLightVertex(vertex, normal);
}

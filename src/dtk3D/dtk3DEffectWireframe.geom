#version 120

/* dtk3DEffectWireframe.geom ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr  8 23:12:18 2013 (+0200)
 * Version: 
 * Last-Updated: Tue Apr  9 00:22:36 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 35
 */

/* Change Log:
 * 
 */

#extension GL_EXT_gpu_shader4 : enable
#extension GL_EXT_geometry_shader4 : enable

// ///////////////////////////////////////////////////////////////////
// Uniforms
// ///////////////////////////////////////////////////////////////////

uniform vec2 view;

// ///////////////////////////////////////////////////////////////////
// Varyings
// ///////////////////////////////////////////////////////////////////

varying mediump in vec3 vs_Normal[3];
varying mediump in vec4 vs_Ambient[3];
varying mediump in vec4 vs_Diffuse[3];
varying mediump in vec3 vs_Position[3];
varying mediump in vec3 vs_HalfVector[3];
varying mediump in vec3 vs_VertexToLight[3];
varying mediump in vec3 vs_LightDirection[3];

varying mediump out vec3 gs_Normal;
varying mediump out vec4 gs_Ambient;
varying mediump out vec4 gs_Diffuse;
varying mediump out vec3 gs_Position;
varying mediump out vec3 gs_HalfVector;
varying mediump out vec3 gs_VertexToLight;
varying mediump out vec3 gs_LightDirection;

noperspective varying vec3 dist;

///////////////////////////////////////////////////////////////////
// Helper functions
///////////////////////////////////////////////////////////////////

void qPassThrough(int i)
{
    gs_Normal = vs_Normal[i];
    gs_Ambient = vs_Ambient[i];
    gs_Diffuse = vs_Diffuse[i];
    gs_HalfVector = vs_HalfVector[i];
    gs_VertexToLight = vs_VertexToLight[i];
    gs_LightDirection = vs_LightDirection[i];
}

///////////////////////////////////////////////////////////////////
// Geometry shader
///////////////////////////////////////////////////////////////////

void main(void)
{
    vec2 p0 = view * gl_PositionIn[0].xy/gl_PositionIn[0].w;
    vec2 p1 = view * gl_PositionIn[1].xy/gl_PositionIn[1].w;
    vec2 p2 = view * gl_PositionIn[2].xy/gl_PositionIn[2].w;

    vec2 v0 = p2-p1;
    vec2 v1 = p2-p0;
    vec2 v2 = p1-p0;

    float area = abs(v1.x*v2.y - v1.y*v2.x);

    dist = vec3(area/length(v0), 0.0, 0.0);
    gs_Normal = vs_Normal[0];
    gs_Position = vs_Position[0];
    gl_Position = gl_PositionIn[0];
    qPassThrough(0);
    EmitVertex();

    dist = vec3(0.0, area/length(v1), 0.0);
    gs_Normal = vs_Normal[1];
    gs_Position = vs_Position[1];
    gl_Position = gl_PositionIn[1];
    qPassThrough(1);
    EmitVertex();

    dist = vec3(0.0, 0.0, area/length(v2));
    gs_Normal = vs_Normal[2];
    gs_Position = vs_Position[2];
    gl_Position = gl_PositionIn[2];
    qPassThrough(2);
    EmitVertex();

    EndPrimitive();
}

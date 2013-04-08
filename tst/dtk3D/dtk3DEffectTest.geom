#version 120

/* dtk3DEffectTest.geom ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr  8 15:44:27 2013 (+0200)
 * Version: 
 * Last-Updated: Mon Apr  8 20:51:21 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 171
 */

/* Change Log:
 * 
 */

#extension GL_EXT_gpu_shader4 : enable
#extension GL_EXT_geometry_shader4 : enable

// ///////////////////////////////////////////////////////////////////
// Varyings
// ///////////////////////////////////////////////////////////////////

varying mediump in vec3 vs_Normal[3];
varying mediump in vec4 vs_Ambient[3];
varying mediump in vec4 vs_Diffuse[3];
varying mediump in vec3 vs_HalfVector[3];
varying mediump in vec3 vs_VertexToLight[3];
varying mediump in vec3 vs_LightDirection[3];

varying mediump out vec3 gs_Normal;
varying mediump out vec4 gs_Ambient;
varying mediump out vec4 gs_Diffuse;
varying mediump out vec3 gs_HalfVector;
varying mediump out vec3 gs_VertexToLight;
varying mediump out vec3 gs_LightDirection;

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
    gl_Position = gl_PositionIn[0]; qPassThrough(0); EmitVertex();
    gl_Position = gl_PositionIn[1]; qPassThrough(1); EmitVertex();
    gl_Position = gl_PositionIn[2]; qPassThrough(2); EmitVertex();
    EndPrimitive();

    gl_Position = gl_PositionIn[0] + vec4(3.0, 0.0, 0.0, 0.0); qPassThrough(0); EmitVertex();
    gl_Position = gl_PositionIn[1] + vec4(3.0, 0.0, 0.0, 0.0); qPassThrough(1); EmitVertex();
    gl_Position = gl_PositionIn[2] + vec4(3.0, 0.0, 0.0, 0.0); qPassThrough(2); EmitVertex();
    EndPrimitive();

    gl_Position = gl_PositionIn[0] - vec4(3.0, 0.0, 0.0, 0.0); qPassThrough(0); EmitVertex();
    gl_Position = gl_PositionIn[1] - vec4(3.0, 0.0, 0.0, 0.0); qPassThrough(1); EmitVertex();
    gl_Position = gl_PositionIn[2] - vec4(3.0, 0.0, 0.0, 0.0); qPassThrough(2); EmitVertex();
    EndPrimitive();
}

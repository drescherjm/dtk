#version 120

/* dtk3DEffectTest.geom ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr  8 15:44:27 2013 (+0200)
 * Version: 
 * Last-Updated: Mon Apr  8 18:02:59 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 97
 */

/* Change Log:
 * 
 */

#extension GL_EXT_gpu_shader4 : enable
#extension GL_EXT_geometry_shader4 : enable

// ///////////////////////////////////////////////////////////////////
// Geometry shader
// ///////////////////////////////////////////////////////////////////

void main(void)
{
    gl_Position = gl_PositionIn[0]; EmitVertex();
    gl_Position = gl_PositionIn[1]; EmitVertex();
    gl_Position = gl_PositionIn[2]; EmitVertex();
    EndPrimitive();

    gl_Position = gl_PositionIn[0] + vec4(2.0, 0.0, 0.0, 0.0); EmitVertex();
    gl_Position = gl_PositionIn[1] + vec4(2.0, 0.0, 0.0, 0.0); EmitVertex();
    gl_Position = gl_PositionIn[2] + vec4(2.0, 0.0, 0.0, 0.0); EmitVertex();
    EndPrimitive();
}

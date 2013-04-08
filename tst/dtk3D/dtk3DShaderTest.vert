/* dtk3DShaderTest.vert ---
 * 
 * Author: Julien Wintz
 * Created: Fri Apr  5 19:33:30 2013 (+0200)
 * Version: 
 * Last-Updated: Sun Apr  7 19:24:17 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 12
 */

/* Change Log:
 * 
 */

attribute highp vec4 qt_Vertex;
uniform mediump mat4 qt_ModelViewProjectionMatrix;

void main(void)
{
    gl_Position = qt_ModelViewProjectionMatrix * qt_Vertex;
}

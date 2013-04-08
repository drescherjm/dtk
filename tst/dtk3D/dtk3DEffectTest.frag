#version 120

/* dtk3DShaderTest.frag ---
 * 
 * Author: Julien Wintz
 * Created: Fri Apr  5 19:33:56 2013 (+0200)
 * Version: 
 * Last-Updated: Mon Apr  8 20:54:00 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 37
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
// Uniforms
// ///////////////////////////////////////////////////////////////////

uniform mediump qt_MaterialParameters qt_Material;
uniform mediump qt_SingleLightParameters qt_Light;

// ///////////////////////////////////////////////////////////////////
// Varyings
// ///////////////////////////////////////////////////////////////////

varying mediump vec3 gs_Normal;
varying mediump vec4 gs_Ambient;
varying mediump vec4 gs_Diffuse;
varying mediump vec3 gs_HalfVector;
varying mediump vec3 gs_VertexToLight;
varying mediump vec3 gs_LightDirection;

// ///////////////////////////////////////////////////////////////////
// Helper functions
// ///////////////////////////////////////////////////////////////////

vec4 qLightPixel(vec4 ambient, vec4 diffuse)
{
    float angle;
    float spot;

    vec4 color;
    vec4 component;
    vec3 normal = normalize(gs_Normal);

    // Start with the ambient color.
    color = ambient;

    // Determine the cosine of the angle between the normal and the
    // vector from the vertex to the light.
    angle = max(dot(normal, gs_LightDirection), 0.0);

    // Calculate the diffuse light components.
    component = angle * diffuse;

    // Calculate the specular light components.
    if (angle != 0.0) {
        angle = max(dot(normal, gs_HalfVector), 0.0);
        component += pow(angle, qt_Material.shininess) * qt_Material.specular;
    }

    // Apply the spotlight angle and exponent.
    if (qt_Light.spotCutoff != 180.0) {
        spot = max(dot(normalize(gs_VertexToLight),
                       normalize(qt_Light.spotDirection)), 0.0);
        if (spot < qt_Light.spotCosCutoff)
            spot = 0.0;
        else
            spot = pow(spot, qt_Light.spotExponent);
        component *= spot;
    }

    return clamp(color + component, 0.0, 1.0);
}

// ///////////////////////////////////////////////////////////////////
// Fragment shader
// ///////////////////////////////////////////////////////////////////

void main(void)
{
    gl_FragColor = qLightPixel(gs_Ambient, gs_Diffuse);
}

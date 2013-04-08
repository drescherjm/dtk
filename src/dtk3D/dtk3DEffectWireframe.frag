#version 120

/* dtk3DEffectWireframe.frag ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr  8 23:12:48 2013 (+0200)
 * Version: 
 * Last-Updated: Tue Apr  9 00:29:57 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 23
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
varying mediump vec3 gs_Position;
varying mediump vec3 gs_HalfVector;
varying mediump vec3 gs_VertexToLight;
varying mediump vec3 gs_LightDirection;

noperspective varying vec3 dist;

// ///////////////////////////////////////////////////////////////////
// Helper functions
// ///////////////////////////////////////////////////////////////////

vec4 qLightPixel(vec4 ambient, vec4 diffuse)
{
    float angle;
    float spot;

    vec4 color;
    vec4 component;
    vec3 normal;

    color = ambient;
    normal = normalize(gs_Normal);
    angle = max(dot(normal, gs_LightDirection), 0.0);
    component = angle * diffuse;

    if (angle != 0.0) {
        angle = max(dot(normal, gs_HalfVector), 0.0);
        component += pow(angle, qt_Material.shininess) * qt_Material.specular;
    }

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
    float nearD = min(min(dist[0],dist[1]),dist[2]);
    float edgeIntensity = exp2(-1.0*nearD*nearD);

    vec3 L = gs_LightDirection;
    vec3 V = normalize(qt_Light.position.xyz - gs_Position);
    vec3 N = normalize(gs_Normal);
    vec3 H = normalize(L+V);

    float amb = 0.6;

    vec4 color = qLightPixel(gs_Ambient, gs_Diffuse);
    vec4 ambient = color * amb;
    vec4 diffuse = color * (1.0 - amb) * max(dot(L, N), 0.0);
    vec4 specular = vec4(0.0);

    gl_FragColor = (edgeIntensity * vec4(0.1,0.1,0.1,1.0)) + ((1.0-edgeIntensity) * vec4(ambient + diffuse + specular));
}

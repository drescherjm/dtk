//Version: $Id$
//
//

//Commentary:
//
//

//Change Log:
//
//

//Code:

import QtQuick 2.0

ShaderEffect {

    id: effectRoot;

    width: parent.width;
    height: parent.height;

    property color gradient_top: "#444444";
    property color gradient_mid: "#333333";
    property color gradient_bot: "#000000";

    Rectangle {
        id: colorTable
        width: parent.width;
        height: parent.height;

        gradient: Gradient {
            GradientStop { position: 0.0; color: gradient_top; }
            GradientStop { position: 0.4; color: gradient_mid; }
            GradientStop { position: 1.0; color: gradient_bot; }
        }

        layer.enabled: true
        layer.smooth: true

        visible: false;
    }

    property variant source: colorTable;

    blending: false;

    fragmentShader:"
    #ifdef GL_ES
    precision lowp float;
    #endif

    uniform lowp sampler2D source;
    uniform lowp float qt_Opacity;
    varying highp vec2 qt_TexCoord0;

    float rand(vec2 co){
        return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
    }

    void main() {
        lowp float len = clamp(length(vec2(0.5, 0.0) - qt_TexCoord0), 0.0, 1.0);
        gl_FragColor = texture2D(source, vec2(0, len)) * qt_Opacity + rand(qt_TexCoord0) * 0.05;
    }
    "
}

//
//PluginStoreShaderEffect.qml ends here

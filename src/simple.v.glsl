#version 400

layout(location=0) in vec4 in_Position;
layout(location=1) in vec4 in_Color;
uniform mat4 mvp;
uniform float colorFact;
out vec4 ex_Color;

void main(void) {
    gl_Position = mvp * in_Position;
    ex_Color = colorFact*in_Color;
    ex_Color[3] = in_Color[3];
}


#version 400

//attribute vec2 coord2d;
layout(location=0) in vec4 in_Position;
layout(location=1) in vec4 in_Color;
out vec4 ex_Color;

void main(void) { 
    gl_Position = in_Position; 
    ex_Color = in_Color;
}


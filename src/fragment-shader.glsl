#version 400

in vec4 ex_Color;
out vec4 out_Color;

void main(void) {
    out_Color[0] = ex_Color[0];
    out_Color[1] = ex_Color[1];
    out_Color[2] = ex_Color[2];
    out_Color[3] = ex_Color[3];
};

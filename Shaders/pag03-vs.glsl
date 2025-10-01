#version 410
layout (location = 0) in vec posicion;
void main ()
{ gl_Position = vec4 ( posicion, 1 );
}
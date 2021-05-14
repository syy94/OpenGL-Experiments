#version 330 core

in vec3 fragmentColor; // from vertexshader

out vec3 color;

void main(){
  color = fragmentColor;
}
#version 410 core

layout(location = 0) in vec3 vertexPosition_modelspace;
  
uniform mat4 projection;
  
void main(){
    gl_Position = projection * vec4(vertexPosition_modelspace.xy, 0.0, 1.0);
}
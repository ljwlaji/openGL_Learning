#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 textCord;
uniform  mat4 u_MVP;
out vec2 v_TexCord;

void main()
{
    gl_Position = u_MVP * position;
    v_TexCord = textCord; 
}
#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 textCord;
uniform  mat4 u_MVP;
out vec2 v_TexCord;

void main()
{
    gl_Position = u_MVP * vec4(position.x, position.y, 1.0f, 1.0f);
    v_TexCord = textCord; 
}
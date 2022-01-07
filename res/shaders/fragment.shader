#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;
uniform sampler2D u_Texture;  

in vec2 v_TexCord;

void main()
{
  vec4 finalColor = texture(u_Texture, v_TexCord);
  color = finalColor * u_Color;
}
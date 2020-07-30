#shader vertex
#version 330 core

layout(location = 0) in vec3 vertPos;

out vec4 color;

uniform mat4 u_Proj;

void main()
{
	gl_Position = u_Proj * vec4(vertPos, 1.0f);
};

#shader fragment
#version 330 core

out vec4 outColor;

uniform vec4 u_Color;

void main()
{
	outColor = u_Color;
};
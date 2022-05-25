#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aCol;

out vec3 col;
out vec3 pos;

// move
uniform vec3 move;

void main()
{
	gl_Position = vec4(aPos+move, 1.f);
	col = aCol;
	pos = aPos;
}
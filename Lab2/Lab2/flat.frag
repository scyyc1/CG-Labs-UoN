#version 330 core

in vec3 col; 
in vec3 pos;
out vec4 fragColour;

// grey level
uniform float grey_level;

void main()
{
	// normal
	// fragColour = vec4(col, 1.f);

	// grey level
	// fragColour = vec4(grey_level, grey_level, grey_level, 1.f); 

	// Blue-red
	float r = (pos.y>-0.2)? 1.f : 0.8f;
	float b = (pos.y<-0.2)? 1.f : 0.8f;
	fragColour = vec4(r, 0.f, b, 1.0);
}
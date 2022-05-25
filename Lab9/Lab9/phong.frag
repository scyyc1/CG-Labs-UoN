#version 330 core

in vec3 col;
in vec3 nor;
in vec3 FragPos;

uniform vec3 DiretionaLightDir;
uniform vec3 lightColour;
uniform	vec3 lightDirection;
uniform vec3 lightPos;
uniform vec3 camPos;

out vec4 fragColour;

float CalculateDirectionalIllumination()
{
	// ambient light
	float ambient = 0.1f;

	// diffuse light
	vec3 Nnor = normalize(nor);
	vec3 Nto_light = -normalize(DiretionaLightDir);
	float diffuse = max(dot(Nnor, Nto_light), 0);

	// specular light
	vec3 Nfrom_light = normalize(DiretionaLightDir);
	vec3 NrefLight = reflect(Nfrom_light, Nnor);
	vec3 camDirection = camPos - FragPos;
	vec3 NcamDirection = normalize(camDirection);
	float specular = pow(max(dot(NcamDirection, NrefLight), 0), 128);

	// Phong
	float phong = ambient + diffuse + specular;
	return phong;
}

float CalculatePositionalIllumination(){
	// ambient light
	float ambient = 0.1f;

	// diffuse light
	vec3 Nnor = normalize(nor);
	vec3 NToLight = normalize(lightPos - FragPos);
	float diffuse = max(dot(Nnor, NToLight), 0);

	// specular light
	vec3 Nfrom_light = -NToLight;
	vec3 NrefLight = reflect(Nfrom_light, Nnor);
	vec3 camDirection = camPos - FragPos;
	vec3 NcamDirection = normalize(camDirection);
	float specular = pow(max(dot(NcamDirection, NrefLight), 0), 128);

	// attenuation
	float d = length(lightPos - FragPos);
	float att_c = 1.5f, att_l = 0.05, att_q = 0.02;
	float attenuation = 1 / (att_c + (att_l * d) + (att_q * pow(d, 2)));

	// Phong
	float phong = (ambient + diffuse + specular) * attenuation;
	return phong;
}

float CalculateSpotIllumination() {
	// ambient light
	float ambient = 0.1f;

	// diffuse light
	vec3 Nnor = normalize(nor);
	vec3 NToLight = normalize(lightPos - FragPos);
	float diffuse = max(dot(Nnor, NToLight), 0);

	// specular light
	vec3 Nfrom_light = -NToLight;
	vec3 NrefLight = reflect(Nfrom_light, Nnor);
	vec3 camDirection = camPos - FragPos;
	vec3 NcamDirection = normalize(camDirection);
	float specular = pow(max(dot(NcamDirection, NrefLight), 0), 128);

	// attenuation
	float d = length(lightPos - FragPos);
	float att_c = 1.5f, att_l = 0.05, att_q = 0.02;
	float attenuation = 1 / (att_c + (att_l * d) + (att_q * pow(d, 2)));

	// cutoff cone
	float cutoff_cone = cos(radians(15));
	vec3 NSpotDir = normalize(lightDirection);
	float theta = dot(Nfrom_light, NSpotDir);

	// Phong
	float phong = 0.f;
	if(theta > cutoff_cone){
		phong = (ambient + diffuse + specular) * attenuation;
	}else{
		phong = ambient * attenuation;
	}
	return phong;
}

void main()
{
	// Directional illumination
	float phong1 = CalculateDirectionalIllumination();
	// Positional illumination
	float phong2 = CalculatePositionalIllumination();
	// Spot illumination
	float phong3 = CalculateSpotIllumination();

	float phong = phong1 + phong2;

	// result
	fragColour = vec4(phong * col * lightColour, 1.f);
}

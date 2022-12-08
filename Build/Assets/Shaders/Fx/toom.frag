#version 430 core

#define POINT		0
#define DIRECTIONAL	1
#define SPOTLIGHT	2


in vec3 position;
in vec3 normal;
in vec2 texcoord;

out vec4 fcolor;

uniform struct Light
{
	int type; 
	vec3 ambient;
	vec3 color;
	vec4 position;
	vec3 direction;
	float cutoff;
	float exponent;
} light;

uniform struct Material
{
	vec3 color;
	float shininess;
	vec2 uv_tiling;
	vec2 uv_offset;
} material;

int levels = 2;
const float scale_factor = 1.0 / levels;

layout (binding = 0)uniform sampler2D diffuseMap;
//layout (binding = 1)uniform sampler2D specularMap;

void toom(vec3 position, vec3 normal, out vec3 ambient, out vec3 diffuse, out vec3 specular)
{
	vec3 light_dir = (light.type == DIRECTIONAL) ? normalize(-light.direction) : normalize(vec3(light.position) - position);


	float spot_intensity = 1;
	if(light.type == SPOTLIGHT)
	{
		float cosine = dot(light.direction, -light_dir);

		float angle = acos(cosine);

		spot_intensity = (angle < light.cutoff) ? pow(cosine, light.exponent) : 0;
	}

	ambient = light.ambient * material.color;


	float intensity = max(dot(light_dir,normal),0);
	intensity = floor(intensity * levels) * scale_factor;



	diffuse = light.color * material.color * intensity * spot_intensity;


	specular = vec3(0);
//	if(intensity > 0)
//	{
//		vec3 reflection = reflect(-light_dir, normal);
//
//		vec3 view_dir = normalize(-vec3(position));
//
//		intensity = max(dot(reflection,view_dir),0);
//
//		intensity = pow(intensity,material.shininess);
//
//		specular = light.color * material.color * intensity;
//	}
}

void main()
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	toom(position,normal,ambient,diffuse,specular);
	
	fcolor = vec4(ambient + diffuse, 1) + (vec4(specular, 1));
}

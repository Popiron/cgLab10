#pragma once

// Исходный код фрагментного шейдера
const char* FragShaderSource = R"(
    #version 330 core

	in Vertex {
		vec2 texcoord;
		vec3 normal;
		vec3 lightDir;
		vec3 viewDir;
	} Vert;

	uniform struct PointLight {
		vec3 direction;
		vec4 ambient;
		vec4 diffuse;
		vec4 specular;
	} light;

	uniform struct Material {
		vec4 ambient;
		vec4 diffuse;
		vec4 specular;
		vec4 emission;
		float shininess;
	} material;

	uniform sampler2D textureData;

	out vec4 color;

    void main() {
		
		vec3 normal = normalize(Vert.normal);
		vec3 lightDir = normalize(Vert.lightDir);
		vec3 viewDir = normalize(Vert.viewDir);

		color = material.emission;
		color += material.ambient * light.ambient;

		float Ndot = max(dot(normal, lightDir), 0.0);
		color += material.diffuse * light.diffuse * Ndot;

		float RdotVpow = max(pow(dot(reflect(-lightDir, normal), viewDir), material.shininess), 0.0);
		color +=material.specular * light.specular * RdotVpow;

		color *= texture(textureData, Vert.texcoord);

		//color = vec4(Ndot);
    }
)";
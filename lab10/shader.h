#pragma once

// Исходный код вершинного шейдера
const char* VertexShaderSource = R"(
    #version 330 core

	uniform vec3 rotate;
	uniform vec3 move;
	uniform vec3 scale;

	uniform vec3 viewPosition;

	uniform struct PointLight {
		vec3 direction;
		vec4 ambient;
		vec4 diffuse;
		vec4 specular;
	} light;

    in vec3 coord;
	in vec2 texcoord;
	in vec3 normal;

	out Vertex {
		vec2 texcoord;
		vec3 normal;
		vec3 lightDir;
		vec3 viewDir;
	} Vert;

    void main() {

		float x_scale = scale[0];
		float y_scale = scale[1];
		float z_scale = scale[2];

		float x_angle = rotate[0];
        float y_angle = rotate[1];
		float z_angle = rotate[2];

		mat3 scale_matr = mat3(
									x_scale, 0, 0,
									0, y_scale, 0,
									0, 0, z_scale);

        // Поворачиваем вершину
        mat3 rotate = mat3(
            1, 0, 0,
            0, cos(x_angle), -sin(x_angle),
            0, sin(x_angle), cos(x_angle)
        ) * mat3(
            cos(y_angle), 0, sin(y_angle),
            0, 1, 0,
            -sin(y_angle), 0, cos(y_angle)
        ) * mat3(
			cos(z_angle), -sin(z_angle), 0,
			sin(z_angle), cos(z_angle), 0,
			0, 0, 1
		);	

		vec3 vertex = coord * scale_matr * rotate;	

        vec4 vert = vec4(vertex, 1.0);

		float x_move = move[0];
        float y_move = move[1];
		float z_move = move[2];

		mat4 move_matr = mat4(
					1, 0, 0, x_move,
					0, 1, 0, y_move,
					0, 0, 1, z_move,
					0, 0, 0, 1);

		vert *= move_matr;

		float c = -1;

		mat4 perspective_matr = mat4(
					1, 0, 0, 0,
					0, 1, 0, 0,
					0, 0, 1, 0,
					0, 0, -1/c, 1);

		vert *= perspective_matr;

		float last_z = vert.z;
		gl_Position = vec4(vert.xy, last_z * vert[3]/1000, vert[3]);

		Vert.texcoord = texcoord;
		Vert.normal = normal * rotate;
		Vert.lightDir = light.direction;
		Vert.viewDir = viewPosition - vec3(vert);
    }
)";

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
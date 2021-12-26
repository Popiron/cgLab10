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
		vec3 vertex = coord * mat3(
									x_scale, 0, 0,
									0, y_scale, 0,
									0, 0, z_scale);	

		float x_angle = rotate[0];
        float y_angle = rotate[1];
		float z_angle = rotate[2];
        
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

		vertex *= rotate;

		float x_move = move[0];
        float y_move = move[1];
		float z_move = move[2];
        
        vec4 vert = vec4(vertex, 1.0);

		vert *= mat4(
					1, 0, 0, x_move,
					0, 1, 0, y_move,
					0, 0, 1, z_move,
					0, 0, 0, 1);

		float c = -1;
		float last_z = vert.z;
		vert *= mat4(
					1, 0, 0, 0,
					0, 1, 0, 0,
					0, 0, 1, 0,
					0, 0, -1/c, 1);

		gl_Position = vec4(vert.xy, last_z * vert[3] / 100, vert[3]);

		Vert.texcoord = texcoord;
		Vert.normal = normal * rotate;
		Vert.lightDir = light.direction;
		Vert.viewDir = viewPosition - vec3(vert);
    }
)";
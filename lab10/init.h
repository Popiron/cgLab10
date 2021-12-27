#pragma once

#include <gl/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

#include "log.h"
#include "id.h"
#include "source.h"
#include "shader.h"

int road_count = 0;
int bus_count = 0;
int grass_count = 0;
int los_count = 0;
int box_count = 0;

void InitVBO()
{
	std::vector<float> pos_tex;

	loadOBJ("road.obj", pos_tex, road_count);
	glGenBuffers(1, &roadVBO);
	glGenVertexArrays(1, &roadVAO);
	glBindVertexArray(roadVAO);
	glEnableVertexAttribArray(attribVertex);
	glEnableVertexAttribArray(attribTexture);
	glEnableVertexAttribArray(attribNormal);
	glBindBuffer(GL_ARRAY_BUFFER, roadVBO);
	glBufferData(GL_ARRAY_BUFFER, pos_tex.size() * sizeof(GLfloat), pos_tex.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(attribVertex, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(attribTexture, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(attribNormal, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	loadOBJ("bus2.obj",pos_tex, bus_count);
	glGenBuffers(1, &busVBO);
	glGenVertexArrays(1, &busVAO);
	glBindVertexArray(busVAO);
	glEnableVertexAttribArray(attribVertex);
	glEnableVertexAttribArray(attribTexture);
	glEnableVertexAttribArray(attribNormal);
	glBindBuffer(GL_ARRAY_BUFFER, busVBO);
	glBufferData(GL_ARRAY_BUFFER, pos_tex.size() * sizeof(GLfloat), pos_tex.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(attribVertex, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(attribTexture, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(attribNormal, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	loadOBJ("grass.obj",pos_tex, grass_count);
	glGenBuffers(1, &grassVBO);
	glGenVertexArrays(1, &grassVAO);
	glBindVertexArray(grassVAO);
	glEnableVertexAttribArray(attribVertex);
	glEnableVertexAttribArray(attribTexture);
	glEnableVertexAttribArray(attribNormal);
	glBindBuffer(GL_ARRAY_BUFFER, grassVBO);
	glBufferData(GL_ARRAY_BUFFER, pos_tex.size() * sizeof(GLfloat), pos_tex.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(attribVertex, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(attribTexture, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(attribNormal, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	loadOBJ("los.obj", pos_tex, los_count);
	glGenBuffers(1, &losVBO);
	glGenVertexArrays(1, &losVAO);
	glBindVertexArray(losVAO);
	glEnableVertexAttribArray(attribVertex);
	glEnableVertexAttribArray(attribTexture);
	glEnableVertexAttribArray(attribNormal);
	glBindBuffer(GL_ARRAY_BUFFER, losVBO);
	glBufferData(GL_ARRAY_BUFFER, pos_tex.size() * sizeof(GLfloat), pos_tex.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(attribVertex, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(attribTexture, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(attribNormal, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	loadOBJ("box.obj", pos_tex, box_count);
	glGenBuffers(1, &boxVBO);
	glGenVertexArrays(1, &boxVAO);
	glBindVertexArray(boxVAO);
	glEnableVertexAttribArray(attribVertex);
	glEnableVertexAttribArray(attribTexture);
	glEnableVertexAttribArray(attribNormal);
	glBindBuffer(GL_ARRAY_BUFFER, boxVBO);
	glBufferData(GL_ARRAY_BUFFER, pos_tex.size() * sizeof(GLfloat), pos_tex.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(attribVertex, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(attribTexture, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(attribNormal, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	checkOpenGLerror();
}

void InitShader() {
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &VertexShaderSource, NULL);
	glCompileShader(vShader);
	std::cout << "vertex shader \n";
	ShaderLog(vShader);

	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &FragShaderSource, NULL);
	glCompileShader(fShader);
	std::cout << "fragment shader \n";
	ShaderLog(fShader);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vShader);
	glAttachShader(shaderProgram, fShader);

	glLinkProgram(shaderProgram);
	int link_status;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &link_status);
	if (!link_status)
	{
		std::cout << "error attach shaders \n";
		return;
	}

	attribVertex = glGetAttribLocation(shaderProgram, "coord");
	if (attribVertex == -1)
	{
		std::cout << "could not bind attrib coord" << std::endl;
		return;
	}

	attribTexture = glGetAttribLocation(shaderProgram, "texcoord");
	if (attribVertex == -1)
	{
		std::cout << "could not bind attrib texcoord" << std::endl;
		return;
	}

	attribNormal = glGetAttribLocation(shaderProgram, "normal");
	if (attribNormal == -1)
	{
		std::cout << "could not bind attrib normal" << std::endl;
		return;
	}

	unifTexture = glGetUniformLocation(shaderProgram, "textureData");
	if (unifTexture == -1)
	{
		std::cout << "could not bind uniform textureData" << std::endl;
		return;
	}

	unifRotation = glGetUniformLocation(shaderProgram, "rotate");
	if (unifRotation == -1)
	{
		std::cout << "could not bind uniform rotate" << std::endl;
		return;
	}

	unifMovement = glGetUniformLocation(shaderProgram, "move");
	if (unifMovement == -1)
	{
		std::cout << "could not bind uniform move" << std::endl;
		return;
	}

	unifScaling = glGetUniformLocation(shaderProgram, "scale");
	if (unifScaling == -1)
	{
		std::cout << "could not bind uniform scale" << std::endl;
		return;
	}

	unifTransformViewPosition = glGetUniformLocation(shaderProgram, "viewPosition");
	if (unifTransformViewPosition == -1)
	{
		std::cout << "could not bind uniform viewPosition" << std::endl;
		return;
	}

	unifMaterialEmission = glGetUniformLocation(shaderProgram, "material.emission");
	if (unifMaterialEmission == -1)
	{
		std::cout << "could not bind uniform material.emission" << std::endl;
		return;
	}

	unifMaterialAmbient = glGetUniformLocation(shaderProgram, "material.ambient");
	if (unifMaterialAmbient == -1)
	{
		std::cout << "could not bind uniform material.ambient" << std::endl;
		return;
	}

	unifMaterialDiffuse = glGetUniformLocation(shaderProgram, "material.diffuse");
	if (unifMaterialDiffuse == -1)
	{
		std::cout << "could not bind uniform material.diffuse" << std::endl;
		return;
	}

	unifMaterialSpecular = glGetUniformLocation(shaderProgram, "material.specular");
	if (unifMaterialSpecular == -1)
	{
		std::cout << "could not bind uniform material.specular" << std::endl;
		return;
	}

	unifMaterialShininess = glGetUniformLocation(shaderProgram, "material.shininess");
	if (unifMaterialShininess == -1)
	{
		std::cout << "could not bind uniform material.shininess" << std::endl;
		return;
	}

	unifLightAmbient = glGetUniformLocation(shaderProgram, "light.ambient");
	if (unifLightAmbient == -1)
	{
		std::cout << "could not bind uniform light.ambient" << std::endl;
		return;
	}

	unifLightDiffuse = glGetUniformLocation(shaderProgram, "light.diffuse");
	if (unifLightDiffuse == -1)
	{
		std::cout << "could not bind uniform light.diffuse" << std::endl;
		return;
	}

	unifLightSpecular = glGetUniformLocation(shaderProgram, "light.specular");
	if (unifLightSpecular == -1)
	{
		std::cout << "could not bind uniform light.specular" << std::endl;
		return;
	}

	unifLightDirection = glGetUniformLocation(shaderProgram, "light.direction");
	if (unifLightDirection == -1)
	{
		std::cout << "could not bind uniform light.direction" << std::endl;
		return;
	}

	checkOpenGLerror();
}

void InitTexture()
{
	const char* road = "road.png";
	const char* bus = "bus2.png";
	const char* grass = "grass.png";
	const char* los = "los.png";
	const char* box = "box.png";
	if (!busTextureData.loadFromFile(bus))
	{
		std::cout << "could not load texture bus";
		return;
	}
	if (!roadTextureData.loadFromFile(road))
	{
		std::cout << "could not load texture road";
		return;
	}
	if (!grassTextureData.loadFromFile(grass))
	{
		std::cout << "could not load texture grass";
		return;
	}
	if (!losTextureData.loadFromFile(los))
	{
		std::cout << "could not load texture los";
		return;
	}
	if (!boxTextureData.loadFromFile(box))
	{
		std::cout << "could not load texture box";
		return;
	}
	roadTextureHandle = roadTextureData.getNativeHandle();
	busTextureHandle = busTextureData.getNativeHandle();
	grassTextureHandle = grassTextureData.getNativeHandle();
	losTextureHandle = losTextureData.getNativeHandle();
	boxTextureHandle = boxTextureData.getNativeHandle();

}


void Init() {
	InitShader();
	InitVBO();
	InitTexture();
}
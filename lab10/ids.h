#pragma once
#include <GL/glew.h>
#include <SFML/Graphics/Texture.hpp>
#include "models.h"

// ���������� � ����������������� ID
// ID ��������� ���������
GLuint shaderProgram;
// ID �������� ������
GLint attribVertex;
// ID �������� ���������� ���������
GLint attribTexture;
// ID �������� ��������
GLint unifTexture;
// ID ������ ������
GLuint vertexVBO;
// ID ������ ���������� ���������
GLuint textureVBO;

// ID ��������
GLint textureHandle;
// SFML ��������
sf::Texture textureData;

std::vector<Vertex> vertices;
std::vector<Vertex> textures;
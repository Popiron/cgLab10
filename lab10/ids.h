#pragma once
#include <GL/glew.h>
#include <SFML/Graphics/Texture.hpp>
#include "models.h"

// Переменные с индентификаторами ID
// ID шейдерной программы
GLuint shaderProgram;
// ID атрибута вершин
GLint attribVertex;
// ID атрибута текстурных координат
GLint attribTexture;
// ID юниформа текстуры
GLint unifTexture;
// ID буфера ыершин
GLuint vertexVBO;
// ID буфера текстурных координат
GLuint textureVBO;

// ID текстуры
GLint textureHandle;
// SFML текстура
sf::Texture textureData;

std::vector<Vertex> vertices;
std::vector<Vertex> textures;
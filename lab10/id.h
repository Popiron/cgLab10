#pragma once

#include <gl/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

GLuint shaderProgram;

GLint attribVertex;
GLint attribTexture;
GLint attribNormal;

GLint unifRotation;
GLint unifMovement;
GLint unifScaling;

GLuint roadVBO;
GLuint busVBO;
GLuint grassVBO;
GLuint losVBO;
GLuint boxVBO;


GLuint roadVAO;
GLuint busVAO;
GLuint grassVAO;
GLuint losVAO;
GLuint boxVAO;


sf::Texture roadTextureData;
sf::Texture busTextureData;
sf::Texture grassTextureData;
sf::Texture losTextureData;
sf::Texture boxTextureData;

GLint unifTexture;
GLint roadTextureHandle;
GLint busTextureHandle;
GLint grassTextureHandle;
GLint losTextureHandle;
GLint boxTextureHandle;

GLint unifTransformViewPosition;

GLint unifMaterialEmission;
GLint unifMaterialAmbient;
GLint unifMaterialDiffuse;
GLint unifMaterialSpecular;
GLint unifMaterialShininess;

GLint unifLightAmbient;
GLint unifLightDiffuse;
GLint unifLightSpecular;
GLint unifLightAttenuation;
GLint unifLightDirection;
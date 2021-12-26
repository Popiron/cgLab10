#pragma once

#include <gl/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "id.h"

void ReleaseShader() {
	glUseProgram(0);
	glDeleteProgram(shaderProgram);
}

// Освобождение буфера
void ReleaseVBO()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteVertexArrays(1, &roadVAO);
	glDeleteBuffers(1, &roadVBO);

	glDeleteVertexArrays(1, &busVAO);
	glDeleteBuffers(1, &busVBO);
}

void Release() {
	ReleaseShader();
	ReleaseVBO();
}
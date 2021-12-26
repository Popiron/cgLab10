#pragma once

#include <gl/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "id.h"
#include "log.h"
#include "uniforms.h"

void Draw() {
	// Устанавливаем шейдерную программу текущей
	glUseProgram(shaderProgram);

	//material
	glUniform4fv(Unif_material_emission, 1, material.emission);
	glUniform4fv(Unif_material_ambient, 1, material.ambient);
	glUniform4fv(Unif_material_diffuse, 1, material.diffuse);
	glUniform4fv(Unif_material_specular, 1, material.specular);
	glUniform1f(Unif_material_shininess, material.shininess);

	//light
	glUniform4fv(Unif_light_ambient, 1, light.ambient);
	glUniform4fv(Unif_light_diffuse, 1, light.diffuse);
	glUniform4fv(Unif_light_specular, 1, light.specular);
	glUniform3fv(Unif_light_direction, 1, light.direction);

	glUniform3fv(Unif_transform_viewPosition, 1, viewPosition);


	//bus
	glUniform3fv(unifRotate, 1, RotationBus);
	glUniform3fv(unifMove, 1, MovementBus);
	glUniform3fv(unifScale, 1, ScalingBus);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&busTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(busVAO);
	glDrawArrays(GL_TRIANGLES, 0, bus_count);
	glBindVertexArray(0);

	//road1
	glUniform3fv(unifRotate, 1, RotationRoad);
	glUniform3fv(unifMove, 1, MovementRoad1);
	glUniform3fv(unifScale, 1, ScalingRoad);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&roadTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(roadVAO);
	glDrawArrays(GL_TRIANGLES, 0, road_count);
	glBindVertexArray(0);

	//road2
	glUniform3fv(unifRotate, 1, RotationRoad);
	glUniform3fv(unifMove, 1, MovementRoad2);
	glUniform3fv(unifScale, 1, ScalingRoad);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&roadTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(roadVAO);
	glDrawArrays(GL_TRIANGLES, 0, road_count);
	glBindVertexArray(0);

	//road3
	glUniform3fv(unifRotate, 1, RotationRoad);
	glUniform3fv(unifMove, 1, MovementRoad3);
	glUniform3fv(unifScale, 1, ScalingRoad);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&roadTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(roadVAO);
	glDrawArrays(GL_TRIANGLES, 0, road_count);
	glBindVertexArray(0);

	//grassleft1
	glUniform3fv(unifRotate, 1, RotationLeftGrass);
	glUniform3fv(unifMove, 1, MovementLeftGrass1);
	glUniform3fv(unifScale, 1, ScalingGrass);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&grassTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(grassVAO);
	glDrawArrays(GL_TRIANGLES, 0, grass_count);
	glBindVertexArray(0);
	//grassleft2
	glUniform3fv(unifRotate, 1, RotationLeftGrass);
	glUniform3fv(unifMove, 1, MovementLeftGrass2);
	glUniform3fv(unifScale, 1, ScalingGrass);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&grassTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(grassVAO);
	glDrawArrays(GL_TRIANGLES, 0, grass_count);
	glBindVertexArray(0);
	//grassleft3
	glUniform3fv(unifRotate, 1, RotationLeftGrass);
	glUniform3fv(unifMove, 1, MovementLeftGrass3);
	glUniform3fv(unifScale, 1, ScalingGrass);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&grassTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(grassVAO);
	glDrawArrays(GL_TRIANGLES, 0, grass_count);
	glBindVertexArray(0);

	//grassright1
	glUniform3fv(unifRotate, 1, RotationRightGrass);
	glUniform3fv(unifMove, 1, MovementRightGrass1);
	glUniform3fv(unifScale, 1, ScalingGrass);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&grassTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(grassVAO);
	glDrawArrays(GL_TRIANGLES, 0, grass_count);
	glBindVertexArray(0);
	//grassright2
	glUniform3fv(unifRotate, 1, RotationRightGrass);
	glUniform3fv(unifMove, 1, MovementRightGrass2);
	glUniform3fv(unifScale, 1, ScalingGrass);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&grassTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(grassVAO);
	glDrawArrays(GL_TRIANGLES, 0, grass_count);
	glBindVertexArray(0);
	//grassright3
	glUniform3fv(unifRotate, 1, RotationRightGrass);
	glUniform3fv(unifMove, 1, MovementRightGrass3);
	glUniform3fv(unifScale, 1, ScalingGrass);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&grassTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(grassVAO);
	glDrawArrays(GL_TRIANGLES, 0, grass_count);
	glBindVertexArray(0);

	glUseProgram(0);
	checkOpenGLerror();
}
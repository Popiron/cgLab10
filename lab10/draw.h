#pragma once

#include <gl/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "id.h"
#include "log.h"
#include "uniforms.h"

void Draw() {
	glUseProgram(shaderProgram);

	glUniform4fv(unifMaterialEmission, 1, material.emission);
	glUniform4fv(unifMaterialAmbient, 1, material.ambient);
	glUniform4fv(unifMaterialDiffuse, 1, material.diffuse);
	glUniform4fv(unifMaterialSpecular, 1, material.specular);
	glUniform1f(unifMaterialShininess, material.shininess);

	glUniform4fv(unifLightAmbient, 1, light.ambient);
	glUniform4fv(unifLightDiffuse, 1, light.diffuse);
	glUniform4fv(unifLightSpecular, 1, light.specular);
	glUniform3fv(unifLightDirection, 1, light.direction);

	glUniform3fv(unifTransformViewPosition, 1, viewPosition);


	glUniform3fv(unifRotation, 1, RotationBus);
	glUniform3fv(unifMovement, 1, MovementBus);
	glUniform3fv(unifScaling, 1, ScalingBus);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&busTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(busVAO);
	glDrawArrays(GL_TRIANGLES, 0, bus_count);
	glBindVertexArray(0);

	glUniform3fv(unifRotation, 1, RotationRoad);
	glUniform3fv(unifMovement, 1, MovementRoad1);
	glUniform3fv(unifScaling, 1, ScalingRoad);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&roadTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(roadVAO);
	glDrawArrays(GL_TRIANGLES, 0, road_count);
	glBindVertexArray(0);

	glUniform3fv(unifRotation, 1, RotationRoad);
	glUniform3fv(unifMovement, 1, MovementRoad2);
	glUniform3fv(unifScaling, 1, ScalingRoad);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&roadTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(roadVAO);
	glDrawArrays(GL_TRIANGLES, 0, road_count);
	glBindVertexArray(0);

	glUniform3fv(unifRotation, 1, RotationRoad);
	glUniform3fv(unifMovement, 1, MovementRoad3);
	glUniform3fv(unifScaling, 1, ScalingRoad);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&roadTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(roadVAO);
	glDrawArrays(GL_TRIANGLES, 0, road_count);
	glBindVertexArray(0);

	glUniform3fv(unifRotation, 1, RotationLeftGrass);
	glUniform3fv(unifMovement, 1, MovementLeftGrass1);
	glUniform3fv(unifScaling, 1, ScalingGrass);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&grassTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(grassVAO);
	glDrawArrays(GL_TRIANGLES, 0, grass_count);
	glBindVertexArray(0);

	glUniform3fv(unifRotation, 1, RotationLeftGrass);
	glUniform3fv(unifMovement, 1, MovementLeftGrass2);
	glUniform3fv(unifScaling, 1, ScalingGrass);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&grassTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(grassVAO);
	glDrawArrays(GL_TRIANGLES, 0, grass_count);
	glBindVertexArray(0);

	glUniform3fv(unifRotation, 1, RotationLeftGrass);
	glUniform3fv(unifMovement, 1, MovementLeftGrass3);
	glUniform3fv(unifScaling, 1, ScalingGrass);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&grassTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(grassVAO);
	glDrawArrays(GL_TRIANGLES, 0, grass_count);
	glBindVertexArray(0);

	glUniform3fv(unifRotation, 1, RotationRightGrass);
	glUniform3fv(unifMovement, 1, MovementRightGrass1);
	glUniform3fv(unifScaling, 1, ScalingGrass);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&grassTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(grassVAO);
	glDrawArrays(GL_TRIANGLES, 0, grass_count);
	glBindVertexArray(0);

	glUniform3fv(unifRotation, 1, RotationRightGrass);
	glUniform3fv(unifMovement, 1, MovementRightGrass2);
	glUniform3fv(unifScaling, 1, ScalingGrass);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&grassTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(grassVAO);
	glDrawArrays(GL_TRIANGLES, 0, grass_count);
	glBindVertexArray(0);

	glUniform3fv(unifRotation, 1, RotationRightGrass);
	glUniform3fv(unifMovement, 1, MovementRightGrass3);
	glUniform3fv(unifScaling, 1, ScalingGrass);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&grassTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(grassVAO);
	glDrawArrays(GL_TRIANGLES, 0, grass_count);
	glBindVertexArray(0);

	glUniform3fv(unifRotation, 1, RotationLos);
	glUniform3fv(unifMovement, 1, MovementLos);
	glUniform3fv(unifScaling, 1, ScalingLos);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&losTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(losVAO);
	glDrawArrays(GL_TRIANGLES, 0, los_count);
	glBindVertexArray(0);

	glUniform3fv(unifRotation, 1, RotationBox);
	glUniform3fv(unifMovement, 1, MovementBox);
	glUniform3fv(unifScaling, 1, ScalingBox);
	glActiveTexture(GL_TEXTURE0);
	sf::Texture::bind(&boxTextureData);
	glUniform1i(unifTexture, 0);
	glBindVertexArray(boxVAO);
	glDrawArrays(GL_TRIANGLES, 0, box_count);
	glBindVertexArray(0);

	glUseProgram(0);
	checkOpenGLerror();
}
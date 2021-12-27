#include <gl/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "init.h"
#include "release.h"
#include "draw.h"

float RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

bool CollisionDetection(float center[3] , float radius) {
	float distance = sqrt((center[0] - MovementBus[0]) * (center[0] - MovementBus[0]) + (center[1] - MovementBus[1]) * (center[1] - MovementBus[1]) + (center[2] - MovementBus[2]) * (center[2] - MovementBus[2]));
	float RadiusBus = 0.3;
	return distance < (radius + RadiusBus);
}

void GameRestart() {
	MovementBox[2] = -10;
	MovementLos[2] = -10;

	MovementBus[0] = 0.0f;
	MovementBus[1] = -1.0f;
	MovementBus[2] = 0.3f;

	RotationBus[0] = 0.0f;
	RotationBus[1] = -3.14f;
	RotationBus[2] = 0.0f;
}

int main() {
	sf::Window window(sf::VideoMode(700, 700), "Main", sf::Style::Default, sf::ContextSettings(24));
	window.setVerticalSyncEnabled(true);
	window.setActive(true);

	// Инициализация glew
	glewInit();
	glEnable(GL_DEPTH_TEST);

	Init();

	bool moveLeft = false;
	bool moveRight = false;
	bool isLightsOff = false;

	double angle = 0.524;
	double radius = 150.0;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::Resized) {
				glViewport(0, 0, event.size.width, event.size.height);
			}
			else if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
				case (sf::Keyboard::A):
				{
					moveLeft = true;
					break;
				}
				case (sf::Keyboard::D):
				{
					moveRight = true;
					break;
				}
				case (sf::Keyboard::Left):
				{
					if (isLightsOff)
						break;
					light.direction[0] -= 5.0;
					break;
				}
				case (sf::Keyboard::Right):
				{
					if (isLightsOff)
						break;
					angle += 0.1;
					light.direction[0] = radius * std::sin(angle) - 50;
					light.direction[1] = radius * std::cos(angle);
					break;
				}
				case (sf::Keyboard::Up):
				{
					if (isLightsOff)
						break;
					angle -= 0.1;
					light.direction[0] = radius * std::sin(angle) - 50;
					light.direction[1] = radius * std::cos(angle);
					break;
				}
				case (sf::Keyboard::Down):
				{
					if (isLightsOff)
						break;
					light.direction[2] -= 1.0;
					break;
				}
				case (sf::Keyboard::N):
				{
					if (isLightsOff) {
						light.direction[0] = 0.0f;
						light.direction[1] = 80.0f;
						light.direction[2] = -150.0f;
					}
					else {
						light.direction[0] = 0.0f;
						light.direction[1] = 0.0f;
						light.direction[2] = 0.0f;
					}
					isLightsOff = !isLightsOff;
					break;
				}
				default: break;
				}
			}
			else if (event.type == sf::Event::KeyReleased) {
				switch (event.key.code) {
				case (sf::Keyboard::A):
				{
					moveLeft = false;
					break;
				}
				case (sf::Keyboard::D):
				{
					moveRight = false;
					break;
				}
				default: break;
				}
			}
		}

		if (moveLeft && MovementBus[0]>=-1.3)
		{
			MovementBus[0] -= 0.05;
			RotationBus[1] -= 0.04;
		}
		if (moveRight && MovementBus[0] <= 1.3)
		{
			MovementBus[0] += 0.05;
			RotationBus[1] += 0.04;
		}

		if (RotationBus[1] < -3.14f && std::abs(RotationBus[1] + 3.14) > 0.05f)
			RotationBus[1] += 0.03f;
		else if (RotationBus[1] > -3.14f && std::abs(RotationBus[1] + 3.14) > 0.05f)
			RotationBus[1] -= 0.03f;
		if (std::abs(MovementBus[1] + 0.25) < 0.01f)
			MovementBus[1] += 1.0f;

		MovementRoad1[2] -= 0.1;
		MovementRoad2[2] -= 0.1;
		MovementRoad3[2] -= 0.1;
		if (std::abs(MovementRoad1[2] + 10) < 0.1)
			MovementRoad1[2] = 10 + std::abs(MovementRoad1[2] + 10);
		if (std::abs(MovementRoad2[2] - 10) < 0.1)
			MovementRoad2[2] = 30 + std::abs(MovementRoad2[2] - 10);
		if (std::abs(MovementRoad3[2] - 30) < 0.1)
			MovementRoad3[2] = 50 + std::abs(MovementRoad3[2] - 30);

		MovementLeftGrass1[2] -= 0.1;
		MovementLeftGrass2[2] -= 0.1;
		MovementLeftGrass3[2] -= 0.1;
		MovementRightGrass1[2] -= 0.1;
		MovementRightGrass2[2] -= 0.1;
		MovementRightGrass3[2] -= 0.1;

		if (std::abs(MovementLeftGrass1[2] + 10) < 0.1)
			MovementLeftGrass1[2] = 10 + std::abs(MovementLeftGrass1[2] + 10);
		if (std::abs(MovementLeftGrass2[2] - 10) < 0.1)
			MovementLeftGrass2[2] = 30 + std::abs(MovementLeftGrass2[2] - 10);
		if (std::abs(MovementLeftGrass3[2] - 30) < 0.1)
			MovementLeftGrass3[2] = 50 + std::abs(MovementLeftGrass3[2] - 30);

		if (std::abs(MovementRightGrass1[2] + 10) < 0.1)
			MovementRightGrass1[2] = 10 + std::abs(MovementRightGrass1[2] + 10);
		if (std::abs(MovementRightGrass2[2] - 10) < 0.1)
			MovementRightGrass2[2] = 30 + std::abs(MovementRightGrass2[2] - 10);
		if (std::abs(MovementRightGrass3[2] - 30) < 0.1)
			MovementRightGrass3[2] = 50 + std::abs(MovementRightGrass3[2] - 30);

		if (MovementLos[2] >= 0.1)
			MovementLos[2] -= 0.1;

		if (MovementBox[2] >= 0.1)
			MovementBox[2] -= 0.1;

		if (CollisionDetection(MovementLos, 0.1))
		{
			std::cout << "Los collision detection. Restart game" << std::endl;
			GameRestart();
		}
		

		if (CollisionDetection(MovementBox, 0.1))
		{
			std::cout << "Box collision detection. Restart game" << std::endl;
			GameRestart();
		}

		if (MovementLos[2] < 0.1 && MovementBox[2] < 0.1) {
			int b = rand() % 2;
			if (b) {
				MovementLos[2] = 50;
				MovementLos[0] = RandomFloat(-1.3, 1.3);

				MovementBox[2] = -10;
			}
			else {
				MovementBox[2] = 50;
				MovementBox[0] = RandomFloat(-1.3, 1.3);

				MovementLos[2] = -10;

			}
		}
			

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Draw();

		window.display();
	}

	Release();
	return 0;
}


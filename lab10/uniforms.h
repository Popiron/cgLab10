#pragma once

float busRotate[3] = { 0.0f, -3.14f, 0.0f };
float busMove[3] = { 0.0f, -1.0f, 0.7f };
float busScale[3] = { 0.07f, 0.07f, 0.07f };

float road1Move[3] = { 0.0f, -1.0f, 10.0f };
float road2Move[3] = { 0.0f, -1.0f, 30.0f };
float road3Move[3] = { 0.0f, -1.0f, 50.0f };
float roadRotate[3] = { 0.0f, 0.0f, 0.0f };
float roadScale[3] = { 0.1f, 0.1f, 0.1f };

float grassLeftRotate[3] = { 0.0f, -3.1415f, 0.0f };
float grassRightRotate[3] = { 0.0f, 0.0f, 0.0f };
float grassLeft1Move[3] = { -11.5f, -1.0f, 10.0f };
float grassLeft2Move[3] = { -11.5f, -1.0f, 30.0f };
float grassLeft3Move[3] = { -11.5f, -1.0f, 50.0f };
float grassRight1Move[3] = { 11.5f, -1.0f, 10.0f };
float grassRight2Move[3] = { 11.5f, -1.0f, 30.0f };
float grassRight3Move[3] = { 11.5f, -1.0f, 50.0f };
float grassScale[3] = { 0.1f, 0.1f, 0.1f };

float skyRotate[3] = { -1.7f, 0.0f, 3.1415f };
float skyMove[3] = { 0.0f, 23.0f, 30.0f };
float skyScale[3] = { 100.0f, 20.0f, 50.0f };

float viewPosition[3] = { 0.0, 0.0, -100.0 };

struct Material
{
	float emission[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	float ambient[4] = { 0.1f, 0.1f, 0.1f , 1.0f };
	float diffuse[4] = { 1.0f, 1.0f, 1.0f , 1.0f };
	float specular[4] = { 1.0f, 1.0f, 1.0f , 1.0f };
	float shininess = 128.0f;
};
Material material;

struct Light
{
	float ambient[4] = { 0.1f, 0.1f, 0.1f , 1.0f };
	float diffuse[4] = { 0.9f, 0.9f, 0.9f , 1.0f };
	float specular[4] = { 1.0f, 1.0f, 1.0f , 1.0f };
	float direction[3] = { 0.0f, 80.0f, -150.0f };
};
Light light;
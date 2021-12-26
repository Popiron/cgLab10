#pragma once

float MovementBus[3] = { 0.0f, -1.0f, 0.3f };
float RotationBus[3] = { 0.0f, -3.14f, 0.0f };
float ScalingBus[3] = { 0.1f, 0.1f, 0.1f };

float MovementRoad1[3] = { 0.0f, -1.0f, 10.0f };
float MovementRoad2[3] = { 0.0f, -1.0f, 30.0f };
float MovementRoad3[3] = { 0.0f, -1.0f, 50.0f };
float RotationRoad[3] = { 0.0f, 0.0f, 0.0f };
float ScalingRoad[3] = { 0.1f, 0.1f, 0.1f };

float MovementLeftGrass1[3] = { -11.5f, -1.0f, 10.0f };
float MovementLeftGrass2[3] = { -11.5f, -1.0f, 30.0f };
float MovementLeftGrass3[3] = { -11.5f, -1.0f, 50.0f };

float MovementRightGrass1[3] = { 11.5f, -1.0f, 10.0f };
float MovementRightGrass2[3] = { 11.5f, -1.0f, 30.0f };
float MovementRightGrass3[3] = { 11.5f, -1.0f, 50.0f };

float RotationLeftGrass[3] = { 0.0f, -3.1415f, 0.0f };
float RotationRightGrass[3] = { 0.0f, 0.0f, 0.0f };

float ScalingGrass[3] = { 0.1f, 0.1f, 0.1f };

float viewPosition[3] = { 0.0, 0.0, -100.0f };

struct Material
{
	float ambient[4] = { 0.1f, 0.1f, 0.1f , 1.0f };
	float diffuse[4] = { 1.0f, 1.0f, 1.0f , 1.0f };
	float specular[4] = { 1.0f, 1.0f, 1.0f , 1.0f };
	float emission[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	float shininess = 100.0f;
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
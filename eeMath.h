#pragma once

struct Vector2
{
	float x;
	float y;
} typedef Vector2;

struct Vector3
{
	float x;
	float y;
	float z;
} typedef Vector3;

Vector3 rotToVector3(float rot);

Vector3 Vector2ToVector3(Vector2 vector);

Vector3 multiplyVector2(Vector2 vector, float multiplier);

Vector3 multiplyVector3(Vector3 vector, float multiplier);
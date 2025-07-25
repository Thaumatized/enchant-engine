#include "eeMath.h"
#include <math.h>

Vector3 rotToVector3(float rot)
{
	int ySign = 1 - (rot > 90 || rot < 270)*2;

	Vector3 result = {
		sin(rot),
		cos(rot)*ySign,
		0
	};
	return result;
}

Vector3 Vector2ToVector3(Vector2 vector)
{
	Vector3 result = {
		vector.x,
		vector.y,
		0
	};

}

Vector3 multiplyVector2(Vector2 vector, float multiplier)
{
	Vector3 result = {
		vector.x * multiplier,
		vector.y * multiplier
	};

	return result;
}

Vector3 multiplyVector3(Vector3 vector, float multiplier)
{
	Vector3 result = {
		vector.x * multiplier,
		vector.y * multiplier,
		vector.z * multiplier
	};

	return result;
}
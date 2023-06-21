#include "pch.h"
#include "curves.h"
#include <cmath>

#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif

Vector3D Ellipse::GetPoint(double t)
{
	Vector3D point;
	point._x = GetRadiusX() * cos(t);
	point._y = GetRadiusY() * sin(t);
	point._z = 0;
	return point;
}

Vector3D Ellipse::GetVector(double t)
{
	Vector3D vector;
	vector._x = GetRadiusX() * cos(t + M_PI/2);
	vector._y = GetRadiusY() * sin(t + M_PI/2);
	vector._z = 0;
	return vector;
}

Vector3D Helix::GetPoint(double t)
{
	Vector3D point = Circle::GetPoint(t);
	point._z = GetStep()*(t/(M_PI*2));
	return point;
}

Vector3D Helix::GetVector(double t)
{
	Vector3D vector = Circle::GetVector(t);
	vector._z = GetStep() / (M_PI * 2);
	return vector;
}
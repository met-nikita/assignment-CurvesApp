#pragma once

#ifdef CURVESLIBRARY_EXPORTS
#define CURVESLIBRARY_API __declspec(dllexport)
#else
#define CURVESLIBRARY_API __declspec(dllimport)
#endif

#define Ellipse EllipseA //conflicts with win includes otherwise

struct CURVESLIBRARY_API Vector3D
{
	Vector3D(double x, double y, double z) : _x(x), _y(y), _z(z) {};
	Vector3D() : _x(0), _y(0), _z(0) {};
	double _x;
	double _y;
	double _z;
};

enum CURVESLIBRARY_API CurveType
{
	CT_Ellipse,
	CT_Circle,
	CT_Helix,
	CT_MAX
};

class CURVESLIBRARY_API Curve
{
public:
	virtual Vector3D GetPoint(double t) = 0;
	virtual Vector3D GetVector(double t) = 0;
	virtual CurveType GetCurveType() = 0;
};

class CURVESLIBRARY_API Ellipse : public Curve
{
public:
	Ellipse(double radiusX, double radiusY) : _radiusX(radiusX), _radiusY(radiusY) {};
	virtual Vector3D GetPoint(double t);
	virtual Vector3D GetVector(double t);
	virtual CurveType GetCurveType() { return CT_Ellipse; }
	double GetRadiusX() { return _radiusX; }
	double GetRadiusY() { return _radiusY; }
private:
	double _radiusX;
	double _radiusY;
};

class CURVESLIBRARY_API Circle : public Ellipse
{
public:
	Circle(double radius) : Ellipse(radius, radius) {};
	virtual CurveType GetCurveType() { return CT_Circle; }
	double GetRadius() { return GetRadiusX(); }
};

class CURVESLIBRARY_API Helix : public Circle
{
public:
	Helix(double radius, double step) : Circle(radius), _step(step) {};
	virtual Vector3D GetPoint(double t);
	virtual Vector3D GetVector(double t);
	virtual CurveType GetCurveType() { return CT_Helix; }
	double GetStep() { return _step; }
private:
	double _step;
};
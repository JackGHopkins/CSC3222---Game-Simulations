#pragma once
#include "CollisionVolume.h"
#include "SimObject.h"
#include "Square.h"

using namespace NCL::CSC3222;

/// <summary>
///		Class for the Circle Shape.
/// </summary>
class Circle : public CollisionVolume {
public:
	/* CONSTRUCTORS & DESTRUCTORS*/
	Circle(float posX, float posY, SimObject* object, float radius);
	~Circle();

	/* METHODS */
	float GetRadius() const;
	bool PointWithinRadius(float posX, float posY) const;
	bool CheckCollision(CollisionVolume& Other);
private:
	float radius;
};

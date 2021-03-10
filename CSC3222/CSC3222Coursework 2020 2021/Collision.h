#pragma once
#include "Circle.h"
#include "Square.h"

/// <summary>
///		For checking collisions between Shapes.
/// </summary>
class Collision {
public:
	void CollisionDetection(std::vector<CollisionVolume*> allColliders);
	bool isCollision(Circle& c1, Circle& c2);
	bool isCollision(Square& s1, Square& s2);
	bool isCollision(Circle& c, Square& s);
	bool IsSameShapeCollide(float x1, float y1, float r1, float x2, float y2, float r2) const;
};

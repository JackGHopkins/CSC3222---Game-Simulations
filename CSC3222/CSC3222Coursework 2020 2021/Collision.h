#pragma once
#include "Circle.h"
#include "Box.h"

/// <summary>
///		For checking collisions between Shapes.
/// </summary>
class Collision {
public:
	bool isCollision(Circle& c1, Circle& c2);
	bool isCollision(Box& s1, Box& s2);
	bool isCollision(Circle& c, Box& s);
	bool IsSameShapeCollide(float x1, float y1, float r1, float x2, float y2, float r2) const;
};

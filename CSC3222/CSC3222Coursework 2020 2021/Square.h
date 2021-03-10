#pragma once
#include "Circle.h"
#include "CollisionVolume.h"
#include "SimObject.h"

using namespace NCL::CSC3222;
using namespace NCL::Maths;

/// <summary>
///		Class for the Square Shape.
/// </summary>
class Square : public CollisionVolume {
public:
	/* CONSTRUCTOR & DESTRUCTOR */
	Square(float posX, float posY, SimObject* object,  Vector2 length);
	~Square();

	/* METHODS */
	Vector2 GetHalfLength() const;
	bool CheckCollision(CollisionVolume& Other);
private:
	Vector2 halfLength;
};
	
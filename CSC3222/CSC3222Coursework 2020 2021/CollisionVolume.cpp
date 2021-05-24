#include "CollisionVolume.h"

using namespace NCL::CSC3222;
using namespace NCL::Maths;

CollisionVolume::CollisionVolume() {}

CollisionVolume::CollisionVolume(float posX, float posY, Vector2 halfLength, SimObject* object) :
	posX(posX),
	posY(posY),
	halfLength(halfLength),
	object(object) {};


// Copy Constructor
CollisionVolume::CollisionVolume(float posX, float posY, Vector2 halfLength) :
	posX(posX),
	posY(posY), 
	halfLength(halfLength) {};

CollisionVolume::~CollisionVolume() {}

float CollisionVolume::GetPosX() const { 
	if (object)
		return object->GetPosition().x;
	else
		return posX;
}

float CollisionVolume::GetPosY() const {
	if (object)
		return object->GetPosition().y;
	else
		return posY;
}

Vector2 CollisionVolume::GetPosition() const {
	if (object)
		return object->GetPosition();
	else
		return Vector2(posX, posY);
}

SimObject* CollisionVolume::GetObject() const {
	return object;
}

Vector2 CollisionVolume::GetHalfLength() const { return halfLength; }

void CollisionVolume::SetPosX(float x) { this->posX = x; }

void CollisionVolume::SetPosY(float y) { this->posY = y; }

void CollisionVolume::SetHalfLength(const Vector2 halfLength) { this->halfLength = halfLength; }

/* Moves CollisionVolume to a new position in the grid. */
void CollisionVolume::Transform(float newX, float newY) {
	this->SetPosX(newX);
	this->SetPosY(newY);
}

#include "CollisionVolume.h"
using namespace NCL::CSC3222;
using namespace NCL::Maths;

CollisionVolume::CollisionVolume() {}

CollisionVolume::CollisionVolume(std::string name, BOUND_TYPE boundType, float posX, float posY, Vector2 halfLength, SimObject* object, COLLISION_STATE collisionState) :
	name(name),
	boundType(boundType),
	posX(posX),
	posY(posY),
	halfLength(halfLength),
	object(object), 
	collisionState(collisionState) {};


// Copy Constructor
CollisionVolume::CollisionVolume(std::string name, BOUND_TYPE boundType, float posX, float posY, Vector2 halfLength, COLLISION_STATE collisionState) :
	name(name),
	boundType(boundType),
	posX(posX),
	posY(posY),
	halfLength(halfLength),
	collisionState(collisionState) {};

// Constructor for when you don't want to update the collisionState
CollisionVolume::CollisionVolume(std::string name, BOUND_TYPE boundType, float posX, float posY, Vector2 halfLength, SimObject* object) :
	name(name),
	boundType(boundType),
	posX(posX),
	posY(posY),
	halfLength(halfLength),
	object(object) {};

// Constructor for when you don't want to update the collisionState
CollisionVolume::CollisionVolume(std::string name, BOUND_TYPE boundType, float posX, float posY, Vector2 halfLength) :
	name(name),
	boundType(boundType),
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

std::string CollisionVolume::GetName() const {
	return name;
}

CollisionVolume::BOUND_TYPE CollisionVolume::GetBoundType() const {
	return boundType;
}

CollisionVolume::COLLISION_STATE CollisionVolume::GetCollisionState() const {
	return collisionState;
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

void CollisionVolume::SetCollisionState(const CollisionVolume::COLLISION_STATE collisionState) { this->collisionState = collisionState; }

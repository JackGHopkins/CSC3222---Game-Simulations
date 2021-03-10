#include "CollisionVolume.h"

using namespace NCL::CSC3222;

CollisionVolume::CollisionVolume(float posX, float posY, SimObject* object) :
	posX(posX),
	posY(posY), 
	object(object) {};

CollisionVolume::~CollisionVolume() {}

float CollisionVolume::GetPosX() const { return object->GetPosition().x; }

float CollisionVolume::GetPosY() const { return object->GetPosition().y; }

void CollisionVolume::SetPosX(float x) { this->posX = x; }

void CollisionVolume::SetPosY(float y) { this->posY = y; }

/* Moves CollisionVolume to a new position in the grid. */
void CollisionVolume::Transform(float newX, float newY) {
	this->SetPosX(newX);
	this->SetPosY(newY);
}

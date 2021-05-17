#include "CollisionCouple.h"

CollisionCouple::CollisionCouple(float penDistance, RigidBody* rB1, RigidBody* rB2, CollisionVolume* cV1, CollisionVolume* cV2, Vector2 collisionNormal)
{
	this->rB1 = rB1;
	this->rB2 = rB2;
	this->cV1 = cV1;
	this->cV2 = cV2;
	this->penDistance = FindPenDist(rB1, rB2);
	this->collisionNormal = CollisionNormal(rB1, rB2);
}

CollisionCouple::~CollisionCouple(){}

float CollisionCouple::FindPenDist(RigidBody* rB1, RigidBody* rB2) {
}

Vector2 CollisionCouple::CollisionNormal(RigidBody * rB1, RigidBody * rB2) {
	Vector2 v = Vector2(2,3);
	v.d

}
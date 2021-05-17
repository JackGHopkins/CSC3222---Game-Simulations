#pragma once
#include "GameSimsPhysics.h"
#include "RigidBody.h"
#include "CollisionVolume.h"
#include "QuadTree.h"
#include "../../Common/Vector2.h"

struct CollisionCouple {

	CollisionCouple(float penDistance, RigidBody* rB1, RigidBody* rB2, CollisionVolume* cV1, CollisionVolume* cV2, Vector2 collisionNormal);
	~CollisionCouple();

	float FindPenDist(RigidBody* rB1, RigidBody* rB2);
	Vector2 CollisionNormal(RigidBody * rB1, RigidBody * rB2);

	float penDistance;
	RigidBody* rB1;
	RigidBody* rB2;
	CollisionVolume* cV1;
	CollisionVolume* cV2;
	Vector2 collisionNormal;
};

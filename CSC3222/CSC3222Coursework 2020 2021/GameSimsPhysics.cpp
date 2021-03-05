#include "GameSimsPhysics.h"
#include "RigidBody.h"
#include "CollisionVolume.h"
#include "../../Common/Vector2.h"

using namespace NCL;
using namespace CSC3222;

GameSimsPhysics::GameSimsPhysics()	{

}

GameSimsPhysics::~GameSimsPhysics()	{

}

void GameSimsPhysics::Update(float dt) {
	IntegrationAcceleration(dt);
	CollisionDetection(dt);
	IntegrationVelocity(dt);

	for (auto it : allBodies) {
		it->force = Vector2(0, 0);
	}
}

void GameSimsPhysics::AddRigidBody(RigidBody* b) {
	allBodies.emplace_back(b);
}

void GameSimsPhysics::RemoveRigidBody(RigidBody* b) {
	auto at = std::find(allBodies.begin(), allBodies.end(), b);

	if (at != allBodies.end()) {
		//maybe delete too?
		allBodies.erase(at);
	}
}

void GameSimsPhysics::AddCollider(CollisionVolume* c) {
	allColliders.emplace_back(c);
}

void GameSimsPhysics::RemoveCollider(CollisionVolume* c) {
	auto at = std::find(allColliders.begin(), allColliders.end(), c);

	if (at != allColliders.end()) {
		//maybe delete too?
		allColliders.erase(at);
	}
}

void GameSimsPhysics::IntegrationAcceleration(float dt) {
	for (auto i : allBodies) {
		Vector2 accleration = i->force * i->inverseMass;
		i->velocity += accleration * dt;
	}
}

void GameSimsPhysics::IntegrationVelocity(float dt) {
	for (auto i : allBodies) {
		i->position = i->position + i->velocity;
		i->velocity *= 0.6;
	}
}

void GameSimsPhysics::CollisionDetection(float dt) {

}
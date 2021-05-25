#include "GameSimsPhysics.h"
#include "RigidBody.h"
#include "CollisionCouple.h"
#include "CollisionVolume.h"
#include "QuadTree.h"
#include "../../Common/Vector2.h"

using namespace NCL;
using namespace CSC3222;

GameSimsPhysics::GameSimsPhysics()	{

}

GameSimsPhysics::~GameSimsPhysics()	{

}

void GameSimsPhysics::Update(float dt) {
	IntegrationAcceleration(dt);
	CollisionDetection();
	CollisionResolution();
	IntegrationVelocity(dt);

	for (auto it : allBodies) {
		it->force = Vector2(0, 0);
	}

	DeleteCollisions();
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

void GameSimsPhysics::UpdateCollider(CollisionVolume* c) {
	for (int i = 0; i < allColliders.size(); i++) {
		if (allColliders[i] == c)
			allColliders[i] = c;			
	}
}

void GameSimsPhysics::RemoveCollider(CollisionVolume* c) {
	auto at = std::find(allColliders.begin(), allColliders.end(), c);

	if (at != allColliders.end()) {
		//maybe delete too?
		allColliders.erase(at);
	}
}

void GameSimsPhysics::DeleteCollisions() {
	for (int i = 0; i < allCollisions.size(); i++) {
		delete allCollisions[i];
	} 
	allCollisions.clear();
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
		i->velocity *= 0.9 * dt;
	}
}

void GameSimsPhysics::CollisionDetection() {
	int k = 0;
	QuadTree quadTree = QuadTree(0, Box("MainQuad",0, 0, Vector2(480, 320), CollisionVolume::COLLISION_STATE::null));

	quadTree.Clear();

	for (int i = 0; i < allColliders.size(); i++)
		quadTree.Insert(allColliders[i]);

	std::vector<CollisionVolume*> retrievedObjects;
	for (int i = 0; i < allColliders.size(); i++) {
		retrievedObjects.clear();
		retrievedObjects = quadTree.RetrieveObjects(retrievedObjects, allColliders[i]);

		for (int j = i + 1; j < retrievedObjects.size(); j++) {
			if (retrievedObjects[j]->CheckCollision(*retrievedObjects[i])) {
				std::cout << "Collision between: [" << allColliders[i]->GetName() << "," << allColliders[j]->GetName() << "]" << std::endl;
				allCollisions.push_back(new CollisionCouple(allColliders[i], allColliders[j]));

				// Change state to grounded if touching the floor
				if (allColliders[i]->GetCollisionState() == CollisionVolume::COLLISION_STATE::floor && allColliders[j]->GetCollisionState() == CollisionVolume::COLLISION_STATE::airborn)
					allColliders[j]->SetCollisionState(CollisionVolume::COLLISION_STATE::grounded);

				if (allColliders[i]->GetCollisionState() == CollisionVolume::COLLISION_STATE::airborn && allColliders[j]->GetCollisionState() == CollisionVolume::COLLISION_STATE::floor)
					allColliders[i]->SetCollisionState(CollisionVolume::COLLISION_STATE::grounded);
					
			}
		}
	}
}

void GameSimsPhysics::CollisionResolution() {
	for (CollisionCouple* i : allCollisions) {
		CollisionResponse(i->cV1, i->cV2, i->collisionNormal, i->penDistance);
	}
}

void GameSimsPhysics::CollisionResponse(CollisionVolume* cV1, CollisionVolume* cV2, Vector2 collisionNormal, float penDistance) {
	Vector2 cV1Vel = (cV1->GetObject() != NULL) ? cV1->GetObject()->GetVelocity() : Vector2(0.0f, 0.0f);
	Vector2 cV2Vel = (cV2->GetObject() != NULL) ? cV2->GetObject()->GetVelocity() : Vector2(0.0f, 0.0f);
	Vector2 deltaVel = cV1Vel - cV2Vel;

	if (!cV1->GetObject() && !cV2->GetObject())
		return;

	if (!cV1->GetObject()) 
	{
		cV2->GetObject()->AddProjection(collisionNormal, penDistance, 0.0f);
		//cV2->GetObject()->GetPosition() += collisionNormal * penDistance;
		cV2->GetObject()->AddImpluse(deltaVel, collisionNormal, 0.0f);
	}
	else if (!cV2->GetObject())
	{
		cV1->GetObject()->AddProjection(-collisionNormal, penDistance, 0.0f);
		//cV1->GetObject()->GetPosition() += collisionNormal * penDistance;
		cV1->GetObject()->AddImpluse(-deltaVel, collisionNormal, 0.0f);
	}
	else if (cV1->GetObject() && cV2->GetObject())
	{
		float cV1IM = cV1->GetObject()->GetInverseMass();
		float cV2IM = cV2->GetObject()->GetInverseMass();

		//cV1->GetObject()->SetPosition(cV1->GetObject()->GetPosition() - collisionNormal * penDistance * (cV1IM / (cV1IM + cV2IM)));
		//cV2->GetObject()->SetPosition(cV2->GetObject()->GetPosition() - collisionNormal * penDistance * (cV2IM / (cV1IM + cV2IM)));

		cV1->GetObject()->AddProjection(-collisionNormal, penDistance, cV2->GetObject()->GetInverseMass());
		cV1->GetObject()->AddImpluse(deltaVel, collisionNormal, cV2->GetObject()->GetInverseMass());

		cV2->GetObject()->AddProjection(collisionNormal, penDistance, cV1->GetObject()->GetInverseMass());
		cV2->GetObject()->AddImpluse(-deltaVel, collisionNormal, cV1->GetObject()->GetInverseMass());
	}
}


	//int size = allColliders.size();
	//for (int i = 0; i < size; i++) {
	//	for (int j = i + 1; j < size; j++) {

	//		if (allColliders[i]->CheckCollision(*allColliders[j]))
	//			std::cout << "Collision between: [" << allColliders[i] << "," << allColliders[j] << "]" << std::endl;
	//	}
	//}

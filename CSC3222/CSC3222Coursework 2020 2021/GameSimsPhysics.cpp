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
	CollisionResolution(dt);
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
	QuadTree quadTree = QuadTree(0, Box(0, 0, Vector2(480, 320)));

	quadTree.Clear();

	for (int i = 0; i < allColliders.size(); i++)
		quadTree.Insert(allColliders[i]);

	std::vector<CollisionVolume*> retrievedObjects;
	for (int i = 0; i < allColliders.size(); i++) {
		retrievedObjects.clear();
		retrievedObjects = quadTree.RetrieveObjects(retrievedObjects, allColliders[i]);

		for (int j = 0; j < retrievedObjects.size(); j++) {
			for (int k = j + 1; k < retrievedObjects.size(); k++) {
				if (retrievedObjects[j]->CheckCollision(*retrievedObjects[k])) {
					std::cout << "Collision between: [" << allColliders[i] << "," << allColliders[j] << "]" << std::endl;
					allCollisions[k] = new CollisionCouple(allColliders[i], allColliders[j], allBodies[i], allBodies[j], );
				}
			}
		}
	}
}

void GameSimsPhysics::CollisionResolution(float dt) {
	// Impluse();
	/*
	
				-(1+e) * (v1 - v2) * Normalised Collision Pair
			J =	______________________________________________
				(inverse mass A * invers mass B)

		vA = vA - inverse mA * J * normalised Collision Pair
		vB = vB - inverse mB * J * normalised Collision Pair

	*/
	


}


	//int size = allColliders.size();
	//for (int i = 0; i < size; i++) {
	//	for (int j = i + 1; j < size; j++) {

	//		if (allColliders[i]->CheckCollision(*allColliders[j]))
	//			std::cout << "Collision between: [" << allColliders[i] << "," << allColliders[j] << "]" << std::endl;
	//	}
	//}
}
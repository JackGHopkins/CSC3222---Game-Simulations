#pragma once
#include <vector>
#include "CollisionCouple.h"
#include "../../Common/Vector2.h"

namespace NCL {
	namespace CSC3222 {
		class RigidBody;
		class CollisionVolume;

		class GameSimsPhysics	{
		public:
			GameSimsPhysics();
			~GameSimsPhysics();

			void Update(float dt);

			void AddRigidBody(RigidBody* b);
			void RemoveRigidBody(RigidBody* b);

			void AddCollider(CollisionVolume* c);
			void UpdateCollider(CollisionVolume* c);
			void RemoveCollider(CollisionVolume* c);

			void DeleteCollisions();

		protected:
			void IntegrationAcceleration(float dt);
			void IntegrationVelocity(float dt);
			void CollisionDetection();
			void CollisionResolution(float dt);

			std::vector<RigidBody*>			allBodies;
			std::vector<CollisionVolume*>	allColliders;
			std::vector<CollisionCouple*>	allCollisions;
		};
	}
}


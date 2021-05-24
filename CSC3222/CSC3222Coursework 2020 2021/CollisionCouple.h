#pragma once
#include "GameSimsPhysics.h"
#include "RigidBody.h"
#include "CollisionVolume.h"
#include "QuadTree.h"
#include "../../Common/Vector2.h"

/// <summary>
///		Storing information about the collisions.
/// </summary>
namespace NCL {
	namespace CSC3222 {
		struct CollisionCouple {

			CollisionCouple(CollisionVolume* cV1, CollisionVolume* cV2);
			~CollisionCouple();

			void FindParameters(CollisionVolume* cV1, CollisionVolume* cV2);

			float penDistance;
			CollisionVolume* cV1;
			CollisionVolume* cV2;
			Vector2 collisionNormal;
		};
	}
}

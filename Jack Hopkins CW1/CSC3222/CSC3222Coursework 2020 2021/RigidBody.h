#pragma once
#include "../../Common/Vector2.h"

namespace NCL {
	using namespace Maths;
	namespace CSC3222 {
		class RigidBody	{
			friend class GameSimsPhysics;
		public:
			RigidBody();
			~RigidBody();

			Vector2 GetPosition() const {
				return position;
			}

			void SetPosition(const Vector2& newPosition) {
				position = newPosition;
			}

			Vector2 GetVelocity() const {
				return velocity;
			}

			void SetVelocity(const Vector2& newVelocity) {
				velocity = newVelocity;
			}

			Vector2 GetForce() const {
				return force;
			}

			void SetForce(const Vector2& newForce) {
				force = newForce;
			}

			void AddForce(const Vector2& newForce) {
				force += newForce;
			}



		protected:
			Vector2 position;
			Vector2 velocity;
			Vector2 force;

			float inverseMass;
			float elasticity;

		};
	}
}

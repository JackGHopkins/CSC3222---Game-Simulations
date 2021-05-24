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

			float GetInverseMass() const {
				return inverseMass;
			}

			void AddForce(const Vector2& newForce) {
				force += newForce;
			}

			void AddProjection(const Vector2& collisionNormal, const float penetration, const float o2InverseMass) {
				position += -collisionNormal * penetration * (inverseMass / (inverseMass + o2InverseMass));
			}

			void AddImpluse(const Vector2& v1, const Vector2& v2, const float o2InverseMass) {
				/*

					-(1+e) * (v1 - v2) * Normalised Collision Pair
				J =	______________________________________________
							(inverse mass A + invers mass B)

				vA = vA - inverse mA * J * normalised Collision Pair
				vB = vB - inverse mB * J * normalised Collision Pair

				*/
				float impluse = ((-(1 + elasticity)) * Vector2::Dot(v1, v2) / (inverseMass + o2InverseMass));
				velocity += v2 * inverseMass * impluse;
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

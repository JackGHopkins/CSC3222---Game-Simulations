#pragma once
#include "../../Common/Vector2.h"
#include "SimObject.h"
#include <vector>
#include <iostream>

//class Circle;
//class Square;

/// <summary>
///		For checking collisions between Shapes.
/// </summary>
namespace NCL {
	namespace CSC3222 {
		class CollisionVolume {
		public:
			enum BOUND_TYPE 
			{
				box,
				circle,
			};

			enum COLLISION_STATE
			{
				null,
				airborn,
				grounded,
				floor,
				wall,
				ladder,
				climb,
			};
			/* CONSTRUCTORS & DECONSTRUCTORS */
			CollisionVolume();
			CollisionVolume(std::string name, BOUND_TYPE boundType, float posX, float posY, Vector2 halfLength, SimObject* object, COLLISION_STATE collisionState);
			CollisionVolume(std::string name, BOUND_TYPE boundType, float posX, float posY, Vector2 halfLength, COLLISION_STATE collisionState);
			CollisionVolume(std::string name, BOUND_TYPE boundType, float posX, float posY, Vector2 halfLength, SimObject* object);
			CollisionVolume(std::string name, BOUND_TYPE boundType, float posX, float posY, Vector2 halfLength);
			~CollisionVolume();

			/* ABSTRACT METHOD */
			virtual bool CheckCollision(CollisionVolume& Other) = 0;

			/* METHODS */
			std::string GetName() const;
			float GetPosX() const;
			float GetPosY() const;
			Vector2 GetPosition() const;
			Vector2 GetHalfLength() const;
			SimObject* GetObject() const;
			COLLISION_STATE GetCollisionState() const;
			BOUND_TYPE GetBoundType() const;
			void SetPosX(const float x);
			void SetPosY(const float y);
			void SetHalfLength(const Vector2 halfLength);
			void Transform(float offsetX, float offsetY);
			void SetCollisionState(const COLLISION_STATE collisionState);

		private:
			std::string name;
			BOUND_TYPE boundType;
			float posX, posY;
			Vector2 halfLength;
			SimObject* object;
			COLLISION_STATE collisionState;
		};
	}
}
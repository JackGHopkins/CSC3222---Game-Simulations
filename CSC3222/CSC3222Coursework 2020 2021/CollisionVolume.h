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
			/* CONSTRUCTORS & DECONSTRUCTORS */
			CollisionVolume();
			CollisionVolume(float posX, float posY, Vector2 halfLength, SimObject* object);
			CollisionVolume(float posX, float posY, Vector2 halfLength);
			~CollisionVolume();

			/* ABSTRACT METHOD */
			virtual bool CheckCollision(CollisionVolume& Other) = 0;

			/* METHODS */
			float GetPosX() const;
			float GetPosY() const;
			Vector2 GetPosition() const;
			Vector2 GetHalfLength() const;
			SimObject* GetObject() const;
			void SetPosX(const float x);
			void SetPosY(const float y);
			void SetHalfLength(const Vector2 halfLength);
			void Transform(float offsetX, float offsetY);

		private:
			float posX, posY;
			Vector2 halfLength;
			SimObject* object;
		};
	}
}
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
			/* CONSTRUCTOR & DECONSTRUCTORS */
			CollisionVolume(float posX, float posY, SimObject* object);
			~CollisionVolume();

			/* ABSTRACT CLASS */
			virtual bool CheckCollision(CollisionVolume& Other) = 0;

			/* METHODS */
			float GetPosX() const;
			float GetPosY() const;
			void SetPosX(const float x);
			void SetPosY(const float y);
			void Transform(float offsetX, float offsetY);

		private:
			float posX, posY;
			SimObject* object;
		};
	}
}
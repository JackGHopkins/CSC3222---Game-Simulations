#include "Circle.h"
#include "Collision.h"

using namespace NCL::CSC3222;

Circle::Circle(float posX, float posY, SimObject object, float radius) :
	CollisionVolume(posX - radius, posY - radius, object), // minus radius to make the position being in the center, not bottom left. 
	radius(radius) {}

Circle::~Circle() {}

float Circle::GetRadius() const {
	return this->radius;
}

bool Circle::CheckCollision(CollisionVolume& Other) {
	Collision collision;
		try {
			// Checks if Other is a Circle or a Square.
			if (typeid(Other) == typeid(Circle))
				return collision.isCollision(static_cast<Circle&>(Other), *this);
			else if (typeid(Other) == typeid(Square))
				return collision.isCollision(*this, static_cast<Square&>(Other));
			else
				throw "Error: Shape Type Not Found.";
		}
		catch (char const*& e) {
			std::cout << e;
		}
		return false;
}

/* For checking if a certain point of a shape is within the Circle. */
bool Circle::PointWithinRadius(float posX, float posY) const {
	float distance = sqrtf(powf(this->GetPosX() - posX, 2.0) + powf(this->GetPosY() - posY, 2.0));

	if (distance < this->GetRadius())
		return true;

	return false;
}
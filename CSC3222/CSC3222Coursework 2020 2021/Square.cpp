#include "Square.h"
#include "Collision.h"

using namespace NCL::CSC3222;


Square::Square(float posX, float posY, SimObject* object, Vector2 halfLength) : 
	CollisionVolume(posX - halfLength.x, posY - halfLength.y, object), // minus halfLength to make the position being in the center, not bottom left. 
	halfLength(halfLength) {}

Square::~Square() {}

Vector2 Square::GetHalfLength() const {
	return this->halfLength;
}

bool Square::CheckCollision(CollisionVolume& Other) {
	Collision collision;
	try {
		// Checks if Other is a Circle or a Square.
		if (typeid(Other) == typeid(Circle))
			return collision.isCollision(static_cast<Circle&>(Other), *this);
		else if (typeid(Other) == typeid(Square))
			return collision.isCollision(static_cast<Square&>(Other), *this);
		else 
			throw "Error: Shape Type Not Found.";
	}
	catch (char const*& e) {
		std::cout << e;
	}

	return false;
}

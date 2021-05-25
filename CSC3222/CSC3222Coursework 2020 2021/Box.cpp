#include "Box.h"
#include "Collision.h"

using namespace NCL::CSC3222;

Box::Box() {}

Box::Box(std::string name, float posX, float posY, SimObject* object, Vector2 halfLength, COLLISION_STATE collsionState) :
	CollisionVolume(name, BOUND_TYPE::box, posX - halfLength.x, posY - halfLength.y, halfLength, object, collsionState), // minus halfLength to make the position being in the center, not bottom left. 
	halfLength(halfLength) {}

// Copy Constructor
Box::Box(std::string name, float posX, float posY, Vector2 halfLength, COLLISION_STATE collsionState) :
	CollisionVolume(name, BOUND_TYPE::box, posX - halfLength.x, posY - halfLength.y, halfLength, collsionState),  // minus halfLength to make the position being in the center, not bottom left. 
	halfLength(halfLength) {}

Box::Box(std::string name, float posX, float posY, SimObject* object, Vector2 halfLength) :
	CollisionVolume(name, BOUND_TYPE::box, posX - halfLength.x, posY - halfLength.y, halfLength, object), // minus halfLength to make the position being in the center, not bottom left. 
	halfLength(halfLength) {}

// Copy Construtor for QuadTree box.
Box::Box(std::string name, float posX, float posY, Vector2 halfLength) :
	CollisionVolume(name, BOUND_TYPE::box, posX - halfLength.x, posY - halfLength.y, halfLength),  // minus halfLength to make the position being in the center, not bottom left. 
	halfLength(halfLength) {}


Box::~Box() {}

Vector2 Box::GetHalfLength() const {
	return this->halfLength;
}

bool Box::CheckCollision(CollisionVolume& Other) {
	Collision collision;
	try {
		// Checks if Other is a Circle or a Box.
		if (typeid(Other) == typeid(Circle))
			return collision.isCollision(static_cast<Circle&>(Other), *this);
		else if (typeid(Other) == typeid(Box))
			return collision.isCollision(static_cast<Box&>(Other), *this);
		else 
			throw "Error: Shape Type Not Found.";
	}
	catch (char const*& e) {
		std::cout << e;
	}

	return false;
}

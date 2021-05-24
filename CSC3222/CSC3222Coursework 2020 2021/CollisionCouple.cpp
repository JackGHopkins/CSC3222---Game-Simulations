#include "CollisionCouple.h"

CollisionCouple::CollisionCouple(CollisionVolume* cV1, CollisionVolume* cV2)
{
	this->cV1 = cV1;
	this->cV2 = cV2;
	FindParameters(cV1, cV2);
	this->penDistance = penDistance;
	this->collisionNormal = collisionNormal;
}

CollisionCouple::~CollisionCouple(){}

void CollisionCouple::FindParameters(CollisionVolume* cV1, CollisionVolume* cV2) {
	float cV1Width = cV1->GetHalfLength().x;
	float cV1Height = cV1->GetHalfLength().y;
	float cV2Width = cV2->GetHalfLength().x;
	float cV2Height = cV2->GetHalfLength().y;
	float deltaX = cV1->GetPosX() - cV2->GetPosX();
	float deltaY = cV1->GetPosY() - cV2->GetPosY();

	/*
		If both are Boxes
	*/
	if (typeid(cV1) == typeid(Box) && typeid(cV2) == typeid(Box)) {
		// If Ys are overlapping more then X.
		if (cV1Width + cV2Width - abs(deltaX) < cV1Height + cV1Height - abs(deltaY)) {
			collisionNormal = Vector2(-deltaX, 0);
			penDistance = (cV1Width + cV2Width - abs(deltaX));
		}
		// Xs are overlapping more then Y.
		else
		{
			collisionNormal = Vector2(0, -deltaY);
			penDistance = (cV1Height + cV2Height - abs(deltaY));
		}
		collisionNormal.Normalise();
	}
	/*
		If both are Circles
	*/
	else if (typeid(cV1) == typeid(Circle) && typeid(cV2) == typeid(Circle))
	{
		float radiusDiff = sqrt(powf(deltaX, 2) + powf(deltaY, 2));
		if (cV1Width + cV2Width > radiusDiff) {
			penDistance = cV1Width + cV2Width - radiusDiff;
			collisionNormal = cV1->GetPosition() - cV2->GetPosition();
			collisionNormal.Normalise();
		}
	}
	/*
		When collision is between a Box and Cirlce
	*/
	else
	{
		CollisionVolume* box;
		CollisionVolume* circle;

		// Check which CV is which shape.
		if (typeid(cV1) == typeid(Box)) {
			box = cV1;
			circle = cV2;
		}
		else {
			box = cV2;
			circle = cV1;
		}

		float rad = circle->GetHalfLength().x;
		Vector2 cirCentre = circle->GetPosition();
		Vector2 boxCentre = box->GetPosition();
		Vector2 closestPoint = Vector2(
			std::clamp(cirCentre.x, boxCentre.x - box->GetHalfLength().x, boxCentre.x + box->GetHalfLength().x),
			std::clamp(cirCentre.y, boxCentre.y - box->GetHalfLength().y, boxCentre.y + box->GetHalfLength().y)
		);
		float minDist = sqrt(powf(cirCentre.x - closestPoint.x, 2.0) + pow(cirCentre.y - closestPoint.y, 2.0));

		if (minDist < rad) {
			penDistance = rad - minDist;
			collisionNormal = cirCentre - closestPoint;
			collisionNormal.Normalise();
		}
	}
}




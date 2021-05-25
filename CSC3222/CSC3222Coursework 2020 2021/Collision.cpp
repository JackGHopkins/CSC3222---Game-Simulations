#include "Circle.h"
#include "Collision.h"
#include "Box.h"
#include <math.h>

class Circle;
class Box;

/*
	Checks collisions between two Circles.
*/
bool Collision::isCollision(Circle& c1, Circle& c2)
{
	return IsSameShapeCollide(c1.GetPosX(), c1.GetPosY(), c1.GetRadius(), c2.GetPosX(), c2.GetPosY(), c2.GetRadius());
}

/*
	Checks collisions between two Boxs.
*/
bool Collision::isCollision(Box& s1, Box& s2)
{
	float s1HalfW = s1.GetHalfLength().x;
	float s1HalfH = s1.GetHalfLength().y;
	float s2HalfW = s2.GetHalfLength().x;
	float s2HalfH = s2.GetHalfLength().y;

	if((s1HalfW + s2HalfW) > abs(s1.GetPosition().x - s2.GetPosition().x) &&	// Check if Within X bounds of each other
		(s1HalfH + s2HalfH) > abs(s1.GetPosition().y - s2.GetPosition().y))		// Check if Within Y bounds of each other
		return true;
	else
		return false;
}

/*
	Checks collisions between a Circle and a Box.
*/
bool Collision::isCollision(Circle& c, Box& s)
{
	// Finds the distance between the centers of the shapes.
	float distanceX = fabsf(c.GetPosX() - s.GetPosX());
	float distanceY = fabsf(c.GetPosY() - s.GetPosY());

	// Checks for case when shapes are out of range ofr the X or Y axis.
	if (distanceX > (s.GetHalfLength().x + c.GetRadius()))
		return false;
	if (distanceY > (s.GetHalfLength().y + c.GetRadius()))
		return false;

	// Checks for Case where the shapes are colliding directly horizontally or vertically.
	if (distanceX <= (s.GetHalfLength().x))
		return true;
	if (distanceY <= (s.GetHalfLength().y))
		return true;

	// Checks if Circle is overlapping with the corner of the Box.
	float cornerCheck = powf((distanceX - s.GetHalfLength().x), 2.0) +
		powf((distanceY - s.GetHalfLength().y), 2.0);

	return cornerCheck <= powf(c.GetRadius(), 2.0);

}

/*
	For checking if the distance between the centers are less then the combined length of the two shapes.
	If comparing Boxs, make sure the "Raidus" of the Boxs is the radius are GetLength() / 2.
*/
bool Collision::IsSameShapeCollide(float x1, float y1, float r1, float x2, float y2, float r2) const
{
	float distance = sqrtf(powf(x1 - x2, 2.0) + powf(y1 - y2, 2.0));
	float sumLength = r1 + r2;

	if (distance <= sumLength)
		return true;

	return false;
}
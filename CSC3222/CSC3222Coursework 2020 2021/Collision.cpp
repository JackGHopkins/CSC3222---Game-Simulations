#include "Circle.h"
#include "Collision.h"
#include "Square.h"
#include <math.h>

class Circle;
class Square;

/*
	Checks collisions between two Circles.
*/
bool Collision::isCollision(Circle& c1, Circle& c2)
{
	return IsSameShapeCollide(c1.GetPosX(), c1.GetPosY(), c1.GetRadius(), c2.GetPosX(), c2.GetPosY(), c2.GetRadius());
}

/*
	Checks collisions between two Squares.
*/
bool Collision::isCollision(Square& s1, Square& s2)
{
	if (s1.GetPosX() < s2.GetPosX() + (s2.GetHalfLength().x * 2) &&	// Checks if s1 is right of s2's left side.    
		s1.GetPosX() + (s1.GetHalfLength().x * 2) > s2.GetPosX() &&	// Checks if s1 is left of s2's right side.  
		s1.GetPosY() < s2.GetPosY() + (s2.GetHalfLength().y * 2) &&	// Checks if s1 is below of s2's top.  
		s1.GetPosY() + (s1.GetHalfLength().y * 2) > s2.GetPosY())		// Checks if s1 is above of s2's bottom.  
		return true;
	else
		return false;

}

/*
	Checks collisions between a Circle and a Square.
*/
bool Collision::isCollision(Circle& c, Square& s)
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

	// Checks if Circle is overlapping with the corner of the Square.
	float cornerCheck = powf((distanceX - s.GetHalfLength().x), 2.0) +
		powf((distanceY - s.GetHalfLength().y), 2.0);

	return cornerCheck <= powf(c.GetRadius(), 2.0);

}

/*
	For checking if the distance between the centers are less then the combined length of the two shapes.
	If comparing Squares, make sure the "Raidus" of the Squares is the radius are GetLength() / 2.
*/
bool Collision::IsSameShapeCollide(float x1, float y1, float r1, float x2, float y2, float r2) const
{
	float distance = sqrtf(powf(x1 - x2, 2.0) + powf(y1 - y2, 2.0));
	float sumLength = r1 + r2;

	if (distance <= sumLength)
		return true;

	return false;
}
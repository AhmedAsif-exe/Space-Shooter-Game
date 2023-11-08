#include "CollisionBox.h"

void CollisionBox::setSize(const Coordinates tLeft, const Coordinates bRight)
{
	topLeft = tLeft;
	bottomRight = bRight;
}
bool CollisionBox::checkForCollision(const CollisionBox& obj)
{
	if (bottomRight.x < obj.topLeft.x)
		return false;
	
	if (obj.bottomRight.x < topLeft.x  )
		return false;
	
	if (bottomRight.y < obj.topLeft.y)
		return false;
	
	if (obj.bottomRight.y < topLeft.y)
		return false;
	

	return true;
}
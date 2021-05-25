#include "CollisionVolume.h"
#include "QuadTree.h"
#include "SimObject.h"
#include <vector>

QuadTree::QuadTree() {}

QuadTree::QuadTree(int depth, Box boundArea){
	this->depth = depth;
	this->boundArea = boundArea;
	objectVector;
	nodeVector;
}

QuadTree::~QuadTree()
{
}

void QuadTree::Clear(){
	this->objectVector.clear();

	for (int i = 0; i < nodeVector.size(); i++) {
		if (nodeVector[i] != nullptr) {
			nodeVector[i]->Clear();
			nodeVector[i] = nullptr;
		}
	}
}

/*
	Splits quadrant in to 4 subquadrants
*/
void QuadTree::Split(){
	int divideWidth = (int)(boundArea.GetHalfLength().x / 2);
	int divideHeight = (int)(boundArea.GetHalfLength().y / 2);
	int x = (int)boundArea.GetPosX();
	int y = (int)boundArea.GetPosY();

	nodeVector[0] = &QuadTree(depth + 1, Box("quadB", x + divideWidth, y + divideHeight, Vector2(divideWidth, divideHeight), CollisionVolume::COLLISION_STATE::null));
	nodeVector[1] = &QuadTree(depth + 1, Box("quadB", x + divideWidth, y - divideHeight, Vector2(divideWidth, divideHeight), CollisionVolume::COLLISION_STATE::null));
	nodeVector[2] = &QuadTree(depth + 1, Box("quadB", x - divideWidth, y + divideHeight, Vector2(divideWidth, divideHeight), CollisionVolume::COLLISION_STATE::null));
	nodeVector[3] = &QuadTree(depth + 1, Box("quadB", x - divideWidth, y - divideHeight, Vector2(divideWidth, divideHeight), CollisionVolume::COLLISION_STATE::null));
}

/*
	Insert an object into the QuadTree.
	Split quadrant is the node exceeds capacity (defined in QuadTree.h).
*/
void QuadTree::Insert(CollisionVolume* CollisionVolume){
	if (nodeVector[0] != nullptr) {
		int index = GetIndex(CollisionVolume);

		if (index != -1) {
			nodeVector[index]->objectVector.push_back(CollisionVolume);
			return; // added element to child node.
		}
	}
	objectVector.push_back(CollisionVolume);

	// Checking if parent objectVector has exceeded max capacity.
	if (objectVector.size() > maxObjects && depth < maxDepth) {
		if (nodeVector[0] == nullptr)
			Split();

		int i = 0;
		while (i < objectVector.size()) {
			int index = GetIndex(objectVector[i]);
			if (index != -1) {
				nodeVector[index]->Insert(objectVector[i]);
				objectVector.erase(next(begin(objectVector) + i));
				objectVector.shrink_to_fit();
			}
			else
				i++;
		}
	}
}

/*
	Assigning which node the object belongs to. 
	-1 is returned when the object does not fit in a just one Child node.
*/
int QuadTree::GetIndex(CollisionVolume* CollisionVolume){
	int index = -1;
	
	// CollisionVolume's origin is in the centre of the shape.
	bool topQuad	= CollisionVolume->GetPosY() - CollisionVolume->GetHalfLength().y > boundArea.GetPosY() && CollisionVolume->GetPosY() + CollisionVolume->GetHalfLength().y < boundArea.GetPosY() + boundArea.GetHalfLength().y;		// True if Object entirely fits in upper quadrants
	bool botQuad	= CollisionVolume->GetPosY() + CollisionVolume->GetHalfLength().y < boundArea.GetPosY() && CollisionVolume->GetPosY() - CollisionVolume->GetHalfLength().y > boundArea.GetPosY() - boundArea.GetHalfLength().y; 	// True if Object entirely fits in lower quadrants
	bool leftQuad	= CollisionVolume->GetPosX() + CollisionVolume->GetHalfLength().x < boundArea.GetPosX() && CollisionVolume->GetPosX() - CollisionVolume->GetHalfLength().x > boundArea.GetPosX() - boundArea.GetHalfLength().x;		// True if Object entirely fits in left quadrants
	bool rightQuad	= CollisionVolume->GetPosX() - CollisionVolume->GetHalfLength().x > boundArea.GetPosX() && CollisionVolume->GetPosX() + CollisionVolume->GetHalfLength().x > boundArea.GetPosX() + boundArea.GetHalfLength().x;		// True if Object entirely fits in right quadrants	

	if (topQuad) { 
		if (leftQuad)
			index = 0;
		else if (rightQuad)
			index = 1;
	}
	else if (botQuad) {
		if (leftQuad)
			index = 2;
		else if (rightQuad)
			index = 3;
	}

	return index;
}

std::vector<CollisionVolume*> QuadTree::RetrieveObjects(std::vector<CollisionVolume*> retrievedObjects, CollisionVolume* CollisionVolume) {
	int index = GetIndex(CollisionVolume);
	if (index != -1 && nodeVector[0] != nullptr)
		retrievedObjects = nodeVector[index]->RetrieveObjects(retrievedObjects, CollisionVolume);

	// Add all bbjectsVector elements to the end of the retrievedObjects.
	retrievedObjects.insert(std::end(retrievedObjects), std::begin(objectVector), std::end(objectVector));

	return retrievedObjects;
}

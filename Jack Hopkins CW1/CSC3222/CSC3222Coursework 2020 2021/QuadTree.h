#pragma once
#include "Box.h"
#include "CollisionVolume.h"
#include <vector>
#include <array>

using namespace NCL::CSC3222;

class Box;
class Circle;

class QuadTree {
public:
	QuadTree();
	QuadTree(int depth, Box boundArea);
	~QuadTree();

	void Clear();
	void Split();
	void Insert(CollisionVolume* CollisionVolume);
	int GetIndex(CollisionVolume* CollisionVolume);
	std::vector<CollisionVolume*> RetrieveObjects(std::vector<CollisionVolume *> retrievedObjects, CollisionVolume* CollisionVolume);

private:
	int maxObjects	= 3;
	int maxDepth	= 3;

	int depth;
	Box boundArea;
	std::vector<CollisionVolume*> objectVector;
	std::array<QuadTree*,4> nodeVector;

};
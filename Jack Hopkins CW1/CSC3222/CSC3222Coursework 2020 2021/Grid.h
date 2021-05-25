#pragma once
#include "Shape.h"
#include <map>

/// <summary>
///		Grid Class in which shapes will be placed.
/// </summary>
class Grid {
public:
	/* CONSTRUCTOR & DECONSTRUCTOR */
	Grid(int width, int height, std::multimap<int, Shape*> multimap);
	~Grid();
	
	/* METHODS */
	std::multimap<int, Shape*> GetMultimap();
private:
	int width, height;
	std::multimap<int, Shape*> multimap;
};


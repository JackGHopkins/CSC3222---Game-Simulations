#pragma once
#include "SimObject.h"
#include <vector>

namespace NCL::CSC3222 {
	class Pixie : public SimObject	{
	public:
		Pixie();
		~Pixie();

		Vector2 Alignment(std::vector<SimObject*> allBoids);
		Vector2 Seperation(std::vector<SimObject*> allBoids);
		Vector2 Cohesion(std::vector<SimObject*> allBoids);
		Vector2 Avoidence(std::vector<SimObject*> allBoids);

		bool UpdateObject(float dt) override;

	protected:
		float alignmentThreshold, separationThreshold, cohesionThreshold, avoidenceThreshold;

	};
}
#pragma once
#include "SimObject.h"

namespace NCL::CSC3222 {
	class Fruit : public SimObject	{
	public:
		Fruit();
		~Fruit();
		bool UpdateObject(float dt) override;
	protected:

	};
}
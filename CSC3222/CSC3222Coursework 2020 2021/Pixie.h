#pragma once
#include "SimObject.h"

namespace NCL::CSC3222 {
	class Pixie : public SimObject	{
	public:
		Pixie();
		~Pixie();

		bool UpdateObject(float dt) override;

	protected:
	};
}
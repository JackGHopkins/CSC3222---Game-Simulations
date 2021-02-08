#pragma once
#include "SimObject.h"

namespace NCL::CSC3222 {
	class PixieDust :	public SimObject	{
	public:
		PixieDust();
		~PixieDust();

		bool UpdateObject(float dt) override;

	protected:
	};
}

#pragma once
#include "SimObject.h"

namespace NCL {
	namespace CSC3222 {
		class ThiefRobot : public SimObject
		{
		public:
			ThiefRobot();
			~ThiefRobot();

			bool UpdateObject(float dt) override;
			void DrawObject(GameSimsRenderer& r) override;

		protected:

		};
	}
}


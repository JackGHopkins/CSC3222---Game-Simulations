#pragma once
#include "../../Common/Vector2.h"
#include "../../Common/Vector4.h"
#include "RigidBody.h"

namespace NCL {
	using namespace Maths;

	namespace Rendering {
		class TextureBase;
	}
	namespace CSC3222 {
		class GameSimsRenderer;
		class TextureManager;
		class FruitWizardGame;
		class RigidBody;
		class CollisionVolume;

		class SimObject	: public RigidBody {
		public:
			SimObject();
			~SimObject();

			void SetCollider(CollisionVolume * c) {
				collider = c;
			}

			CollisionVolume* GetCollider() const {
				return collider;
			}

			void	UpdateAnimFrame(float dt);

			virtual bool UpdateObject(float dt) = 0;

			virtual void DrawObject(GameSimsRenderer &r);

			static void InitObjects(FruitWizardGame* game, TextureManager* manager);

		protected:

			CollisionVolume*		collider;
			Rendering::TextureBase* texture;


			Vector4			animFrameData;
			int				currentanimFrame;
			bool			flipAnimFrame;
			int				animFrameCount;
			float			frameTime;
			float			frameRate;

			static TextureManager*  texManager;
			static FruitWizardGame*		game;
		};
	}
}


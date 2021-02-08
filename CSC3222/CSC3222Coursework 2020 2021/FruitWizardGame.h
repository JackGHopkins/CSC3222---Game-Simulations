#pragma once
#include <vector>

namespace NCL::CSC3222 {
	class GameMap;
	class SimObject;
	class GameSimsRenderer;
	class GameSimsPhysics;
	class TextureBase;
	class TextureManager;
	class PlayerCharacter;

	class FruitWizardGame {
	public:
		FruitWizardGame();
		~FruitWizardGame();

		void Update(float dt);

		void AddNewObject(SimObject* object);

	protected:
		void InitialiseGame();

		TextureManager*		texManager;
		GameSimsRenderer*	renderer;
		GameSimsPhysics*	physics;
		GameMap* currentMap;

		PlayerCharacter* player;

		float gameTime;

		int currentScore;
		int magicCount;
		int dustCount;
		int lives;

		std::vector<SimObject*> gameObjects;
		std::vector<SimObject*> newObjects;
	};
}
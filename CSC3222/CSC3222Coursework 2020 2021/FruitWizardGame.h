#pragma once
#include <vector>

namespace NCL::CSC3222 {
	class Collision;
	class GameMap;
	class SimObject;
	class GameSimsRenderer;
	class GameSimsPhysics;
	class TextureBase;
	class TextureManager;
	class PlayerCharacter;
	class Guard;

	class FruitWizardGame {
	public:
		FruitWizardGame();
		~FruitWizardGame();

		void Update(float dt);

		void AddNewObject(SimObject* object);

		void VisualiseColliders();

	protected:
		void InitialiseGame();
		TextureManager*		texManager;
		GameSimsRenderer*	renderer;
		GameSimsPhysics*	physics;
		GameMap*			currentMap;

		PlayerCharacter*	player;
		Guard*				testGuard;

		float gameTime;

		int currentScore;
		int magicCount;
		int dustCount;
		int lives;

		std::vector<SimObject*> gameObjects;
		std::vector<SimObject*> newObjects;
		std::vector<Collision*> allColliders;
	};
}
#pragma once
#include <vector>

namespace NCL::CSC3222 {
	class CollisionVolume;
	class GameMap;
	class SimObject;
	class GameSimsRenderer;
	class GameSimsPhysics;
	class TextureBase;
	class TextureManager;
	class PlayerCharacter;
	class Guard;
	class Pixie;
	class Fruit;

	class FruitWizardGame {
	public:
		FruitWizardGame();
		~FruitWizardGame();

		void Update(float dt);
		void AddNewObject(SimObject* object);
		void VisualiseEnviromentColliders();
		void SetEnviromentCollisions();
		float RandomNumber(float Min, float Max);

	protected:
		void InitialiseGame();
		TextureManager*		texManager;
		GameSimsRenderer*	renderer;
		GameSimsPhysics*	physics;
		GameMap*			currentMap;

		PlayerCharacter*	player;
		Guard*				testGuard;
		Pixie*				testPixie;
		Fruit*				testFruit;

		float gameTime;

		int currentScore;
		int magicCount;
		int dustCount;
		int lives;

		std::vector<SimObject*> gameObjects;
		std::vector<SimObject*> newObjects;
		std::vector<CollisionVolume*> allColliders;
	};
}
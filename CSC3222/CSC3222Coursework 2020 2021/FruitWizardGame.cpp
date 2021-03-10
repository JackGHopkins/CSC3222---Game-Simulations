#include "FruitWizardGame.h"
#include "SimObject.h"
#include "GameMap.h"
#include "Circle.h"
#include "Collision.h"
#include "CollisionVolume.h"
#include "TextureManager.h"
#include "GameSimsRenderer.h"
#include "GameSimsPhysics.h"
#include "PlayerCharacter.h"
#include "Fruit.h"
#include "Guard.h"
#include "Froggo.h"
#include "Pixie.h"
#include "PixieDust.h"
#include "Spell.h"
#include "Square.h"
#include <iostream>
#include <vector>

#include "../../Common/Window.h"
#include "../../Common/TextureLoader.h"

using namespace NCL::CSC3222;

FruitWizardGame::FruitWizardGame()	{
	renderer		= new GameSimsRenderer();
	texManager		= new TextureManager();
	physics			= new GameSimsPhysics();
	SimObject::InitObjects(this, texManager);
	InitialiseGame();
}

FruitWizardGame::~FruitWizardGame()	{
	delete currentMap;
	delete texManager;
	delete renderer;
	delete physics;
}

void FruitWizardGame::Update(float dt) {
	for (auto i : newObjects) {
		gameObjects.emplace_back(i);
	}
	newObjects.clear();

	gameTime += dt;

	renderer->Update(dt);
	physics->Update(dt);
	currentMap->DrawMap(*renderer);

	srand((int)(gameTime * 1000.0f));

	for (auto i = gameObjects.begin(); i != gameObjects.end(); ) {
		(*i)->UpdateAnimFrame(dt);
		if (!(*i)->UpdateObject(dt)) { //object has said its finished with
			delete (*i);
			 i = gameObjects.erase(i);
		}
		else {
			(*i)->DrawObject(*renderer);
			++i;
		}
	}	
	renderer->DrawString("Score:" + std::to_string(currentScore), 
		Vector2(32, 12), Vector4(1,1,1,1), 100.0f);
	renderer->DrawString("Lives:" + std::to_string(lives), 
		Vector2(144, 12), Vector4(1, 0,0, 1), 100.0f);
	renderer->DrawString("Magic:" + std::to_string(magicCount), 
		Vector2(256, 12), Vector4(1, 0, 0.5f, 1), 100.0f);
	renderer->DrawString("Dust:"  + std::to_string(dustCount), 
		Vector2(366, 12), Vector4(0.5f, 0.3f, 0.8, 1), 100.0f);

	/*
	Some examples of debug rendering! 
	These all use coordinates in the same 'space' as the game positions
	*/
	renderer->DrawBox(Vector2(16,16), Vector2(8, 8), Vector4(1, 0, 0, 1));
	renderer->DrawLine(Vector2(16, 16), Vector2(192, 192), Vector4(1, 1, 0, 1));
	renderer->DrawCircle(Vector2(100, 100), 10.0f, Vector4(1, 0, 1, 1));

	renderer->DrawCircle(player->GetPosition(), 6.0f, Vector4(1, 0, 0, 1));
	renderer->DrawBox(Vector2(player->GetPosition().x, player->GetPosition().y - 8), Vector2(6, 8), Vector4(1, 0, 0, 1));
	physics->RemoveCollider(player->GetCollider());
	player->SetCollider(new Square(player->GetPosition().x, player->GetPosition().y, Vector2(6, 8)));
	physics->AddCollider(player->GetCollider());
	//physics->UpdateCollider(player->GetCollider());

	// Test Guard
	renderer->DrawCircle(Vector2(testGuard->GetPosition().x, testGuard->GetPosition().y - 8), 8, Vector4(1, 0, 0, 1));

	VisualiseColliders();

	renderer->Render();
}

void FruitWizardGame::InitialiseGame() {
	delete currentMap;
	for (auto o : gameObjects) {
		delete o;
	}
	gameObjects.clear();

	currentMap = new GameMap("FruitWizardMap.txt", gameObjects, *texManager);

	renderer->SetScreenProperties(16, currentMap->GetMapWidth(), currentMap->GetMapHeight());

	player = new PlayerCharacter();
	player->SetPosition(Vector2(100, 32));
	player->SetCollider(new Square(player->GetPosition().x, player->GetPosition().y, Vector2(6, 8)));
	AddNewObject(player);

	testGuard = new Guard();
	testGuard->SetPosition(Vector2(130, 224));
	testGuard->SetCollider(new Circle(testGuard->GetPosition().x, testGuard->GetPosition().y, 8));
	AddNewObject(testGuard);

	Spell* testSpell = new Spell(Vector2(1,0));
	testSpell->SetPosition(Vector2(160, 48));
	AddNewObject(testSpell);

	Fruit* testFruit = new Fruit();
	testFruit->SetPosition(Vector2(250, 150));
	AddNewObject(testFruit);

	PixieDust* testDust = new PixieDust();
	testDust->SetPosition(Vector2(285, 220));
	AddNewObject(testDust);

	Pixie* pixie = new Pixie();
	pixie->SetPosition(Vector2(350, 96));
	AddNewObject(pixie);

	Froggo* testFroggo = new Froggo();
	testFroggo->SetPosition(Vector2(370, 285));
	AddNewObject(testFroggo);

	gameTime		= 0;
	currentScore	= 0;
	magicCount		= 0;
	dustCount		= 0;
	lives			= 3;
}

void FruitWizardGame::AddNewObject(SimObject* object) {
	newObjects.emplace_back(object);
	physics->AddRigidBody(object);
	if (object->GetCollider()) {
		physics->AddCollider(object->GetCollider());
	}
}

void FruitWizardGame::VisualiseColliders() {
	float tileSize = 16;
	float halfTileSize = tileSize / 2;

	// Walls
	renderer->DrawBox(Vector2(halfTileSize, tileSize * 10), Vector2(halfTileSize, 160), Vector4(0, 0, 0, 1)); // Left
	
	
	renderer->DrawBox(Vector2(30 * tileSize - halfTileSize, tileSize*10), Vector2(halfTileSize, 160), Vector4(0, 0, 0, 1)); // Right

	// Floors
	renderer->DrawBox(Vector2(15 * tileSize, halfTileSize), Vector2(224, halfTileSize), Vector4(0, 0, 0, 1)); // Bottom

	renderer->DrawBox(Vector2(3 * tileSize + halfTileSize, 4 * tileSize + halfTileSize), Vector2(tileSize * 5 / 2, halfTileSize), Vector4(0, 0, 0, 1)); // Floor 1;0
	renderer->DrawBox(Vector2(8 * tileSize + halfTileSize, 4 * tileSize + halfTileSize), Vector2(tileSize * 1 / 2, halfTileSize), Vector4(0, 0, 0, 1)); // Floor 1:1
	renderer->DrawBox(Vector2(12.5 * tileSize + halfTileSize, 4 * tileSize + halfTileSize), Vector2(tileSize * 4 / 2, halfTileSize), Vector4(0, 0, 0, 1)); // Floor 1:2
	renderer->DrawBox(Vector2(22.5 * tileSize + halfTileSize, 4 * tileSize + halfTileSize), Vector2(tileSize * 12 / 2, halfTileSize), Vector4(0, 0, 0, 1)); // Floor 1:3

	renderer->DrawBox(Vector2(16 * tileSize + halfTileSize, 8 * tileSize + halfTileSize), Vector2(tileSize * 11 / 2, halfTileSize), Vector4(0, 0, 0, 1)); // Floor 2:0
	renderer->DrawBox(Vector2(26 * tileSize + halfTileSize, 8 * tileSize + halfTileSize), Vector2(tileSize * 5 / 2, halfTileSize), Vector4(0, 0, 0, 1)); // Floor 2:1

	renderer->DrawBox(Vector2(6.5 * tileSize + halfTileSize, 12 * tileSize + halfTileSize), Vector2(tileSize * 8 / 2, halfTileSize), Vector4(0, 0, 0, 1)); // Floor 3:0
	renderer->DrawBox(Vector2(13 * tileSize + halfTileSize, 12 * tileSize + halfTileSize), Vector2(tileSize * 1 / 2, halfTileSize), Vector4(0, 0, 0, 1)); // Floor 3:1
	renderer->DrawBox(Vector2(17 * tileSize + halfTileSize, 12 * tileSize + halfTileSize), Vector2(tileSize * 1 / 2, halfTileSize), Vector4(0, 0, 0, 1)); // Floor 3:2
	renderer->DrawBox(Vector2(21 * tileSize + halfTileSize, 12 * tileSize + halfTileSize), Vector2(tileSize * 3 / 2, halfTileSize), Vector4(0, 0, 0, 1)); // Floor 3:3

	renderer->DrawBox(Vector2(2.5 * tileSize + halfTileSize, 16 * tileSize + halfTileSize), Vector2(tileSize * 4 / 2, halfTileSize), Vector4(0, 0, 0, 1)); // Floor 4:0
	renderer->DrawBox(Vector2(7 * tileSize + halfTileSize, 16 * tileSize + halfTileSize), Vector2(tileSize * 1 / 2, halfTileSize), Vector4(0, 0, 0, 1)); // Floor 4:1
	renderer->DrawBox(Vector2(19 * tileSize + halfTileSize, 16 * tileSize + halfTileSize), Vector2(tileSize * 13 / 2, halfTileSize), Vector4(0, 0, 0, 1)); // Floor 4:2
	renderer->DrawBox(Vector2(28 * tileSize + halfTileSize, 16 * tileSize + halfTileSize), Vector2(tileSize * 1 / 2, halfTileSize), Vector4(0, 0, 0, 1)); // Floor 4:3

	// Ladder Tops
	renderer->DrawBox(Vector2(6.5 * tileSize + halfTileSize, 4 * tileSize + halfTileSize), Vector2(tileSize * 2 / 2, halfTileSize), Vector4(0, 0, 1, 1)); // Floor 1:0
	renderer->DrawBox(Vector2(15.5 * tileSize + halfTileSize, 4 * tileSize + halfTileSize), Vector2(tileSize * 2 / 2, halfTileSize), Vector4(0, 0, 1, 1)); // Floor 1:1

	renderer->DrawBox(Vector2(22.5 * tileSize + halfTileSize, 8 * tileSize + halfTileSize), Vector2(tileSize * 2 / 2, halfTileSize), Vector4(0, 0, 1, 1)); // Floor 2:0

	renderer->DrawBox(Vector2(1.5 * tileSize + halfTileSize, 12 * tileSize + halfTileSize), Vector2(tileSize * 2 / 2, halfTileSize), Vector4(0, 0, 1, 1)); // Floor 3:0
	renderer->DrawBox(Vector2(11.5 * tileSize + halfTileSize, 12 * tileSize + halfTileSize), Vector2(tileSize * 2 / 2, halfTileSize), Vector4(0, 0, 1, 1)); // Floor 3:1
	renderer->DrawBox(Vector2(18.5 * tileSize + halfTileSize, 12 * tileSize + halfTileSize), Vector2(tileSize * 2 / 2, halfTileSize), Vector4(0, 0, 1, 1)); // Floor 3:2

	renderer->DrawBox(Vector2(5.5 * tileSize + halfTileSize, 16 * tileSize + halfTileSize), Vector2(tileSize * 2 / 2, halfTileSize), Vector4(0, 0, 1, 1)); // Floor 4:0
	renderer->DrawBox(Vector2(26.5 * tileSize + halfTileSize, 16 * tileSize + halfTileSize), Vector2(tileSize * 2 / 2, halfTileSize), Vector4(0, 0, 1, 1)); // Floor 4:1


	// Ladder Mid & bottom
	renderer->DrawBox(Vector2(6.5 * tileSize + halfTileSize, 2 * tileSize + halfTileSize), Vector2(tileSize * 2 / 2, 3 * halfTileSize), Vector4(0, 1, 1, 1)); // Floor 1:0
	renderer->DrawBox(Vector2(15.5 * tileSize + halfTileSize, 2 * tileSize + halfTileSize), Vector2(tileSize * 2 / 2, 3 * halfTileSize), Vector4(0, 1, 1, 1)); // Floor 1:1

	renderer->DrawBox(Vector2(22.5 * tileSize + halfTileSize, 6 * tileSize + halfTileSize), Vector2(tileSize * 2 / 2, 3 * halfTileSize), Vector4(0, 1, 1, 1)); // Floor 2:0

	renderer->DrawBox(Vector2(1.5 * tileSize + halfTileSize, 8 * tileSize + halfTileSize), Vector2(tileSize * 2 / 2, 7 * halfTileSize), Vector4(0, 1, 1, 1)); // Floor 3:0
	renderer->DrawBox(Vector2(11.5 * tileSize + halfTileSize, 10 * tileSize + halfTileSize), Vector2(tileSize * 2 / 2, 3 * halfTileSize), Vector4(0, 1, 1, 1)); // Floor 3:1
	renderer->DrawBox(Vector2(18.5 * tileSize + halfTileSize, 10 * tileSize + halfTileSize), Vector2(tileSize * 2 / 2, 3 * halfTileSize), Vector4(0, 1, 1, 1)); // Floor 3:2

	renderer->DrawBox(Vector2(5.5 * tileSize + halfTileSize, 14 * tileSize + halfTileSize), Vector2(tileSize * 2 / 2, 3 * halfTileSize), Vector4(0, 1, 1, 1)); // Floor 4:0
	renderer->DrawBox(Vector2(26.5 * tileSize + halfTileSize, 12 * tileSize + halfTileSize), Vector2(tileSize * 2 / 2, 7 * halfTileSize), Vector4(0, 1, 1, 1)); // Floor 4:1
}
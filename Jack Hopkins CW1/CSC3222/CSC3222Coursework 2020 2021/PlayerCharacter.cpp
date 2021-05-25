#include "PlayerCharacter.h"
#include "TextureManager.h"
#include "../../Common/Window.h"
#include "GameSimsRenderer.h"

using namespace NCL;
using namespace CSC3222;

Vector4 runFrames[] = {
	Vector4(64,160, 32, 32),
	Vector4(96,160, 32, 32),
	Vector4(128,160, 32, 32),
	Vector4(160,160, 32, 32),
	Vector4(192,160, 32, 32),
	Vector4(224,160, 32, 32),
};

Vector4 attackFrames[] = {
	Vector4(128,288, 32, 30),
	Vector4(64,224, 32, 32),
	Vector4(160,288, 32, 30),
	Vector4(96,224, 32, 32),
	Vector4(192,288, 32, 29),
	Vector4(64,256, 32, 32)
};

Vector4 idleFrames[] = {
	Vector4(64,128, 32, 32),
	Vector4(96,128, 32, 32),
	Vector4(128,128, 32, 32),
	Vector4(160,128, 32, 32),
	Vector4(128,128, 32, 32),
	Vector4(224,128, 32, 32)
};

Vector4 fallFrames[] = {
	Vector4(64,320, 32, 32),
	Vector4(64,320, 32, 32),
	Vector4(64,320, 32, 32),
	Vector4(96,320, 32, 32),
	Vector4(96,320, 32, 32),
	Vector4(96,320, 32, 32)
};

Vector4 deathFrames[] = {
	Vector4(96,352, 32, 32),
	Vector4(128,352, 32, 32),
	Vector4(96,352, 32, 32),	
	Vector4(128,352, 32, 32),
	Vector4(96,352, 32, 32),
	Vector4(128,352, 32, 32),
};

Vector4 ladderFrames[] = {//Not an ideal spritesheet for ladders!
	Vector4(64,224, 32, 32),
	Vector4(64,224, 32, 32),
	Vector4(64,224, 32, 32),
	Vector4(64,224, 32, 32),
	Vector4(64,224, 32, 32),
	Vector4(64,224, 32, 32),
};


PlayerCharacter::PlayerCharacter() : SimObject() {
	currentAnimState	= PlayerState::Left;
	texture				= texManager->GetTexture("FruitWizard\\mini_fantasy_sprites_oga_ver.png");
	animFrameCount		= 6;
	inverseMass			= 10;
}

PlayerCharacter::~PlayerCharacter() {

}

PlayerCharacter::PlayerState PlayerCharacter::GetCurrentAnimState() {
	return currentAnimState;
}

bool PlayerCharacter::UpdateObject(float dt) {
	float testSpeed = 30;
	Vector4* animSource = idleFrames;

	Vector2 newVelocity;

	if (currentAnimState == PlayerState::Attack) {
		animSource = attackFrames;
		if (currentanimFrame >= 5) {
			currentAnimState = PlayerState::Idle;
		}
	}
	else {
		currentAnimState = PlayerState::Idle;
		if (Window::GetKeyboard()->KeyDown(KeyboardKeys::LEFT)) {
			animSource = runFrames;
			currentAnimState = PlayerState::Left;
			AddForce(Vector2(-testSpeed, 0) / inverseMass);
			flipAnimFrame = true;
		}
		if (Window::GetKeyboard()->KeyDown(KeyboardKeys::RIGHT)) {
			animSource = runFrames;
			currentAnimState = PlayerState::Right;
			AddForce(Vector2(testSpeed, 0) / inverseMass);
			flipAnimFrame = false;
		}	
		if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::SPACE)) {
			currentAnimState = PlayerState::Attack;
			currentanimFrame = 0;
		}
		if (Window::GetKeyboard()->KeyDown(KeyboardKeys::UP)) {
			animSource = ladderFrames;
			currentAnimState = PlayerState::Climb;
			AddForce(Vector2(0, testSpeed / 2) / inverseMass);
		}
		if (Window::GetKeyboard()->KeyDown(KeyboardKeys::DOWN)) {
			animSource = ladderFrames;
			currentAnimState = PlayerState::Climb;
			AddForce(Vector2(0, -testSpeed / 2) / inverseMass);
		}
	}

	position += newVelocity;

	animFrameData = animSource[currentanimFrame];

	return true;
}
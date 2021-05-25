#include "Spell.h"
#include "TextureManager.h"
#include "GameSimsRenderer.h"

#include "../../Common/Maths.h"

#include "../../Common/Vector3.h"
#include "../../Common/Vector4.h"

using namespace NCL;
using namespace CSC3222;

Vector4 activeFrames[] = {
	Vector4(512,384, 32, 32),
	Vector4(512,384, 32, 32),
	Vector4(512,384, 32, 32),
	Vector4(384,416, 32, 32),
	Vector4(384,416, 32, 32),
	Vector4(384,416, 32, 32),
};

Vector4 explodeFrames[] = {
	Vector4(512,384, 32, 32),
	Vector4(384,416, 32, 32),
	Vector4(416,416, 32, 32),
	Vector4(448,416, 32, 32),
	Vector4(480,416, 32, 32),
	Vector4(512,416, 32, 32),	
};

Spell::Spell(Vector2 direction) : SimObject()	{
	texture				= texManager->GetTexture("FruitWizard\\mini_fantasy_sprites_oga_ver.png");
	velocity			= direction;
	animFrameCount		= 6;
	this->time			= 0;
	inverseMass			= 0.01;
}

Spell::~Spell()	{
}

void Spell::DrawObject(GameSimsRenderer &r) {
	Vector4	texData = explodeFrames[currentanimFrame];
	Vector2 texPos	= Vector2(texData.x, texData.y);
	Vector2 texSize = Vector2(texData.z, texData.w);
	r.DrawTextureArea((OGLTexture*)texture, texPos, texSize, position);
}

bool Spell::UpdateObject(float dt) {
	animFrameData = explodeFrames[currentanimFrame];

	int fps = 60;
	int timeLimit = 3 * fps; // seconds * fps = total frames
	time++;

	if (this->time > timeLimit) {
		std::cout << "Del Spell" << std::endl;
		return false;
	}

	return true;
}

void Spell::InitMovement() {
	//AddForce(Vector2(100, 0) / inverseMass);
	AddForce(this->GetVelocity() / inverseMass * 2000);
}
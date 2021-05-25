#include "ThiefRobot.h"
#include "TextureManager.h"
#include "GameSimsRenderer.h"

using namespace NCL;
using namespace CSC3222;

Vector4 animFramesThief[] = {
	Vector4(40,622,16,18),
	Vector4(73,622,16,18),
	Vector4(105,622,16,18),
	Vector4(168,622,16,18),
};

ThiefRobot::ThiefRobot() : SimObject() {
	texture = texManager->GetTexture("TL_oldcharacters.png");
	currentFrameCount = 4;
}

ThiefRobot::~ThiefRobot() {

}

bool ThiefRobot::UpdateObject(float dt) {
	UpdateAnimFrame(dt);

	return true;
}

void ThiefRobot::DrawObject(GameSimsRenderer& r) {
	Vector2 screenPos = position;
	Vector2	texPos = Vector2(animFramesThief[currentanimFrame].x, animFramesThief[currentanimFrame].y);
	Vector2 texSize = Vector2(animFramesThief[currentanimFrame].z, animFramesThief[currentanimFrame].w);

	r.DrawTextureArea((OGLTexture*)texture, texPos, texSize, screenPos, false);
}
#include "Pixie.h"
#include "TextureManager.h"
#include "GameSimsRenderer.h"

using namespace NCL;
using namespace CSC3222;

Vector4 pixieFrames[] = {
	Vector4(32 * 1,32 * 4, 32, 32),
	Vector4(32 * 2,32 * 4, 32, 32),
	Vector4(32 * 3,32 * 4, 32, 32),
	Vector4(32 * 4,32 * 4, 32, 32),
};

Pixie::Pixie() : SimObject() {
	texture					= texManager->GetTexture("FruitWizard\\super_random_sprites.png");
	animFrameCount			= 4;
	inverseMass				= 1;
	alignmentThreshold		= 1;
	separationThreshold		= 1;
	cohesionThreshold		= 1;
	avoidenceThreshold		= 1;
}

Pixie::~Pixie() {
}

bool Pixie::UpdateObject(float dt) {
	animFrameData = pixieFrames[currentanimFrame];
	return true;

	std::vector<SimObject*> allBoids;
	allBoids.push_back(this);

	for (SimObject* o : allBoids) {

		Vector2 dir;
		dir += Alignment(allBoids);
		dir += Seperation(allBoids);
		dir += Cohesion(allBoids);
		dir += Avoidence(allBoids);
		o->GetPosition() += dir * dt;
	}
}

Vector2 Pixie::Alignment(std::vector<SimObject*> allBoids) {
	Vector2	dir = this->velocity;

	for (SimObject* o : allBoids) {
		if (o == this)
			continue;

		float distance = sqrt(powf(this->GetPosition().x - o->GetPosition().x, 2.0f) + powf(this->GetPosition().y - o->GetPosition().y, 2.0f));

		if (distance > alignmentThreshold)
			continue;

		dir += o->GetVelocity();
	}
	return dir.Normalised();
}

Vector2 Pixie::Seperation(std::vector<SimObject*> allBoids){
	Vector2	dir;
	for (SimObject* o : allBoids) {
		if (o == this)
			continue;

		float distance = sqrt(powf(this->GetPosition().x - o->GetPosition().x, 2.0f) + powf(this->GetPosition().y - o->GetPosition().y, 2.0f));

		if (distance > separationThreshold)
			continue;

		float strength = 1.0f - (distance / separationThreshold);
		dir += (this->position - o->GetPosition()).Normalised() * strength;
	}
	return dir.Normalised();
}

Vector2 Pixie::Cohesion(std::vector<SimObject*> allBoids) {
	Vector2 avgPos = this->position;
	float count = 1.0f;

	for (SimObject* o : allBoids) {
		if (o == this)
			continue;

		float distance = sqrt(powf(this->GetPosition().x - o->GetPosition().x, 2.0f) + powf(this->GetPosition().y - o->GetPosition().y, 2.0f));

		if (distance > cohesionThreshold)
			continue;
		avgPos += o->GetPosition();
		count++;
	}
	avgPos /= count;
	Vector2 dir = avgPos - this->position;
	return dir.Normalised();
}

Vector2 Pixie::Avoidence(std::vector<SimObject*> allBoids) {
	Vector2 dir;

	for (SimObject* o : allBoids) {
		if (o == this)
			continue;

		float distance = sqrt(powf(this->GetPosition().x - o->GetPosition().x, 2.0f) + powf(this->GetPosition().y - o->GetPosition().y, 2.0f));

		if (distance > avoidenceThreshold)
			continue;

		dir += (this->position - o->GetPosition()).Normalised();
	}
	return dir.Normalised();
}
#include "../../Common/Window.h"
#include "FruitWizardGame.h"

using namespace NCL;
using namespace CSC3222;

int main() {
	Window*w = Window::CreateGameWindow("CSC3222 - Fruit Wizard!", 1120, 768);

	if (!w->HasInitialised()) {
		return -1;
	}

	FruitWizardGame* theGame = new FruitWizardGame();
	w->GetTimer()->GetTimeDeltaSeconds(); //Reset so we don't get a big dt in the first frame!
	while (w->UpdateWindow() && !Window::GetKeyboard()->KeyDown(KeyboardKeys::ESCAPE)) {
		float time = w->GetTimer()->GetTimeDeltaSeconds();

		if (time > 1.0f) {
			continue; //Skip the timestep if it's huge!
		}

		theGame->Update(time);

		if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::PRIOR)) {
			w->ShowConsole(true);
		}
		if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::NEXT)) {
			w->ShowConsole(false);
		}
		if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::HOME)) {
			w->SetFullScreen(true);
		}
		if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::END)) {
			w->SetFullScreen(false);
		}

		w->SetTitle(std::to_string(time));
	}

	delete theGame;

	Window::DestroyGameWindow();
}
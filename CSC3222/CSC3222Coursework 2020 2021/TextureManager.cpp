#include "TextureManager.h"
#include "../../Common/TextureLoader.h"
#include "../../Common/TextureBase.h"
#include <iostream>
using namespace NCL;
using namespace CSC3222;
using namespace Rendering;

TextureManager::TextureManager()	{

}

TextureManager::~TextureManager()	{
	for (auto& i : allTextures) {
		delete i.second;
	}
}

Rendering::TextureBase* TextureManager::GetTexture(const std::string& name) {
	auto i = allTextures.find(name);
	if (i != allTextures.end()) {
		return i->second;
	}
	TextureBase* tex = TextureLoader::LoadAPITexture(name);

	if (!tex) {
		std::cout << "Can't load texture: " << name << std::endl;
	}
	allTextures.insert(std::make_pair(name, tex));

	return tex;
}

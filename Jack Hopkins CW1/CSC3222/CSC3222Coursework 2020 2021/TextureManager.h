#pragma once
#include <string>
#include <map>

namespace NCL {
	namespace Rendering {
		class TextureBase;
	}
	namespace CSC3222 {
		class TextureManager	{
		public:
			TextureManager();
			~TextureManager();

			Rendering::TextureBase* GetTexture(const std::string& name);

		protected:

			std::map<std::string, Rendering::TextureBase*> allTextures;
		};
	}
}


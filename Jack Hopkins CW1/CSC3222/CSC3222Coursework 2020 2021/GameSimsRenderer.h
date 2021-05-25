#pragma once
#include "../../Plugins/OpenGLRendering/OGLRenderer.h"
#include "../../Plugins/OpenGLRendering/OGLShader.h"
#include "../../Plugins/OpenGLRendering/OGLTexture.h"
#include "../../Plugins/OpenGLRendering/OGLMesh.h"

#include <vector>

namespace NCL {
	namespace CSC3222 {
		class SimObject;
		class GameSimsRenderer : public OGLRenderer	{
		public:
			GameSimsRenderer();
			virtual ~GameSimsRenderer();

			void AddSimObject(const SimObject* s) const;
			void RemoveSimObject(const SimObject* s);

			void Update(float dt) override;

			void DrawTextureArea(OGLTexture* texture, Vector2 start, Vector2 size, 
								 Vector2 screenPos, bool invertX = false);

			void DrawMesh(OGLMesh* mesh, OGLTexture* texture);
			void DrawBox(Vector2 worldPos, Vector2 halfSize, Vector4 colour = Vector4(1,0,0,1));
			void DrawCircle(Vector2 worldPos, float radius, Vector4 colour = Vector4(0, 1, 0, 1));
			void DrawLine(Vector2 worldStart, Vector2 worldEnd, Vector4 colour = Vector4(0, 0, 1, 1));

			void SetScreenProperties(int tileSize, int numTilesX, int numTilesY);

			Matrix4 SetupDebugLineMatrix()	const override;
			Matrix4 SetupDebugStringMatrix()const override;
		protected:
			void RenderFrame()	override;

			struct TextureArea {
				OGLTexture* texture;
				Vector2 start;
				Vector2 size;
				Vector2 screenPos;
				bool	flipX;
			};

			struct QuickMesh {
				OGLTexture* texture;
				Vector2 screenPos;
				OGLMesh* mesh;
			};

			int tileSize;
			int numTilesX;
			int numTilesY;

			std::vector<SimObject*> allObjects;

			std::vector<TextureArea> texAreas;
			std::vector<QuickMesh> quickMeshes;
			std::vector<Vector3> debugLineVerts;
			std::vector<Vector4> debugLineColours;

			OGLShader*  debugLineShader;
			OGLShader*	spriteShader;
			OGLMesh*	spriteMesh;
		};
	}
}


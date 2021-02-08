#include "GameSimsRenderer.h"
#include "../../Common/Vector2.h"
#include "../../Common/Vector3.h"
#include "../../Common/Matrix4.h"
#include "../../Common/Maths.h"

#include "SimObject.h"
using namespace NCL;
using namespace Rendering;
using namespace CSC3222;

GameSimsRenderer::GameSimsRenderer() : OGLRenderer(*Window::GetWindow())	{
	spriteShader = new OGLShader("GameSimsSpriteVert.glsl", "GameSimsSpriteFrag.glsl");
	debugLineShader = new OGLShader("GameSimsDebugVert.glsl", "GameSimsDebugFrag.glsl");

	spriteMesh = new OGLMesh(); 

	spriteMesh->SetVertexPositions({ Vector3(-0.5f, -0.5f, 0), Vector3(-0.5f, 0.5f, 0), Vector3(0.5f, -0.5f, 0) , Vector3(0.5f, 0.5f, 0) });
	spriteMesh->SetVertexTextureCoords({ Vector2(0,0),  Vector2(0,1) , Vector2(1,0) , Vector2(1,1) });

	spriteMesh->SetPrimitiveType(NCL::GeometryPrimitive::TriangleStrip);

	spriteMesh->UploadToGPU();

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

GameSimsRenderer::~GameSimsRenderer()	{
	delete spriteShader;
	delete spriteMesh;
}

void GameSimsRenderer::SetScreenProperties(int tileSize, int numTilesX, int numTilesY) {
	this->tileSize	= tileSize;
	this->numTilesX = numTilesX;
	this->numTilesY = numTilesY;
}

void GameSimsRenderer::AddSimObject(const SimObject* s) const {

}

void GameSimsRenderer::RemoveSimObject(const SimObject* s) {

}

void GameSimsRenderer::Update(float dt) {
	texAreas.clear();
	quickMeshes.clear();
}

void GameSimsRenderer::RenderFrame()	{
	//sort tex areas;

	BindShader(spriteShader);
	BindMesh(spriteMesh);

	GLuint screenSize	= glGetUniformLocation(spriteShader->GetProgramID(), "screenSize");
	GLuint spritePos	= glGetUniformLocation(spriteShader->GetProgramID(), "spritePos");
	GLuint spriteSize	= glGetUniformLocation(spriteShader->GetProgramID(), "spriteSize");

	GLuint texPos	= glGetUniformLocation(spriteShader->GetProgramID(), "texPos");
	GLuint texSize	= glGetUniformLocation(spriteShader->GetProgramID(), "texSize");

	GLuint invertX = glGetUniformLocation(spriteShader->GetProgramID(), "invertX");

	GLuint projMatrix = glGetUniformLocation(spriteShader->GetProgramID(), "projMatrix");


	Matrix4 ortho = Matrix4::Orthographic(-1, 1, (float)(tileSize * numTilesX), 0, (float)(tileSize * numTilesY), 0); //each sprite is 16 pixels, times how many sprites we want

	glUniformMatrix4fv(projMatrix, 1, false, ortho.array);

	glUniform2f(screenSize, (float)(tileSize * numTilesX), (float)(tileSize * numTilesY)); //

	glDisable(GL_DEPTH_TEST);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (auto&mesh : quickMeshes) {
		BindTextureToShader(mesh.texture, "spriteTex", 0);
		BindMesh(mesh.mesh);
		glUniform2f(spritePos, mesh.screenPos.x, mesh.screenPos.y); //
		glUniform2f(spriteSize, 1.0f, 1.0f);

		glUniform2f(texPos, 0, 0); //
		glUniform2f(texSize, 1, 1); //
		glUniform1i(invertX, 0);
		DrawBoundMesh(0, 1);
	}
	BindMesh(spriteMesh);
	for (auto &tex : texAreas) {
		BindTextureToShader(tex.texture, "spriteTex", 0);

		glUniform2f(spritePos, std::round(tex.screenPos.x), std::round(tex.screenPos.y)); //
		glUniform2f(spriteSize, tex.size.x, -tex.size.y); //

		glUniform2f(texPos, tex.start.x, tex.start.y); //
		glUniform2f(texSize, tex.size.x, tex.size.y); //

		glUniform1i(invertX, tex.flipX);

		DrawBoundMesh(0, 1);
	}	

	//Debug Lines
	if (debugLineVerts.size() > 0) {
		GLuint debugProjMatrix = glGetUniformLocation(debugLineShader->GetProgramID(), "projMatrix");
		OGLMesh* debugMesh = new OGLMesh();
		debugMesh->SetPrimitiveType(NCL::GeometryPrimitive::Lines);

		debugMesh->SetVertexPositions(debugLineVerts);
		debugMesh->SetVertexColours(debugLineColours);

		debugMesh->UploadToGPU();

		BindMesh(debugMesh);
		BindShader(debugLineShader);
		glUniformMatrix4fv(debugProjMatrix, 1, false, ortho.array);

		DrawBoundMesh();
		BindMesh(nullptr);

		delete debugMesh;
	}

	debugLineVerts.clear();
	debugLineColours.clear();
}

void GameSimsRenderer::DrawTextureArea(OGLTexture* texture, Vector2 start, Vector2 size, Vector2 screenPos, bool invertX) {
	TextureArea t;
	t.texture	= texture;
	t.screenPos = screenPos;
	t.start		= start;
	t.size		= size;
	t.flipX		= invertX;

	texAreas.emplace_back(t);
}

void GameSimsRenderer::DrawMesh(OGLMesh* mesh, OGLTexture* texture) {
	QuickMesh m;
	m.mesh = mesh;
	m.texture = texture;

	quickMeshes.emplace_back(m);
}

void GameSimsRenderer::DrawBox(Vector2 worldPos, Vector2 halfSize, Vector4 colour) {
	Vector3 worldStart = Vector3(worldPos.x, worldPos.y, 0);

	debugLineVerts.emplace_back(worldStart + Vector3(-halfSize.x, -halfSize.y, 0));
	debugLineVerts.emplace_back(worldStart + Vector3( halfSize.x, -halfSize.y, 0));

	debugLineVerts.emplace_back(worldStart + Vector3(halfSize.x, -halfSize.y, 0));
	debugLineVerts.emplace_back(worldStart + Vector3(halfSize.x,  halfSize.y, 0));

	debugLineVerts.emplace_back(worldStart + Vector3( halfSize.x, halfSize.y, 0));
	debugLineVerts.emplace_back(worldStart + Vector3(-halfSize.x, halfSize.y, 0));

	debugLineVerts.emplace_back(worldStart + Vector3(-halfSize.x, halfSize.y, 0));
	debugLineVerts.emplace_back(worldStart + Vector3(-halfSize.x,-halfSize.y, 0));

	for (int i = 0; i < 8; ++i) {
		debugLineColours.emplace_back(colour);
	}
}

void GameSimsRenderer::DrawCircle(Vector2 worldPos, float radius, Vector4 colour) {

	int numVerts = 16;

	float advance = (2 * Maths::PI) / (float)(numVerts-1);

	float currentPos = 0;

	Vector3 currentVert = Vector3(std::sin(0.0f), std::cos(0.0f), 0) * radius;
	Vector3 worldStart	= Vector3(worldPos.x, worldPos.y, 0);

	for (int i = 0; i < numVerts; ++i) {
		Vector3 start	= currentVert;
		Vector3 end		= Vector3(std::sin(currentPos), std::cos(currentPos), 0) * radius;

		currentVert = end;
		currentPos += advance;

		debugLineVerts.emplace_back(worldStart + start);
		debugLineVerts.emplace_back(worldStart + end);
	
		debugLineColours.emplace_back(colour);
		debugLineColours.emplace_back(colour);
	}

}
void GameSimsRenderer::DrawLine(Vector2 worldStart, Vector2 worldEnd, Vector4 colour) {
	debugLineVerts.emplace_back(Vector3(worldStart.x, worldStart.y, 0));
	debugLineVerts.emplace_back(Vector3(worldEnd.x, worldEnd.y, 0));

	debugLineColours.emplace_back(colour);
	debugLineColours.emplace_back(colour);
}

Matrix4 GameSimsRenderer::SetupDebugLineMatrix()		const {
	return Matrix4::Orthographic(-1, 1, (float)(tileSize * numTilesX), 0, 0, (float)(tileSize * numTilesY));
}

Matrix4 GameSimsRenderer::SetupDebugStringMatrix()	const {
	return Matrix4::Orthographic(-1, 1, (float)(tileSize * numTilesX), 0, 0, (float)(tileSize * numTilesY));
}
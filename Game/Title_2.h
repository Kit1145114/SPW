#pragma once
#include"Game.h"
#include"GamenDraw.h"
#include"SansenGamen.h"
#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/debug/math/tkVectorRender.h"
#include "Utility/MovePosition.h"

class MoveCharacter : public IGameObject{
public:
	void Init(wchar_t character, CFont* font) {
		ch[0] = character;
		ch[1] = '\0';
		m_font = font;
	}

	void PostRender(CRenderContext& rc) override;

	MovePosition& Pos() {
		return pos;
	}

private:
	MovePosition pos;
	CFont* m_font;
	wchar_t ch[2];
};

class Flush : public IGameObject{
public:
	void Init(prefab::CSpriteRender** background) {
		back = background;
		tex.CreateFromDDSTextureFromFile(L"sprite/dummy.dds");
		sprite.Init(tex, MainCamera2D().GetWidth(), MainCamera2D().GetHeight());
	}

	void Update() override;

	void PostRender(CRenderContext& rc) override{
		sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
	}

private:
	CShaderResourceView tex;
	CSprite sprite;
	float alpha = 0.0f;
	bool in = true;
	bool end = false;
	prefab::CSpriteRender** back;
};

class GamenDraw;
class SansenGamen;
class Title_2 : public IGameObject
{
public:
	Title_2();
	~Title_2();

	bool Start();
	void Update();

	void Setmode(int modeV)
	{
		mode = modeV;
	}
private:
	GamenDraw* m_Draw = nullptr;
	prefab::CSpriteRender* sprite_line = nullptr;

	Flush* flush = nullptr;
	float flushWait = 2.5f;

	prefab::CSpriteRender* m_background = nullptr;
	prefab::CSoundSource* m_bgm = nullptr;

	static constexpr wchar_t* titleName = L"spaceworld";
	static constexpr int sentenceNum = 10;
	MoveCharacter* sentence[sentenceNum];

	std::unique_ptr<DirectX::SpriteFont> dxFont;
	CFont m_font;

	int mode = 0;
};


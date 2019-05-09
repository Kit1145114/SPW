#pragma once
#include"Game.h"
#include"GamenDraw.h"
#include"SansenGamen.h"
#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/debug/math/tkVectorRender.h"

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
	prefab::CSpriteRender* m_spriteRender = nullptr;
	prefab::CSoundSource* m_bgm = nullptr;
	int mode = 0;
};


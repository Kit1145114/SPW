#pragma once
#include"Game.h"
#include"GamenDraw.h"
#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/debug/math/tkVectorRender.h"

class GamenDraw;

class Title_2 : public IGameObject
{
public:
	Title_2();
	~Title_2();

	bool Start();
	void Update();

	GamenDraw* m_Draw = nullptr;
	prefab::CSpriteRender* m_spriteRender = nullptr;
};


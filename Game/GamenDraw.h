#pragma once
#include"Game.h"

class Game;

class GamenDraw : public IGameObject
{
public:
	GamenDraw();
	~GamenDraw();

	void Update();
	void PostRender(CRenderContext& rc) override;
	CFont m_font;
	CVector2 m_position = CVector2::Zero;
	Game* m_game = nullptr;
};


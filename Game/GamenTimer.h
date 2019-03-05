#pragma once
#include"Game.h"

class Game;
class GamenTimer : public IGameObject
{
public:
	GamenTimer();
	~GamenTimer();

	void Update();
	void PostRender(CRenderContext& rc) override;
	CFont m_font;
	CVector2 m_position = CVector2::Zero;

	int m_timer = 0;
	int T = 60;
	Game* m_game = nullptr;
};


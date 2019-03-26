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

private:
	CFont m_font;
	Game* m_game = nullptr;
	CVector2 m_position = CVector2::Zero;
	int m_timer = 0;
	int MaxTimer = 5;
};


#pragma once
#include"Game.h"
#include"Player.h"

class Game;
class Player;
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
	Player* m_player = nullptr;
	CVector2 m_position = CVector2::Zero;
	int m_timer = 0;
	int frame = 60;
	int MaxTimer = 10;
	int MinTimer = 10;
};


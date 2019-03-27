#pragma once
#include"Game.h"

class Game;
class GameTaiki : public IGameObject
{
public:
	GameTaiki();
	~GameTaiki();
	void Update();
	void PostRender(CRenderContext& rc) override;
private:
	int timer = 0;
	int MaxTimer = 5;
	CFont m_font;
	Game* m_game = nullptr;
	CVector2 m_position = CVector2::Zero;

};


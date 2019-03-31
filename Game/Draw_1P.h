#pragma once
#include"Game.h"

class Game;
class Draw_1P : public IGameObject
{
public:
	Draw_1P();
	~Draw_1P();
	bool Start();
	void Update();
	void SetDeath(bool a)
	{
		Death = a;
	}
	enum EnState {
		enState_1P,
		enState_Gekitui
	};

	void SetPosition(int x, int y)
	{
		m_position.x = x;
		m_position.y = y;
	}
private:
	EnState m_state;
	Game* m_game = nullptr;
	prefab::CSpriteRender* m_spriteRender = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_scale = CVector3::Zero;
	int timer = 0;
	bool Death = false;
	bool State = false;
};


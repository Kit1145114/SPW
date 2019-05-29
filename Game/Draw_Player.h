#pragma once
#include"Game.h"

class Game;
class Draw_Player : public IGameObject
{
public:
	Draw_Player();
	~Draw_Player();
	bool Start();
	void Update();
	void SetDeath(bool a)
	{
		Death = a;
	}
	void SetPosition(int x, int y)
	{
		m_position.x = x;
		m_position.y = y;
	}
	void SetPlayerPicture(const wchar_t* player)
	{
		draw_P = player;
	}
private:
	prefab::CSpriteRender* m_spriteRender = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_scale = CVector3::Zero;
	bool Death = false;
	bool State = false;
	float timer = 0;
	float Limit = 3.0f;
	float yoko = 100.0f;
	float tate = 60.0f;
	const wchar_t* draw_P = nullptr;
};


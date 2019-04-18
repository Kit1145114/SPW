#pragma once
#include"Bullet.h"
#include"Player.h"
#include"Game.h"
#include"SansenKazu.h"

class Bullet;
class Player;
class Game;
class SansenKazu;
class Senkan_Rtype_2:public IGameObject
{
public:
	Senkan_Rtype_2();
	~Senkan_Rtype_2();
	bool Start();
	void Update();
	void Houdai();
	void SetShortCount(bool a)
	{
		ShortCount = a;
	}
	bool GetShortCount()
	{
		return ShortCount;
	}

private:
	Bullet* m_bullet = nullptr;
	Player* m_player =nullptr;
	Game* m_game = nullptr;
	SansenKazu* s_kazu = nullptr;
	int m_timer = 0;
	int m_Short = 0;
	int p_timer = 0;
	int PadNum = 0;
	bool ShortCount = false;
	int Maxtimer = 25;
	float HoukouX = 0.0f;
	float HoukouZ = 0.0f;
	float SpeedX = 0.0f;
	float SpeedZ = 0.0f;
};


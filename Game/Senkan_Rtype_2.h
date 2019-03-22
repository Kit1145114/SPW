#pragma once
#include"Bullet.h"
#include"Player.h"

class Bullet;
class Player;
class Senkan_Rtype_2:public IGameObject
{
public:
	Senkan_Rtype_2();
	~Senkan_Rtype_2();
	bool Start();
	void Update();
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
	Player* m_player = nullptr;
	int m_timer = 0;
	int m_Short = 0;
	int p_timer = 0;
	bool ShortCount = false;
};


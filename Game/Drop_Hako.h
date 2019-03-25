#pragma once
#include"Player.h"
#include"Game.h"

class Player;
class Game;
class Drop_Hako : public IGameObject
{
public:
	Drop_Hako();
	~Drop_Hako();
	bool Start();
	void Update();
	void Hantei();
	void Spawn();
	void Death();
	void Push();
	CVector3 GetPosition()
	{
		return m_position;
	}
	void SetPosition(CVector3 hkpos)
	{
		m_position = hkpos;
	}
	void SetSpwanCount(int a)
	{
		spwancount += a;
	}
	int GetSpwanCount()
	{
		return spwancount;
	}

private:
	Player * m_player = nullptr;
	Game* game = nullptr;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CVector3 m_position = CVector3::Zero;
	CQuaternion m_rotation = CQuaternion::Identity;
	CVector3 m_scale = { 1.0f,1.0f,1.0f };

	int timer = 0;
	int spwancount = 0;
};


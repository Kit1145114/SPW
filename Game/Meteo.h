#pragma once
#include"Game.h"

class Game;
class Meteo: public IGameObject
{
public:
	Meteo();
	~Meteo();
	bool Start();
	void Update();
	void Move();
	void Hantei();
	void Death();
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
private:
	Game* game = nullptr;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	CVector3 randomspeed = CVector3::Zero;
	CQuaternion m_rotation = CQuaternion::Identity;
	CVector3 scale = CVector3::Zero;
	float hantei = 2500.0f;
	float Speed = 5000.0f;
	float PosMaxLimitx = 35000.0f;
	float PosMaxLimitz = 20000.0f;
	bool repopflag = false;
	bool movecount = false;
};


#pragma once
#include"Game.h"

class Game;
class Planet;
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
	void Rotation();
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	CVector3 GetPosition()
	{
		return m_position;
	}
	void SetMoveSpeed(CVector3 speed) {
		randomspeed = speed;
	}

	float getRadius() {
		return hantei;
	}
	void SetRadius(float rad)
	{
		radius = rad;
	}
private:
	Game* game = nullptr;
	Planet* pla = nullptr;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	CVector3 randomspeed = CVector3::Zero;
	CQuaternion m_rotation = CQuaternion::Identity;
	CVector3 scale = CVector3::Zero;
	int Plkazu = 12;
	float angleY = 0.0f;	
	float angleX = 0.0f;
	float hantei = 2500.0f;
	float Plhantei = 2500.0f;
	float Metehantei = 5000.0f;
	float Speed = 5000.0f;
	float PosMaxLimitx = 40000.0f;
	float PosMaxLimitz = 30000.0f;
	float radius = 0.0f;
	bool repopflag = false;
	bool movecount = false;
	const wchar_t* mete[12] = { nullptr };
};


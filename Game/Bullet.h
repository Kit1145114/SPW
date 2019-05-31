#pragma once
#include"Game.h"

class Player;

class Game;
class Bullet : public IGameObject
{
public:
	Bullet();
	~Bullet();

	bool Start();
	CVector3 GetPosition() {
		return m_position;
	}
	void SetPosition(CVector3 plpos)
	{
		m_position = plpos;
	}
	void SetPositionXZ(float x ,float z)
	{
		m_position.x += x;
		m_position.z += z;
	}
	void SetPositionX(float x)
	{
		m_position.x = x;
	}
	CVector3 GetMoveSpeed()
	{
		return m_moveSpeed;
	}
	void SetMoveSpeedZ(float a, float b)
	{
		m_moveSpeed.x = a;
		m_moveSpeed.z = b;
	}
	void SetMoveSpeed(CVector3 mspos)
	{
		m_moveSpeed += mspos;
	}
	void SetKill(bool a)
	{
		Kill = a;
	}
	bool GetKill()
	{
		return Kill;
	}
	void SetPBnum(int a)
	{
		PB = a;
	}
	int GetPB() const {
		return PB;
	}

	void Update();
	void Death();
	void BulletDeath();
	int GetPB();
private:
	Game * m_game = nullptr;
	int PB = 0;
	int Limit = 1.95f;
	float timer = 0.0f;
	float BulletHantei = 500.0f;
	float BulletYpos = 300.0f;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	CVector3 m_scale = { 1.0f,1.0f,1.0f };
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	bool Kill = false;
};


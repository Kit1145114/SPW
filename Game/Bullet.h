#pragma once
#include"Game.h"

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
	void SetPositionZ(float x ,float z)
	{
		m_position.x += x;
		m_position.z += z;
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
		m_moveSpeed = mspos;
	}
	void SetKill(bool a)
	{
		Kill = a;
	}
	bool GetKill()
	{
		return Kill;
	}
	void Update();
private:
	Game * m_game = nullptr;
	int m_timer = 0;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	bool Kill = false;
};


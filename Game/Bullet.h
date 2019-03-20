#pragma once
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
	void SetPositionY(float y,float x, float z)
	{
		m_position.y = y;
		m_position.x = x;
		m_position.z = z;
	}
	CVector3 GetMoveSpeed()
	{
		return m_moveSpeed;
	}
	void SetMoveSpeed(float a)
	{
		m_moveSpeed.z = a;
	}
	void Update();
private:
	int m_timer = 0;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
};


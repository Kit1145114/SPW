#pragma once
class Bullet : public IGameObject
{
public:
	Bullet();
	~Bullet();

	bool Start();
	void Update();
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	int m_timer = 0;
};


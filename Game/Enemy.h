#pragma once
class Enemy : public IGameObject
{
public:
	Enemy();
	~Enemy();

	bool Start();
	void Update();

	CCharacterController m_CharaCon;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	CQuaternion m_rotation = CQuaternion::Identity;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;

};


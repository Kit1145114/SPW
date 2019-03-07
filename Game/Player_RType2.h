#pragma once
#include"Bullet.h"
#include"Player.h"

class Bullet;
class Player;

class Player_RType2:public IGameObject
{
public:
	Player_RType2();
	~Player_RType2();
	bool Start();

	void Update();
	void Move();
	void PBullet();
	Player* m_player = nullptr;
	Bullet* m_bullet = nullptr;
	CCharacterController m_CharaCon;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	CQuaternion m_rotation = CQuaternion::Identity;

	prefab::CSkinModelRender* m_skinModelRender = nullptr;

	int m_timer = 0;
	int m_Short = 0;
	int m_mode = 0;
};


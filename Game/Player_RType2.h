#pragma once
#include"Bullet.h"
#include"Player.h"
#include"Game.h"
#include"Enemy.h"

class Bullet;
class Player;
class Enemy;
class Game;

class Player_RType2:public IGameObject
{
public:
	Player_RType2();
	~Player_RType2();
	bool Start();
	void Update();
	void Move();
	void PBullet();
	void PHantei();
	void Rotation();
	CVector3 GetPosition()
	{
		return m_position;
	}
	void SetPosition(CVector3 plpos2)
	{
		m_position = plpos2;
	}
	CVector3 GetMoveSpeed()
	{
		return m_moveSpeed;
	}
	void GetMoveSpeed(CVector3 plmov2)
	{
		m_moveSpeed = plmov2;
	}
	CVector3 m_position = CVector3::Zero;
	bool ShortCount = false;
private:
	Player* m_player = nullptr;
	Bullet* m_bullet = nullptr;
	Game* m_game = nullptr;
	Enemy* m_enemy = nullptr;
	CCharacterController m_CharaCon;

	CVector3 m_moveSpeed = CVector3::Zero;
	CQuaternion m_rotation = CQuaternion::Identity;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	int m_timer = 0;
	int m_Short = 0;
	int m_mode = 0;
	int p_timer = 0;
};


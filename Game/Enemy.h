#pragma once
#include"Player.h"
#include"Bullet.h"
#include"Senkan_Rtype_2.h"
#include"Game.h"
#include"Star.h"

class Senkan_Rtype_2;
class Player;
class Bullet;
class Game;
class Star;

class Enemy : public IGameObject
{
public:
	Enemy();
	~Enemy();

	bool Start();
	void Update();
	void Pl_Hantei();
	void Death();
	void Move();
	void Rotation();
	CVector3 GetPosition()
	{
		return m_position;
	}
	void SetPosition(CVector3 enpos)
	{
		m_position = enpos;
	}
	CVector3 GetMovePosition()
	{
		return m_moveSpeed;
	}
	void GetPosition(CVector3 enmov)
	{
		m_moveSpeed = enmov;
	}

private:
	CCharacterController m_CharaCon;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	CQuaternion m_rotation = CQuaternion::Identity;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	Player* m_player[3] = { nullptr };
	Senkan_Rtype_2* S_RType2 = nullptr;
	Bullet* m_bullet = nullptr;
	Game* m_game = nullptr;
	Star* m_star = nullptr;
	int PadKazu = 0;
};


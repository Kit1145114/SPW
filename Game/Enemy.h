#pragma once
#include"Player.h"
#include"Bullet.h"
#include"Game.h"
class Player;
class Bullet;
class Game;

class Enemy : public IGameObject
{
public:
	Enemy();
	~Enemy();

	bool Start();
	void Update();
	void Hantei();

	CCharacterController m_CharaCon;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	CQuaternion m_rotation = CQuaternion::Identity;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	Player* m_player = nullptr;
	Bullet* m_bullet = nullptr;
	Game* m_game = nullptr;
};


#pragma once
#include"Bullet.h"
#include"Player_RType2.h"
#include"Game.h"
#include"Enemy.h"
#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
#include "tkEngine/character/tkCharacterController.h"

class Bullet;
class Player_RType2;
class Game;
class Enemy;

class Player: public IGameObject
{
public:
	Player();
	~Player();

	bool Start();
	void Update();
	void Move();
	void PBullet();
	void Pevolution();
	void Hantei();
	void Rotation();

	Player_RType2* m_player_Rtype2 = nullptr;
	Bullet* m_bullet = nullptr;
	Game* m_game = nullptr;
	Enemy* m_enemy = nullptr;

	CCharacterController m_CharaCon;
	CVector3 m_position = CVector3::Zero;
	CVector3 memory_position = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	CQuaternion m_rotation = CQuaternion::Identity;

	prefab::CSkinModelRender* m_skinModelRender = nullptr;

	int m_timer = 0;
	int p_timer = 0;
	int m_Short = 0;
	int Ver = 0;
	int ShortCount = 0;
	int m_mode = 0;
};


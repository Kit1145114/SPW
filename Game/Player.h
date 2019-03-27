#pragma once
#include"Bullet.h"
#include"Player_RType2.h"
#include"Senkan_Rtype_2.h"
#include"Game.h"
#include"Enemy.h"
#include"Drop_Hako.h"
#include"Star.h"
#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
#include "tkEngine/character/tkCharacterController.h"

class Bullet;
class Player_RType2;
class Game;
class Enemy;
class Senkan_Rtype_2;
class Drop_Hako;
class Star;

class Player: public IGameObject
{
public:
	Player();
	~Player();

	bool Start();
	void Update();
	void Move();
	void PBullet();
	void PBullet2();
	void Pevolution();
	void Hantei();
	void Rotation();
	void Death();
	void Respawn();
	void HakoHantei();
	void Houdai();
	void S_Hantei();
	void B_Hantei();
	void P_Hantei();
	CVector3 GetPosition() {
		return m_position;
	}
	void SetPosition(CVector3 plpos)
	{
		m_position = plpos;
	}
	void SetPositionX(float x)
	{
		m_position.x = x;
	}
	CVector3 GetMoveSpeed()
	{
		return m_moveSpeed;
	}
	void SetMoveSpeedZ(float a)
	{
		m_moveSpeed.z = a;
	}
	void SetVer(float a)
	{
		Ver = a;
	}
	int GetVer()
	{
		return Ver;
	}
	void SetStarCount(int a)
	{
		StarCount += a;
	}
	int GetStarCount()
	{
		return StarCount;
	}
	void SetShortCount(bool a)
	{
		ShortCount = a;
	}
	bool GetShortCount()
	{
		return ShortCount;
	}
	bool GetDeathCount()
	{
		return DeathCount;
	}
	CVector3 GetMemoryPosition()
	{
		return memory_position;
	}
	void  SetPadNum(int num)
	{
		PadNum = num;
	}
	int GetPadNum()
	{
		return PadNum;
	}
private:
	Player_RType2* m_player_Rtype2 = nullptr;
	Senkan_Rtype_2* S_Rtype2 = nullptr;
	Bullet* m_bullet = nullptr;
	Game* m_game = nullptr;
	Enemy* m_enemy = nullptr;
	Star* m_star = nullptr;
	Drop_Hako* d_hako = nullptr;
	CCharacterController m_CharaCon;
	CVector3 m_position = CVector3::Zero;
	CVector3 memory_position = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	CVector3 b_moveSpeed = CVector3::Zero;
	CVector3 m_scale = { 1.0f,1.0f,1.0f };
	CQuaternion m_rotation = CQuaternion::Identity;
	CVector3 b_position = CVector3::Zero;
	
	prefab::CSkinModelRender* m_skinModelRender = nullptr;

	int m_timer = 0.0f;
	int p_timer = 0;
	int d_timer = 0;
	int m_Short = 0;
	int m_mode = 0;
	int Ver = 0;
	int StarCount = 0;
	int PadNum = 0;
	float HoukouX = 0.0f;
	float HoukouZ = 0.0f;
	float SpeedX = 0.0f;
	float SpeedZ = 0.0f;

	bool DeathCount = false;
	bool ShortCount = false;
	bool MyBullet = true;
};


#pragma once
#include"field.h"
#include"Camera.h"
#include"Player.h"
#include"Player_RType2.h"
#include"GamenTimer.h"
#include"Enemy.h"
#include"Title_2.h"
#include"Planet.h"
#include"Star.h"
#include"Sinka_Bar.h"
#include"Drop_Hako.h"
#include"SansenKazu.h"
#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
#include "tkEngine/character/tkCharacterController.h"

class field;
class Camera;
class Player;
class GamenTimer;
class Enemy;
class Title_2;
class Planet;
class Player_RType2;
class Star;
class Sinka_Bar;
class Drop_Hako;
class SansenKazu;

enum Planetnumber {
	Planetnumber_00,
	Planetnumber_01,
	Planetnumber_02,
	Planetnumber_03,
	Planetnumber_04,
	Planetnumber_05,
	Planetnumber_06,
	Planetnumber_07,
	Planetnumber_08,
	Planetnumber_09,
	Planetnumber_10,
	Planetnumber_11,
	Planetnumber_Num
};

const int PlKazu = 4;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void P_Ver();
	void S_Pu();
	void H_Pu();
	void PlayerNum();
	void CameraPos();
	void Star_Life();
	void Bullet_Life();
	void SetGameMode(int a)
	{
		GameMode = a;
	}
	void SetPlanetAgeinCount(int a)
	{
		PlanetAgeinCount =+ a;
	}
	int GetPlanetAgeinCount()
	{
		return PadKazu;
	}
	CVector3 GetPosition() {
		return memory_position;
	}//�p�b�h�̐�
	int GetPadKazu()
	{
		return PadKazu;
	}//�v���C���[�̒e�����݂��Ă��邩
	void SetPBInit(bool a)
	{
		PBullet_Init = a;
	}//�ʂ��邩��Ԃ��B
	bool GetPBInit()
	{
		return PBullet_Init;
	}//�e�̐�
	void SetKazu(int a)
	{
		PB_Kazu += a;
	}
	//�X�^�[�̐�
	void SetStarCount(int kazu)
	{
		StarCount += kazu;
	}//�X�^�[�����݂��Ă��邩
	bool GetS_Init()
	{
		return S_Init;
	}//�Q�[�����̋�
	Planet* memoryPP[Planetnumber_Num];
	Player* m_player[PlKazu] = {nullptr};
	Enemy* m_enemy = nullptr;
	Star* m_star = nullptr;
	Drop_Hako* d_hako = nullptr;
private:
	//Star * m_star = nullptr;
	Camera* m_camera = nullptr;
	field* m_field = nullptr;
	GamenTimer* m_G_Timer = nullptr;
	Planet* m_planet = nullptr;
	Player_RType2* m_player_Rtype2 = nullptr;
	Sinka_Bar*s_bar = nullptr;
	SansenKazu* s_kazu = nullptr;
	CVector3 memory_position = CVector3::Zero;
	
	int GameMode = 0;
	int Pver = 0;
	int starget = 0;
	int MAXPad = 3;
	int MINPad = 1;
	//int PadNum = 0;
	int NumMin = 0;
	int PadMaxKazu =0;
	int PadKazu = 0;
	int PlanetAgeinCount = 0;
	int StarCount  = 0;
	int Star0 = 0;
	float P_pos = 400.0f;
	float MaxC_pos = 1700.0f;
	float MinC_pos = 800.0f;
	int PB_Kazu = 0;
	bool PBullet_Init = false;
	bool S_Init = false;
	CVector3 Kyori = CVector3::Zero;
	CVector3 SyokiCamera = CVector3::Zero;
	CVector3 Tyuou = CVector3::Zero;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;		//�X�L�����f�������_���[�B
};


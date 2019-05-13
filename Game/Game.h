#pragma once
#include"BlackHole.h"
#include"field.h"
#include"Camera.h"
#include"Player.h"
#include"GamenTimer.h"
#include"Enemy.h"
#include"Title_2.h"
#include"ResultGamen.h"
#include"Planet.h"
#include"Star.h"
#include"Sinka_Bar.h"
#include"Draw_Player.h"
#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
#include "tkEngine/character/tkCharacterController.h"

class BlackHole;
class field;
class Camera;
class Player;
class GamenTimer;
class Enemy;
class Title_2;
class ResultGamen;
class Planet;
class Player_RType2;
class Star;
class Sinka_Bar;
class Draw_Player;


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
	void Star_Life();
	void Bullet_Life();
	void PlStar_Life();
	static Game* GetInstance();

	void SetGameMode(int a)
	{
		GameMode = a;
	}
	void SetPlanetAgeinCount(int a)
	{
		PlanetAgeinCount =+ a;
	}
	CVector3 GetPosition() {
		return memory_position;
	}
	void SetSanSenkazu(int kazu)
	{
		SansenKazu = kazu;
	}
	int GetSansenKazu()
	{
		return SansenKazu;
	}
	//プレイヤーの弾が存在しているか
	void SetPBInit(bool a)
	{
		PBullet_Init = a;
	}//玉あるかを返す。
	bool GetPBInit()
	{
		return PBullet_Init;
	}//弾の数
	void SetKazu(int a)
	{
		PB_Kazu += a;
	}
	//スターの数
	void SetStarCount(int kazu)
	{
		StarCount += kazu;
	}//スターが存在しているか
	bool GetS_Init()
	{
		return S_Init;
	}
	void AddPlStarCount(int kazu)
	{
		PlStarCount += kazu;
	}
	bool GetPlS_Init()
	{
		return PlS_Init;
	}
	Planet* memoryPP[Planetnumber_Num];
	Player* m_player[PlKazu] = {nullptr};
	Enemy* m_enemy = nullptr;
	Star* m_star = nullptr;
private:
	BlackHole* bh = nullptr;
	static Game* m_instance;
	Draw_Player* Pl1= nullptr;
	Camera* m_camera = nullptr;
	field* m_field = nullptr;
	GamenTimer* m_G_Timer = nullptr;
	Planet* m_planet = nullptr;
	Player_RType2* m_player_Rtype2 = nullptr;
	Sinka_Bar*s_bar = nullptr;
	CVector3 memory_position = CVector3::Zero;
	
	int GameMode = 0;
	int Stage = 1;          //二つ目の戦闘場所。
	int Pver = 0;
	int starget = 0;
	int MAXPad = 3;
	int MINPad = 1;
	//int PadNum = 0;
	int NumMin = 0;
	int SansenKazu = 0;
	int PlanetAgeinCount = 0;
	int StarCount  = 0;
	int PlStarCount = 0;
	int Star0 = 0;
	float P_pos = 1000.0f;
	float MaxC_pos = 1700.0f;
	float MinC_pos = 1600.0f;
	int PB_Kazu = 0;
	bool PBullet_Init = false;
	bool S_Init = false;
	bool PlS_Init = false;
	CVector3 Kyori = CVector3::Zero;
	CVector3 SyokiCamera = CVector3::Zero;
	CVector3 Tyuou = CVector3::Zero;
	//CVector3 BHpos1 = { 0.0f , 0.0f, 5000.0f };
	//CVector3 BHsca1 = { 1000.0f,0.0f,5.0f };
	prefab::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
};


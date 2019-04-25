#pragma once
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
#include"Drop_Hako.h"
#include"SansenKazu.h"
#include"Draw_1P.h"
#include"Draw_2P.h"
#include"Draw_3P.h"
#include"Draw_4P.h"
#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
#include "tkEngine/character/tkCharacterController.h"

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
class Drop_Hako;
class SansenKazu;
class Draw_1P;
class Draw_2P;
class Draw_3P;
class Draw_4P;

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
	int GetPlanetAgeinCount()
	{
		return PadKazu;
	}
	CVector3 GetPosition() {
		return memory_position;
	}//パッドの数
	int GetPadKazu()
	{
		return s_kazu->GetKazu();
	}//プレイヤーの弾が存在しているか
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
	static Game* m_instance;
	Draw_1P* Pl1 = nullptr;
	Draw_2P* Pl2 = nullptr;
	Draw_3P* Pl3 = nullptr;
	Draw_4P* Pl4 = nullptr;
	Camera* m_camera = nullptr;
	Drop_Hako* d_hako = nullptr;
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
	int PlStarCount = 0;
	int Star0 = 0;
	float P_pos = 700.0f;
	float MaxC_pos = 1700.0f;
	float MinC_pos = 1600.0f;
	int PB_Kazu = 0;
	bool PBullet_Init = false;
	bool S_Init = false;
	bool PlS_Init = false;
	CVector3 Kyori = CVector3::Zero;
	CVector3 SyokiCamera = CVector3::Zero;
	CVector3 Tyuou = CVector3::Zero;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
};


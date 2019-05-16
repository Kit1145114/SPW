#pragma once
#include"BlackHole.h"
#include"field.h"
#include"Camera.h"
#include"Player.h"
#include"GamenTimer.h"
#include"Meteo.h";
#include"Enemy.h"
#include"Title_2.h"
#include"ResultGamen.h";
#include"Planet.h";
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
class Meteo;
class Enemy;
class Title_2;
class ResultGamen;
class Planet;
class Player_RType2;
class Star;
class Sinka_Bar;
class Draw_Player;
class SatelliteGene;

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
	void PlStar_Life();
	void Stage2();
	static Game* GetInstance();

	void SetGameMode(int a)
	{
		GameMode = a;
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

	 //弾の数
	void SetKazu(int a)
	{
		PB_Kazu += a;
	}
	//スターの数
	void SetStarCount(int kazu)
	{
		StarCount += kazu;
	}//スターが存在しているか
	void AddPlStarCount(int kazu)
	{
		PlStarCount += kazu;
	}

	//遊ぶステージを設定する
	void setStage(int _stage) {
		Stage = _stage;
	}

private:
	void CreateStage0();
	void CreateStage1();
	void CreateStage2();
public:
	Planet* memoryPP[Planetnumber_Num] = {};
	Player* m_player[PlKazu] = {nullptr};
	Enemy* m_enemy = nullptr;
	Star* m_star = nullptr;
private:
	static Game* m_instance;
	Camera* m_camera = nullptr;
	field* m_field = nullptr;
	GamenTimer* m_G_Timer = nullptr;
	Meteo* meteo = nullptr;
	SatelliteGene* satelliteG = nullptr;
	prefab::CSoundSource* bgmSoundSource = nullptr;//BGM用のサウンドソース。
	
	int GameMode = 0;
	int Stage = 0;          //ステージ選択用
	int SansenKazu = 0;
	int StarCount  = 0;
	int PlStarCount = 0;
	float P_pos = 1800.0f;

	int PB_Kazu = 0;
	int timer = 0;
	bool PlS_Init = false;
	//CVector3 BHpos1 = { 0.0f , 0.0f, 5000.0f };
	//CVector3 BHsca1 = { 1000.0f,0.0f,5.0f };
};


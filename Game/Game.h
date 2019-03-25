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
	void SetGameMode(int a)
	{
		GameMode = a;
	}

	CVector3 GetPosition() {
		return memory_position;
	}

	Planet* memoryPP[Planetnumber_Num];
	Player* m_player = nullptr;
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
	CVector3 memory_position = CVector3::Zero;
	int GameMode = 0;
	int Pver = 0;
	int starget = 0;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
};


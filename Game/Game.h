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

class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void P_Ver();
	void S_Pu();

	Player* m_player = nullptr;
	Camera* m_camera = nullptr;
	field* m_field = nullptr;
	GamenTimer* m_G_Timer = nullptr;
	Enemy* m_enemy = nullptr;
	Planet* m_planet = nullptr;
	Player_RType2* m_player_Rtype2 = nullptr;
	Star* m_star = nullptr;
	Sinka_Bar*s_bar = nullptr;
	int GameMode = 0;
	int Pver = 0;
	int starget = 0;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
};


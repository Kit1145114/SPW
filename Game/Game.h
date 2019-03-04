#pragma once
#include"field.h"
#include"Camera.h"
#include"Player.h"
#include"GamenTimer.h"
#include"Enemy.h"
#include"Title_2.h"
#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
#include "tkEngine/character/tkCharacterController.h"

class field;
class Camera;
class Player;
class GamenTimer;
class Enemy;
class Title_2;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();

	Player* m_player = nullptr;
	Camera* m_camera = nullptr;
	field* m_field = nullptr;
	GamenTimer* m_G_Timer = nullptr;
	Enemy* m_enemy = nullptr;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
};


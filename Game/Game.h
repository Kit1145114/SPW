#pragma once
#include"field.h"
#include"Camera.h"

#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
#include "tkEngine/character/tkCharacterController.h"

class field;
class Camera;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();

	Camera* m_camera = nullptr;
	field* m_field = nullptr;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
};


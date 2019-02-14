#pragma once
#include"Game.h"
#include "tkEngine/character/tkCharacterController.h"

class Game;
class Title_1 : public IGameObject
{
public:
	Title_1();
	~Title_1();

	bool Start();
	void Update();

	prefab::CSpriteRender* m_spriteRender = nullptr;
};


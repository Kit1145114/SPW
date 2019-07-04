#pragma once
#include"Game.h"
#include"Title_2.h"
#include "tkEngine/character/tkCharacterController.h"

class Game;
class Title_1 : public IGameObject
{
public:
	Title_1();
	~Title_1();

	bool Start();
	void Update();

private:
	float timer = 0.0f;
	float Limit = 3.0f;
	prefab::CSpriteRender* m_spriteRender = nullptr;

	bool isSecondSprite = false;
};


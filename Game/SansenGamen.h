#pragma once
#include"Game.h"
#include"SansenKazu.h"

class SansenKazu;

class SansenGamen : public IGameObject
{
public:
	SansenGamen();
	~SansenGamen();
	bool Start();
	void Update();
	
private:
	SansenKazu * s_kazu = nullptr;
	prefab::CSpriteRender* m_spriteRender = nullptr;

};


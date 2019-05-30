#pragma once
#include"Title_2.h"

class SetumeiGamen : public IGameObject
{
public:
	SetumeiGamen();
	~SetumeiGamen();
	bool Start();
	void Update();
private: 
	prefab::CSpriteRender* m_spriteRender = nullptr;
	prefab::CSoundSource* m_push = nullptr;
	prefab::CSoundSource* m_bgm = nullptr;
};


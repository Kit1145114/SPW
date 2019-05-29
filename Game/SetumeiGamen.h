#pragma once
#include"Title_2.h"

class SetumeiGamen : public IGameObject
{
public:
	SetumeiGamen();
	~SetumeiGamen();
	bool Start();
	void Update();
	void Kirikae();
private: 
	prefab::CSpriteRender* m_spriteRender = nullptr;
	prefab::CSoundSource* m_push = nullptr;
	prefab::CSoundSource* m_bgm = nullptr;
	int mode = 0;
};


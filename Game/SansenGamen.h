#pragma once
#include"Game.h"

class SansenGamen : public IGameObject
{
public:
	SansenGamen();
	~SansenGamen();
	bool Start();
	void Update();
	void PostRender(CRenderContext& rc) override;

private:
	CFont m_font;
	prefab::CSpriteRender* m_spriteRender = nullptr;
	int Kazu = 1;
	int MaxKazu = 4;
	int MinKazu = 1;
	bool GameStart = false;
	bool Death = false;
};


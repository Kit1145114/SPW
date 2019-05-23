#pragma once
#include"Game.h"
#include "Utility/MoveSprite.h"

class SansenGamen : public IGameObject
{
public:
	SansenGamen();
	~SansenGamen();
	bool Start();
	void Update();
	void PostRender(CRenderContext& rc) override;

	void setBackGround(prefab::CSpriteRender* back) {
		sprite_back = back;
	}

private:
	CFont m_font;
	prefab::CSpriteRender* sprite_back = nullptr;
	MoveSprite* sprite_player = nullptr;
	MoveSprite* sprite_num = nullptr;
	prefab::CSoundSource* m_push = nullptr;
	int Kazu = 1;
	int MaxKazu = 4;
	int MinKazu = 1;
	bool GameStart = false;
	bool Death = false;

	float waitStageSelect = -1.0f;
};


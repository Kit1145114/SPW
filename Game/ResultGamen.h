#pragma once
#include"Title_2.h"
#include"Player.h"
#include"ResultDraw.h"

class Player;
class Title_2;
class ResultDraw;
class ResultGamen : public IGameObject
{
public:
	ResultGamen();
	~ResultGamen();
	bool Start();
	void Update();
	void Result();
	void SetSansenKazu(int kazu)
	{
		PadKazu = kazu;
	}
private:
	ResultDraw* r_Draw[4] = { nullptr };
	Player* m_player[4] = {nullptr};
	int PS[4] = { 0 };
	int Max = 3;
	int m_timer = 0;
	int PadKazu = 0;
	prefab::CSpriteRender* r_spriteRender = nullptr;
	prefab::CSpriteRender* P1_spriteRender = nullptr;
	prefab::CSpriteRender* P2_spriteRender = nullptr;
	prefab::CSpriteRender* P3_spriteRender = nullptr;
	prefab::CSpriteRender* P4_spriteRender = nullptr;
	CVector3 N1position = { -220.0f,120.0f,0.0f };
	CVector3 N2position = { 230.0f,120.0f,0.0f };
	CVector3 N3position = { -220.0f,-180.0f,0.0f };
	CVector3 N4position = { 230.0f,-180.0f,0.0f };
};


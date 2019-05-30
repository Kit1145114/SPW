#pragma once
#include"Title_2.h"
#include"Player.h"
#include"ResultDraw.h"
#include "Utility/MoveSprite.h"

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
	void GateDraw();
	void SetSansenKazu(int kazu)
	{
		PadKazu = kazu;
	}
	void SetStage(int sta)
	{
		stage = sta;
	}
	void PostRender(CRenderContext& rc) override;
private:
	CFont m_font;
	std::array<ResultDraw*, 4> r_Draw = { nullptr };
	std::array<Player*, 4> m_player = { nullptr };
	std::array<int, 4> PS = { -1, -1, -1, -1 };
	int Max = 3;
	int m_timer = 0;
	int PadKazu = 0;
	std::array<int, 4> PNums;
	int timer = 0;
	int stage = 0;
	prefab::CSpriteRender* r_spriteRender = nullptr;
	//プレイヤー
	const wchar_t* draw_P[4] = { nullptr };
	prefab::CSpriteRender* P_spriteRender[4] = { nullptr };
	CVector3 N1position = { 40.0f,180.0f,0.0f };
	CVector3 N2position = { 40.0f,39.0f,0.0f };
	CVector3 N3position = { 40.0f,-110.0f,0.0f };
	CVector3 N4position = { 40.0f,-260.0f,0.0f };
	//ゲート。
	int junban = 0;
	int Limit = 80;
	int StarCount[4] = { 0 };
	float change = 1000.0f;
	prefab::CSpriteRender* G_spriteRender[4] = { nullptr };
	float GateSizeX = 700.0f;
	float GateSizeY = 100.0f;
	CVector3 G1position = { 180.0f,180.0f,0.0f };
	CVector3 G2position = { 180.0f,39.0f,0.0f };
	CVector3 G3position = { 180.0f,-110.0f,0.0f };
	CVector3 G4position = { 180.0f,-260.0f,0.0f };
};


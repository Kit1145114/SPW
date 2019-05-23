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
private:
	ResultDraw* r_Draw[4] = { nullptr };
	Player* m_player[4] = { nullptr };
	int PS[4] = { -1, -1, -1, -1 };
	int Max = 3;
	int m_timer = 0;
	int PadKazu = 0;
	int PNums[4];
	int timer = 0;
	int stage = 0;
	prefab::CSpriteRender* r_spriteRender = nullptr;
	//プレイヤー
	const wchar_t* draw_P[4] = { nullptr };
	prefab::CSpriteRender* P_spriteRender[4] = { nullptr };
	CVector3 N1position = { 180.0f,180.0f,0.0f };
	CVector3 N2position = { 180.0f,39.0f,0.0f };
	CVector3 N3position = { 180.0f,-110.0f,0.0f };
	CVector3 N4position = { 180.0f,-260.0f,0.0f };
	//ゲート。
	int junban = 0;
	int Limit = 80;
	float change = 900.0f;
	prefab::CSpriteRender* G_spriteRender[4] = { nullptr };
	float GateSizeX = 500.0f;
	float GateSizeY = 100.0f;
	CVector3 G1position = { 180.0f,180.0f,0.0f };
	CVector3 G2position = { 180.0f,39.0f,0.0f };
	CVector3 G3position = { 180.0f,-110.0f,0.0f };
	CVector3 G4position = { 180.0f,-260.0f,0.0f };
	//prefab::CSpriteRender* G_spriteRender[8] = { nullptr };
	//float GateSizeX = 205.0f;
	//float GateSizeY = 100.0f;
	//CVector3 G1position = { 50.0f,189.0f,0.0f };
	//CVector3 G2position = { 250.0f,189.0f,0.0f };
	//CVector3 G3position = { 50.0f,39.0f,0.0f };
	//CVector3 G4position = { 250.0f,39.0f,0.0f };
	//CVector3 G5position = { 50.0f,-121.0f,0.0f };
	//CVector3 G6position = { 250.0f,-121.0f,0.0f };
	//CVector3 G7position = { 50.0f,-271.0f,0.0f };
	//CVector3 G8position = { 250.0f,-271.0f,0.0f };
};


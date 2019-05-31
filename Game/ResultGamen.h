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
	/*void SetStage(int sta)
	{
		stage = sta;
	}*/
	void PostRender(CRenderContext& rc) override;
private:
	CFont m_font;
	std::array<ResultDraw*, 4> r_Draw = { nullptr };//順位を表示するオブジェクトの配列

	std::array<int, 4> PS = { -1, -1, -1, -1 };//プレイヤーの獲得した星の数

	int PadKazu = 0;//参戦人数
	//int stage = 0;ステージによって背景を変えるという案が昔あった
	prefab::CSpriteRender* r_spriteRender = nullptr;//背景

	//プレイヤー
	prefab::CSpriteRender* P_spriteRender[4] = { nullptr };
	const wchar_t* draw_P[4] = {
		L"sprite/1Player.dds",
		L"sprite/2Player.dds",
		L"sprite/3Player.dds",
		L"sprite/4Player.dds"
	};
	const CVector3 N_pos_array[4] = {
		{ 40.0f,180.0f,0.0f },
		{ 40.0f,39.0f,0.0f },
		{ 40.0f,-110.0f,0.0f },
		{ 40.0f,-260.0f,0.0f }
	};


	//ゲート。
	int timer = 0;
	int junban = 0;
	const int Limit = 80;
	int StarCount[4] = { 0 };
	const float change = 1000.0f;
	prefab::CSpriteRender* G_spriteRender[4] = { nullptr };
	prefab::CSoundSource* resultSound = nullptr;
	const float GateSizeX = 700.0f;
	const float GateSizeY = 100.0f;
	CVector3 G_pos_array[4] = {
		{ 180.0f,180.0f,0.0f },
		{ 180.0f,39.0f,0.0f },
		{ 180.0f,-110.0f,0.0f },
		{ 180.0f,-260.0f,0.0f }
	};
	bool gate_skip = false; //Aが押されるとゲートの速度を上げる。動き終わったときもtrueを入れる。

	//星の数を表示する位置
	const CVector2 const star_pos_array[4] = {
		{ 420.0f, 195.0f },
		{ 420.0f, 55.0f },
		{ 420.0f, -95.0f },
		{ 420.0f, -245.0f }
	};
};


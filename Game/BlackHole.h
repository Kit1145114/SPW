#pragma once
#include "Planet.h"
#include "Game.h"
#include"Meteo.h"

class Game;
class Player;
class Planet;
class Draw_Player;
class BlackHole : public IGameObject
{
public:
	BlackHole();
	~BlackHole();
	bool Start();
	//生成。
	//position      (BH発生場所。
	//magnification (BH大きさ倍率。
	static void Generate(CVector3 position, float magnification); 
	//重力。
	void Gravity();
	//発生時間カウント。
	//Deathtimeを経過すると消滅へと向かう。
	void Count();
	//完全削除。
	void Death();
	//POP処理、少しづつ大きくなる。
	void PopSize();
	//Death処理、少しづつ小さくなる。
	void DeathSize();
	void Update();

	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	void SetScale(CVector3 sca)
	{
		scale = sca;
	}
protected:
	prefab::CEffect* effect =nullptr;
	Game* m_game = nullptr;
	Draw_Player* Pl1 = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 scale = { 1.0f,1.0f,1.0f };//標準スケール、状況に合わせて変更可。
	float timer = 0.0f;            //   発生からの時間をカウントする。
	float Deathtime = 8.0f;        //   発生時間、←経過すると消滅へと向かう。
	float radius = { 1.0f };       //	基本惑星の半径。
	float Searchment = { 1500.0f };//	BHの重力範囲の調整。
	float G_limitar = { 50000.0f };//   BHの重力（Ｇ）調整。
	float BBHnizyou = { 1000.0f }; //   BBH（二乗調整。
	bool Countflg = false;         //   自然消滅するかのフラグ。
};


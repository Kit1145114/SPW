#pragma once
//#include "Player.h"
#include "Planet.h"
#include"Game.h"

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
	//時間制限ありの普通のＢＨ
	static void Generate(CVector3 position, float magnification); 
	//時間制限なしの固定のＢＨ
	static void Generate2(CVector3 position, float magnification); 
	void Move();
	void Gravity();
	void Count();
	void Death();
	void Update();
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	void SetScale(CVector3 sca)
	{
		scale = sca;
	}
	private:
	prefab::CEffect* effect;
	Game* m_game = nullptr;
	Draw_Player* Pl1 = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 scale = { 1.0f,1.0f,1.0f };
	int timer = 0;
	float radius = { 1.0f };       //	基本惑星の半径。
	float Searchment = { 1500.0f };//	BHの重力範囲の調整。
	float G_limitar = { 10000.0f };    //   BHの重力（Ｇ）調整。
	bool Countflg = false;         //自然消滅するかのフラグ。
};


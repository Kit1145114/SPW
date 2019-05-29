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
	static void Generate(CVector3 position, float magnification); 
	void Move();
	void Gravity();
	void Count();
	void Death();
	void PopSize();
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
	CVector3 scale = { 1.0f,1.0f,1.0f };
	float timer = 0.0f;
	float radius = { 1.0f };       //	î{f¯Ì¼aB
	float Searchment = { 1500.0f };//	BHÌdÍÍÍÌ²®B
	float G_limitar = { 50000.0f };//   BHÌdÍifj²®B
	float BBHnizyou = { 1000.0f }; //   BBHiñæ²®B
	bool Countflg = false;         //   ©RÁÅ·é©ÌtOB
};


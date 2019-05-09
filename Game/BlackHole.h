#pragma once
//#include "Player.h"
#include "Planet.h"
class Player;
class Planet;
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
	void Update();
	
private:
	prefab::CEffect* effect;
	Game* m_game = nullptr;
	Draw_Player* Pl1 = nullptr;
	//Player* m_player[4] = { nullptr };
	CVector3 m_position;
	int timer = 0;
	float radius = { 1.0f };//	äÓñ{òfêØÇÃîºåa
};


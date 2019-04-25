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
	void Move();
	void Gravity();
	void Update();
	
private:
	Game* m_game = nullptr;
	Draw_Player* Pl1 = nullptr;
	Player* m_player[4] = { nullptr };
	CVector3 m_position;
	float radius = { 30.0f };//	äÓñ{òfêØÇÃîºåa
};


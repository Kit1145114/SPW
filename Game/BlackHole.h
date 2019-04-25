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
	Draw_1P* Pl1 = nullptr;
	Draw_2P* Pl2 = nullptr;
	Draw_3P* Pl3 = nullptr;
	Draw_4P* Pl4 = nullptr;
	Player* m_player[4] = { nullptr };
	CVector3 m_position;

	
	float radius = { 30.0f };//	äÓñ{òfêØÇÃîºåa
};


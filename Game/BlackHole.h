#pragma once
//#include "Player.h"
#include "Planet.h"
class Player;
class SansenKazu;
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
	SansenKazu* m_sansenkazu = nullptr;
	CVector3 m_position;

	
	int PadMaxKazu = 0;
	float radius = { 30.0f };//	äÓñ{òfêØÇÃîºåa
};

